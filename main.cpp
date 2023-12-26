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
