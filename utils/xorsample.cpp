#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <iomanip>

int main() {
  std::ofstream sample("xorsample.txt");

  sample << "structure: 2 4 1" << std::endl;

  std::random_device rd;
  std::uniform_int_distribution<int> dist(0, 1);

  for (unsigned n = 0; n < 1000; n++) {
    double val1 = dist(rd);
    double val2 = dist(rd);
    sample << std::fixed << std::setprecision(1) << "in: " << val1 << ' ' << val2 << std::endl << "out: " << (double)((!val1 && !val2) || (val1 && val2)) << std::endl;
  }

  std::cout << "Done";
  std::cin.get();

  return 0;
}