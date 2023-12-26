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


## Input Format
The program expects input in the following format:

```bash
[Task] [Execution Time] [Task] [Execution Time] ...
```

For example:

```bash
A 2 B 4 C 3 A 7
```


## Output
The program outputs the entropy values for each CPU scheduling information provided. For example:


```bash
CPU 1
Task scheduling information: A(2), B(4), C(3), A(7)
Entropy for CPU 1
0.00 0.92 1.53 1.42
```


## Dependencies
- g++ compiler with support for C++11 or later.
- POSIX threads library.
