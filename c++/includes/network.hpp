#pragma once
#include <vector>
#include "neuron.hpp"

typedef std::vector<Neuron> Layer;

class Net {

public:
  Net();
  Net(const std::vector<unsigned> &structure);

  void setStructure(const std::vector<unsigned int> &structure);

  void feedForward(const std::vector<double> &inputValues);
  void backProp(const std::vector<double> &targetValues);

  // Getters
  void getResults(std::vector<double> &resultValues) const;
  double getRecentAverageError() const;

  std::vector<Layer> getLayers() const;

  void setNeuron(unsigned indexLayer, unsigned indexNeuron, double gradient, std::vector<Connection> &weights);

private:
  std::vector<Layer> layers;

  double error;
  double recentAverageError;
  double recentAverageSmoothingFactor;
};