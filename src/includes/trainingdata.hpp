#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

class TrainingData {

public:
  TrainingData();
  TrainingData(const std::string filename);
  void openData(const std::string filename);
  bool isEof(void);
  void getStructure(std::vector<unsigned> &structure);

  unsigned getNextInputs(std::vector<double> &inputValues);
  unsigned getTargetOutputs(std::vector<double> &targetOutputValues);

private:
  std::ifstream trainingDataFile;

};