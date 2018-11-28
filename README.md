
# TSP
## Project description
This project implements the following algorithms regarding the tsp:
* Brute-Force 
* Branch & Bound( Best First Search and Depth First Search)
* Held-Karp(Dynamic programming)
 
All of three mentioned above find the shortest Hamiltonian cycle (if such exists) within both symmetric and asymmetric graphs.
## Requirements
* **CMake** version > 2.8.2
## Technical overview
The program was implemented as a cross-platform console application. In order to simplify the process of building and running the program on different platforms CMake was used. The build process goes as follows:
1. Create a **build** directory within the top level of a source tree `$ mkdir build`.
2. Enter the directory `$ cd build`.
3. Run an out of source build `$ cmake ..`
4. Compile the project with `$ make`.
5. You can also specify the makefile generator with:

	` $ cmake -G "MinGW Makefiles" ..`
6. In order to check the generators available on your platform run `$ cmake --help`.

The directory - **data** contains text files with example matrices which could be used to test the algorithms. You can introduce new files , however they have to follow the format represented below:
```
4 		# Number of nodes in the first line.
5 4 3 9		# Consecutive rows of an adjacency matrix.
1 4 3 2
8 7 4 3
9 0 8 7
```
Additionally, there is an option within the program to generate a random asymmetric graph with a specified amount of nodes.
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
