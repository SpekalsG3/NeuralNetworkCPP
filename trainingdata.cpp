#include "./includes/trainingdata.hpp"

TrainingData::TrainingData(const std::string filename) {
  this->trainingDataFile.open(filename.c_str());
}

bool TrainingData::isEof() {
  return this->trainingDataFile.eof();
}

void TrainingData::getStructure(std::vector<unsigned> &structure) {
  std::string line;
  std::string label;

  getline(this->trainingDataFile, line);
  std::stringstream ss(line);
  ss >> label;
  if ((this->isEof() || label.compare("structure:")) != 0) {
    abort();
  }

  while(!ss.eof()) {
    unsigned n;
    ss >> n;
    structure.push_back(n);
  }

  return;
}

unsigned TrainingData::getNextInputs(std::vector<double> &inputValues) {
  inputValues.clear();

  std::string line;
  getline(this->trainingDataFile, line);
  std::stringstream ss(line);

  std::string label;
  ss >> label;
  if (label.compare("in:") == 0) {
    double oneValue;
    while (ss >> oneValue) {
      inputValues.push_back(oneValue);
    }
  }

  return inputValues.size();
}

unsigned TrainingData::getTargetOutputs(std::vector<double> &targetOutputValues) {
  targetOutputValues.clear();

  std::string line;
  getline(this->trainingDataFile, line);
  std::stringstream ss(line);

  std::string label;
  ss >> label;
  if (label.compare("out:") == 0) {
    double oneValue;
    while (ss >> oneValue) {
      targetOutputValues.push_back(oneValue);
    }
  }

  return targetOutputValues.size();
}