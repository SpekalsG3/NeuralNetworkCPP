#include "./includes/networksettings.hpp"

NetworkSettings::NetworkSettings(Net &net) : network(net) {}

void NetworkSettings::saveSettings(std::string path) {
  std::ofstream settings(path);
  settings << "structure:";
  std::vector<Layer> netLayers = this->network.getLayers();
  for (const Layer& layer : netLayers) {
    settings << " " << layer.size() - 1;
  } 
  for (unsigned i = 0; i < netLayers.size(); i++) {
    for (unsigned j = 0; j < netLayers[i].size() - 1; j++) {
      settings << std::endl << i << ' ';
      netLayers[i][j].getData(settings);
    }
  }
}

void NetworkSettings::openSettings(std::string path) {
  std::ifstream settings(path);
  std::stringstream line;
  std::string settingsParam;
  unsigned indexLayer, indexNeuron;
  double gradient;
  Connection weight;
  std::vector<Connection> weights;
  while (getline(settings, settingsParam)) {
    line.str(settingsParam);
    line >> indexLayer >> indexNeuron >> gradient;
    while(line >> weight.weight && line >> weight.deltaWeight)
      weights.push_back(weight);
    this->network.setNeuron(indexLayer, indexNeuron, gradient, weights);
  }
}