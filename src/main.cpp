#include "include/cpu.hpp"
#include <algorithm>
#include <memory>

int main(int argc, char *argv[]) {
  // Cpu cpu = Cpu();
  // cpu.run(1);
  std::unique_ptr<ICpu> cpu{new Cpu()};
  cpu->run(1);
  return 0;
}
