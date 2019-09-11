#include "./includes/neuron.hpp"

typedef std::vector<Neuron> Layer;

double Neuron::randomWeight() {
  return rand() / double(RAND_MAX);
}

Neuron::Neuron(unsigned outputsNum, unsigned index) {
  for (unsigned c = 0; c < outputsNum; c++) {
    this->outputWeights.push_back(Connection());
    this->outputWeights.back().weight = this->randomWeight();
  }

  this->index = index;
}

void  Neuron::setOutputVal(double val) {
  this->outputVal = val;
}

double Neuron::getOutputVal() const {
  return this->outputVal;
}

double Neuron::transferFunction(double x) {
  // tang - x E [-1.0; 1]
  return tanh(x);
}

double Neuron::transferFunctionDerivative(double x) {
  // tanh derivative

  return 1.0 - x * x;
}

void Neuron::feedForward(const Layer &prevLayer) {
  double sum = 0.0;
  // Sum the previous layers' outputs

  for (unsigned n = 0; n < prevLayer.size(); n++) {
    sum += prevLayer[n].getOutputVal() * prevLayer[n].outputWeights[this->index].weight;
  }

  this->outputVal = this->transferFunction(sum);
}

double Neuron::sumDOW(const Layer &nextLayer) const {
  double sum = 0.0;
  for (unsigned n = 0; n < nextLayer.size() - 1; n++) {
    sum += this->outputWeights[n].weight * nextLayer[n].gradient;
  }
  return sum;
}

void Neuron::calcOutputGradients(double targetVal) {
  double delta = targetVal - this->outputVal;
  this->gradient = delta * this->transferFunctionDerivative(this->outputVal);
}

void Neuron::calcHiddenGradients(const Layer &nextLayer) {
  double dow = sumDOW(nextLayer);
  this->gradient = dow * this->transferFunctionDerivative(this->outputVal);
}

double Neuron::eta = 0.15;
double Neuron::alpha = 0.5;

void Neuron::updateInputWeights(Layer &prevLayer) {
  for (unsigned n = 0; n < prevLayer.size(); n++) {
    Neuron &neuron = prevLayer[n];
    double oldDeltaWeight = neuron.outputWeights[this->index].deltaWeight;

    double newDeltaWeight =
      // Individual input
      eta * neuron.getOutputVal() * this->gradient
      // Add momentum
      + alpha * oldDeltaWeight;

    neuron.outputWeights[this->index].deltaWeight = newDeltaWeight;
    neuron.outputWeights[this->index].weight += newDeltaWeight;
  }
}
