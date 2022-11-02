
# TSP

Solves for the optimal path between taxi routes by treating every route as a point in an asymetric traveling salesman problem.

## Installation
Download the proper executable for your platform from Releases tab.
## Usage
Use with the following command:
### Linux
```
atsp_taxi problem.json
```
### Windows
```
atsp_taxi.exe problem.json
```
`problem.json` should be a json file describing the problem. Sample problems can be generated with `generate_problem.py`.

## Project description
This project implements the following algorithms regarding the tsp:
* Brute-Force 
* Branch & Bound( Best First Search and Depth First Search)
* Held-Karp(Dynamic programming)
 
All of three mentioned above find the shortest Hamiltonian cycle (if such exists) within both symmetric and asymmetric graphs.

## Building from source
First, clone the repository.
### Linux
```
apt install libcurl4-openssl-dev #install libcurl 
mkdir build
cd build
cmake ..
make
```
### Windows
Requires Visual Studio and cmake
```
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
```

## Overview of the algorithms
### Brute-Force
Time complexity: O(n!) or O((n-1)!) if the starting node has been predetermined.

The Brute-Force algorithm generates all possible Hamiltonian cycles within the tree and selects a one with a minimal cost of travel. The algorithm for generating all possible permutations within a container can be found [here](https://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/).

### Branch & Bound
In order to get acquainted with the way the algorithm works in theory you can go [here](https://www.techiedelight.com/travelling-salesman-problem-using-branch-and-bound/) or [here](http://math.cmu.edu/~bkell/21257-2014f/tsp.pdf).
The implementation introduces two ways to traverse the tree:
* DFS - Depth First Search (Stack based)
* BFS - Best First Search (Piority queue based)

BFS while quicker(shown below) uses up more  memory on average. This occurs because the BFS method looks for the best currently possible cycle, and then starts removing the paths which have a higher bound.
___
