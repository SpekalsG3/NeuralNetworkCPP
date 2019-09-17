#include "./includes/neuron.hpp"
#include "./includes/network.hpp"
#include <cassert>

Net::Net(const std::vector<unsigned> &structure) {
  unsigned numLayers = structure.size();
  for (unsigned layerNum = 0; layerNum < numLayers; layerNum++) {
    this->layers.push_back(Layer());
    unsigned outputsNum = layerNum == structure.size() - 1 ? 0 : structure[layerNum + 1];

    for (unsigned neuronNum = 0; neuronNum <= structure[layerNum]; neuronNum++) {
      this->layers.back().push_back(Neuron(outputsNum, neuronNum));
    }

    // Force the bias nodes' values to 1.0
    this->layers.back().back().setOutputVal(1.0);
  }
}

void Net::feedForward(const std::vector<double> &inputValues) {
  // std::assert(inputValues.size() == this->layers[0].size() - 1);

  for (unsigned i = 0; i < inputValues.size(); i++) {
    this->layers[0][i].setOutputVal(inputValues[i]);
  }

  // Forward Propogantion
  for (unsigned layerNum = 1; layerNum < this->layers.size(); layerNum++) {
    Layer &prevLayer = this->layers[layerNum - 1];
    for (unsigned n = 0; n < this->layers[layerNum].size() -1; n++) {
      this->layers[layerNum][n].feedForward(prevLayer);
    }
  }
}

void Net::backProp(const std::vector<double> &targetValues) {
  // Calculate overall net error
  Layer &outputLayer = this->layers.back();
  this->error = 0.0;

  for (unsigned n = 0; n < outputLayer.size() - 1; n++) {
    double delta = targetValues[n] - outputLayer[n].getOutputVal();
    this->error += delta * delta;
  }

  this->error /= outputLayer.size() - 1;
  this->error = sqrt(this->error);

  this->recentAverageError = (this->recentAverageError * this->recentAverageSmoothingFactor + this->error) / (this->recentAverageSmoothingFactor + 1.0);

  // Calculate output layer gradients
  for (unsigned n = 0; n < outputLayer.size() - 1; n++) {
    outputLayer[n].calcOutputGradients(targetValues[n]);
  }

  // Calculate gradients on hidden layers
  for (unsigned layerNum = this->layers.size() - 2; layerNum > 0; layerNum--) {
    Layer &hiddenLayer = this->layers[layerNum];
    Layer &nextLayer = this->layers[layerNum + 1];

    for (unsigned n = 0; n < hiddenLayer.size(); n++) {
      hiddenLayer[n].calcHiddenGradients(nextLayer);
    }
  }

  // Update connection weights
  for (unsigned layerNum = this->layers.size() - 1; layerNum > 0; layerNum--) {
    Layer &layer = this->layers[layerNum];
    Layer &prevLayer = this->layers[layerNum - 1];

    for (unsigned n = 0; n < layer.size() - 1; n++) {
      layer[n].updateInputWeights(prevLayer);
    }
  }
}

void Net::getResults(std::vector<double> &resultValues) const {
  resultValues.clear();

  for (unsigned n = 0; n < this->layers.back().size() - 1; n++) {
    resultValues.push_back(this->layers.back()[n].getOutputVal());
  }
}

double Net::getRecentAverageError() const {
  return this->recentAverageError;
}