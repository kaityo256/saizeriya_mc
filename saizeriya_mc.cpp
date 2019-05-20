#include "mc.hpp"
#include "remc.hpp"

void do_mc(std::mt19937 &mt) {
  MC m;
  double max = 0.0;
  while (true) {
    m.onestep(0.01, mt);
    if (max > m.current_energy()) {
      max = m.current_energy();
      m.show();
    }
  }
}

void do_remc(std::mt19937 &mt) {
  REMC remc;
  double beta = 0.001;
  for (int i = 0; i < 20; i++) {
    MC m;
    std::cout << beta << std::endl;
    remc.add(m, beta);
    beta *= 2.0;
  }
  while (true) {
    remc.onestep(mt);
  }
}

int main() {
  std::mt19937 mt(1);
  MC::load_files();
#ifdef RE
  do_remc(mt);
#else
  do_mc(mt);
#endif
}
