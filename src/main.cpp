#include <iostream>
#include "./includes/network.hpp"
#include "./includes/trainingdata.hpp"

void showVectorValues(std::string label, std::vector<double> &v) {
  std::cout << label << " ";
  for (const double &d : v) {
    std::cout << d << " ";
  }

  std::cout << std::endl;
}

int main() {
  std::string trainingDataFile;
  std::cout << "Enter training data file's name? ";
  std::cin >> trainingDataFile;
  // TrainingData trainData(trainingDataFile);
  TrainingData trainData;
  trainData.openData(trainingDataFile);

  std::vector<unsigned> structure;
  trainData.getStructure(structure);
  Net network(structure);

  std::vector<double> inputValues, targetValues, resultValues;
  int trainingPass = 0;

  while (!trainData.isEof()) {
    trainingPass++;
    std::cout << std::endl << "Pass " << trainingPass;

    //Get new input data and feed it forward
    if (trainData.getNextInputs(inputValues) != structure[0]) {
      break;
    }
    showVectorValues(": Inputs:", inputValues);
    network.feedForward(inputValues);

    network.getResults(resultValues);
    showVectorValues("Output:", resultValues);

    // Train the network what outputs should have been
    trainData.getTargetOutputs(targetValues);
    showVectorValues("Targets:", targetValues);
    // assert(targetValues.size() == structure.back());

    network.backProp(targetValues);

    // Report how well the training goes
    std::cout << "Net recent average error: " << network.getRecentAverageError() << std::endl;
  }

  std::cout << std::endl << "Done";

  std::cout << std::endl << "Now you can test it: ";

  std::vector<double> nextValues(2), lastResults;
  while(true) {
    std::cout << std::endl << "- ";
    std::cin >> nextValues[0] >> nextValues[1];
    network.feedForward(nextValues);
    network.getResults(lastResults);
    showVectorValues("Result: ", lastResults);
  }

  return 0;
}