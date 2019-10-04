#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "network.hpp"
#include "neuron.hpp"

class NetworkSettings {
public:
  NetworkSettings(Net &net);

  void saveSettings(std::string path);
  void openSettings(std::string path);

private:
  Net &network;
};