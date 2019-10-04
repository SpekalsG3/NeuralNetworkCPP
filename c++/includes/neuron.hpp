#pragma once
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>

class Neuron;
typedef std::vector<Neuron> Layer;

struct Connection {
  double weight;
  double deltaWeight;
};

class Neuron {

public:
  Neuron(unsigned outputsNum, unsigned index);

  void feedForward(const Layer &prevLayer);

  void calcOutputGradients(double targetVal);
  void calcHiddenGradients(const Layer &nextLayer);
  void updateInputWeights(Layer &prevLayer);
  double sumDOW(const Layer &nextLayer) const;

  // Setters and Getters
  void setOutputVal(double val);
  double getOutputVal() const;

  void getData(std::ofstream &output);
  void setGradient(double gradient);
  void setWeights(std::vector<Connection> &weights);

private:
  static double eta;    // overall net learning rate [0.0; 1.0]
  static double alpha;  // momentum [0.0; n]

  static double randomWeight();
  static double transferFunction(double x);
  static double transferFunctionDerivative(double x);

  double outputVal;
  std::vector<Connection> outputWeights;
  
  unsigned index;
  double gradient;
};