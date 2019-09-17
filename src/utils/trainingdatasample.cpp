#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>

int main() {
  std::string output;
  std::cout << "What do we call training data file? ";
  std::cin >> output;
  std::ofstream sample(output + ".txt");

  unsigned layersNum;
  std::cout << "How many layers? ";
  std::cin >> layersNum;

  sample << "structure:";
  for (unsigned n = 0; n < layersNum; n++) {
    unsigned neuronesNum;
    std::cout << "How manu neurones on layer " << n << "? ";
    std::cin >> neuronesNum;
    sample << " " << neuronesNum;
  }
  sample << std::endl;

  unsigned testsNum;
  std::cout << "How many tests we will create? ";
  std::cin >> testsNum;
  for (unsigned n = 0; n < testsNum; n++) {
    double inVal;
    double outVal;
    std::cout << "In value: ";
    std::cin >> inVal;
    std::cout << "Out value: ";
    std::cin >> outVal;
    sample << "in:" << inVal << std::endl << "out:" << outVal << std::endl;
  }

  std::cout << "Done";

  return 0;
}