# Multithreaded Incremental Entropy Calculator (PA1)

## Overview
This repository contains my implementation of a multithreaded incremental entropy algorithm, as proposed in the paper "Entropy-based scheduling performance in real-time multiprocessor systems" by Dr. Rincon. This project was developed as part of my Operating Systems course at the University of Houston.

## Objective
The aim of this assignment is to create a multithreaded version of the incremental entropy algorithm. The program reads a series of strings representing task scheduling information of CPUs in a multiprocessor system and calculates the entropy at each scheduling instant using POSIX threads.

## Features
- **Multithreading**: Utilizes POSIX threads for concurrent entropy calculations.
- **Dynamic Input**: Reads scheduling information from STDIN.
- **Efficient Entropy Calculation**: Implements Dr. Rincon's incremental entropy algorithm.

## How to Run
To compile and run this project:

1. Clone the repository:
```bash
git clone https://github.com/mustafaemresahin/multithreaded-entropy-calculation.git
```

2. Navigate to the repository directory:

```bash
cd multithreaded-entropy-calculation
```

3. Compile the program using g++:

```bash
g++ -pthread -o entropyCalculator main.cpp
```

4. Run the program:

```bash
./entropyCalculator
```
Input the scheduling information when prompted.