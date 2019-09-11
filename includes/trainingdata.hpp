#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

class TrainingData {

public:
  TrainingData(const std::string filename);
  bool isEof();
  void getStructure(std::vector<unsigned> &structure);

  unsigned getNextInputs(std::vector<double> &inputVals);
  unsigned getTargetOutputs(std::vector<double> &targetOutputValues);

private:
  std::ifstream trainingDataFile;

};