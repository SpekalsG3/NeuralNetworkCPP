#pragma once
#include <vector>
#include "neuron.hpp"

typedef std::vector<Neuron> Layer;

class Net {

public:
  Net(const std::vector<unsigned> &structure);
  
  void feedForward(const std::vector<double> &inputValues);
  void backProp(const std::vector<double> &targetValues);

  // Getters
  void getResults(std::vector<double> &resultValues) const;
  double getRecentAverageError() const;

private:
  std::vector<Layer> layers;

  double error;
  double recentAverageError;
  double recentAverageSmoothingFactor;
};