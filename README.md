# Apollo and Diana Maze Solver

## Overview
This project models the **Apollo and Diana maze problem** using a graph and implements a depth-first search (DFS)-based traversal algorithm to solve these mazes. The goal is to determine a valid path from the starting position to the goal while adhering to the maze's constraints.

## Features
- **Graph Representation**: Models the maze as a graph where nodes represent positions and edges define valid movements.
- **Iterative Depth-First Search (DFS) Algorithm**: Implements DFS to find a valid path while keeping track of color changes.
- **Maze Validation**: Detects whether a given maze is solvable or invalid.
- **Handling Non-Square Mazes**: Supports arbitrary rectangular maze dimensions.

## Installation & Compilation
### Prerequisites
- **C++ compiler** (e.g., g++)
- **Standard input/output for reading and writing maze data**

### Compilation
```sh
g++ -o maze_solver main.cpp
```

### Running the Program
```sh
./maze_solver
```

The program reads from `input.txt` and outputs the solution to `output.txt`.

## Input Format
The input file (`input.txt`) contains:
1. The first line specifies the number of rows and columns in the maze.
2. The following lines contain space-separated arrow strings formatted as:
   - `R-direction` for red arrows (e.g., `R-N` for North)
   - `B-direction` for blue arrows (e.g., `B-SW` for Southwest)
   - `O` for the bull's-eye (goal position)

## Output Format
The output file (`output.txt`) contains:
- A sequence of moves indicating how to traverse the maze.
- If no valid path is found, it prints `No solution`.

## Error Handling
- **Invalid Maze Structure**: Detects and reports if the maze is not well-formed.
- **Unreachable Goal**: Reports when the goal cannot be reached from the start.
- **Non-Square Mazes**: Ensures proper handling of rectangular mazes.

