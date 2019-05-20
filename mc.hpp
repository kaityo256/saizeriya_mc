#pragma once
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <x86intrin.h>

const int SIZE = 114;
typedef unsigned __int128 mbit;

inline int popcnt_u128(const mbit &s) {
  const uint64_t *m = (uint64_t *)&s;
  return _mm_popcnt_u64(m[0]) + _mm_popcnt_u64(m[1]);
}

inline std::ostream &operator<<(std::ostream &dest, mbit v) {
  char buffer[SIZE];
  for (int i = 0; i < SIZE; i++) {
    buffer[i] = (v & 1) + '0';
    v = v >> 1;
  }
  dest.rdbuf()->sputn(buffer, SIZE);
  return dest;
}

inline int bitpos(mbit s) {
  return popcnt_u128(s - 1);
}

class MC {
private:
  mbit _data;
  mbit _max_data;
  int _price;
  int _calorie;
  int _max_calorie;
  static std::vector<int> vcalorie;
  static std::vector<int> vprice;
  static std::vector<std::string> vname;

public:
  static void load_files() {
    std::ifstream ifs("calorie.txt");
    int c = 0;
    while (ifs >> c) {
      vcalorie.push_back(c);
    }
    ifs.close();
    ifs.open("price.txt");
    while (ifs >> c) {
      vprice.push_back(c);
    }
    std::string n;
    ifs.close();
    ifs.open("name.txt");
    while (ifs >> n) {
      vname.push_back(n);
    }
  }

  MC() {
    _price = 0;
    _calorie = 0;
    _data = mbit(0);
    _max_calorie = 0;
  }

  // ランダムに1ビット削除する
  mbit random_remove(const mbit &s, std::mt19937 &mt) {
    std::uniform_int_distribution<> ud(0, popcnt_u128(s) - 1);
    mbit t = s;
    const unsigned int n = ud(mt);
    for (unsigned int i = 0; i < n; i++) {
      t = t ^ (t & -t);
    }
    return (s ^ (t & -t));
  }

  // ランダムに1ビット追加する
  mbit random_add(const mbit &s, std::mt19937 &mt) {
    static const mbit mask = (mbit(1) << SIZE) - 1;
    mbit t = (~s) & mask;
    std::uniform_int_distribution<> ud(0, popcnt_u128(t) - 1);
    const unsigned int n = ud(mt);
    for (unsigned int i = 0; i < n; i++) {
      t = t ^ (t & -t);
    }
    return (s | (t & -t));
  }

  // ランダムに一品増やす
  void try_add(const double beta, std::mt19937 &mt) {
    mbit ns = random_add(_data, mt);
    int i = bitpos(ns ^ _data);
    int ncalorie = _calorie + vcalorie[i];
    // 千円超えたらアウト
    if (_price + vprice[i] > 1000) return;
    //そうでなければ無条件で更新
    _price += vprice[i];
    _calorie += vcalorie[i];
    _data = ns;
    if (_max_calorie < _calorie) {
      _max_calorie = _calorie;
      _max_data = _data;
      std::cout << _max_calorie << std::endl;
    }
  }

  // ランダムに一品減らす
  void try_remove(const double beta, std::mt19937 &mt) {
    if (_data == mbit(0)) return;
    std::uniform_real_distribution<double> ud(0.0, 1.0);
    mbit ns = random_remove(_data, mt);
    int i = bitpos(_data ^ ns);
    if (ud(mt) < exp(-vcalorie[i] * beta)) {
      _data = ns;
      _price -= vprice[i];
      _calorie -= vcalorie[i];
    }
  }

  void onestep(const double beta, std::mt19937 &mt) {
    try_add(beta, mt);
    try_remove(beta, mt);
  }

  void show() {
    mbit v = _max_data;
    int price = 0;
    int calorie = 0;
    while (v) {
      mbit vv = (v & -v);
      int i = bitpos(vv);
      std::cout << vname[i] << ":" << vcalorie[i] << " kcal " << vprice[i] << "Yen" << std::endl;
      price += vprice[i];
      calorie += vcalorie[i];
      v ^= vv;
    }
    std::cout << "合計 " << calorie << " kcal " << price << " Yen" << std::endl;
  }
};

__attribute__((weak)) std::vector<int> MC::vcalorie;
__attribute__((weak)) std::vector<int> MC::vprice;
__attribute__((weak)) std::vector<std::string> MC::vname;
