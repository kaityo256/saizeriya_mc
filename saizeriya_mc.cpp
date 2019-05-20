#include "mc.hpp"

int main() {
  MC::load_files();
  std::mt19937 mt;
  MC m;
  for (int i = 0; i < 1000000; i++) {
    m.onestep(0.001, mt);
  }
  m.show();
}