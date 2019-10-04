# Simple neural network in c++ and python
## Fast run

To see this neural network in work immediately you can go to my repl project on [Repl.it](https://repl.it/) (There is only one training data sample):

[C++ Neural Network](https://repl.it/@SpekalsG3Play/Neural-Network-C)  
[Python Neural Network](https://repl.it/@SpekalsG3Play/Neural-Network-Python)

## Installation

Use following command to clone this repo:

```bash
git clone https://github.com/SpekalsG3/NeuralNetworks.git
```

Then go to created folder:

```bash
cd NeuralNetworks
```

Choose what language you want to use and go to corresponding folder

Now you can run this neural network.


To compile C++ files use mingw and run following command:

```bash
g++ -o main main.cpp network.cpp neuron.cpp trainingdata.cpp
```

To use python versio simply create another .py file and import network.py as you like:

```python
import network

# or

from network import *
```

## Utils

There is "trainingdatasample.cpp" in C++ version which you can compile, run executable and create your own sample with trainingdata