#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <pthread.h>
#include <sstream>
#include <string>
#include <vector>

// Define a struct to hold thread data
struct ThreadData {
  std::string input;
  std::vector<double> *entropy;
};

// Function to calculate incremental entropy
double calc_incremental_entropy(std::map<char, int> &freq, int &currFreq, double &currH, char selectedTask, int extraFreq, int &NFreq) {
  double H, newTerm, currentTerm;

  // Update the total frequency
  NFreq = currFreq + extraFreq;

  // Calculate the entropy
  if (NFreq == extraFreq) {
    H = 0;
  } else {
    currentTerm = freq[selectedTask] == 0 ? 0 : freq[selectedTask] * log2(freq[selectedTask]);
    newTerm = (freq[selectedTask] + extraFreq) * log2(freq[selectedTask] + extraFreq);
    NFreq = static_cast<double>(NFreq);
    H = log2(NFreq) - ((log2(currFreq) - currH) * (currFreq) - currentTerm + newTerm) / NFreq;
  }

  // Update the current frequency and entropy
  currFreq = NFreq;
  currH = H;

  return H;
};

// Thread function to calculate entropy
void *entropy(void *arg) {
  ThreadData *data = (ThreadData *)arg;
  std::istringstream iss(data->input);
  char selectedTask;
  int extraFreq;
  std::map<char, int> freq;
  int currFreq = 0;
  double currH = 0.0;
  int NFreq = 0;

  // Parse the input and calculate entropy for each task
  while (iss >> selectedTask >> extraFreq) {
    if (freq.find(selectedTask) == freq.end()) {
      freq[selectedTask] = 0;
    }
    double ent = calc_incremental_entropy(freq, currFreq, currH, selectedTask, extraFreq, NFreq);
    freq[selectedTask] += extraFreq;
    data->entropy->push_back(ent);
  }

  return NULL;
}

int main() {
  std::vector<std::string> inputs;
  std::string line;

  // Read lines from standard input to get task scheduling information
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      break;
    }
    inputs.push_back(line);
  }

  // Initialize data structures for storing entropy values
  std::vector<std::vector<double>> entropies(inputs.size());
  std::vector<ThreadData> data(inputs.size());
  std::vector<pthread_t> tid(inputs.size());

  // Create threads to calculate entropy for each CPU
  for (int i = 0; i < inputs.size(); i++) {
    data[i] = {inputs[i], &entropies[i]};
    pthread_create(&tid[i], NULL, entropy, &data[i]);
  }

  // Wait for threads to complete
  for (int i = 0; i < inputs.size(); i++) {
    pthread_join(tid[i], NULL);
  }

  // Output the results
  for (size_t i = 0; i < inputs.size(); i++) {
    std::cout << "CPU " << (i + 1) << std::endl;
    std::cout << "Task scheduling information: ";

    std::istringstream iss(inputs[i]);
    char task;
    int time;
    bool first = true;

    // Display the task scheduling information
    while (iss >> task >> time) {
      if (!first)
        std::cout << ", ";
      std::cout << task << "(" << time << ")";
      first = false;
    }

    std::cout << std::endl << "Entropy for CPU " << (i + 1) << std::endl;
    // Display the calculated entropy values for the CPU
    for (auto &e : entropies[i]) {
      std::cout << std::fixed << std::setprecision(2) << e << ' ';
    }
    std::cout << std::endl << std::endl;
  }

  return 0;
  
}
