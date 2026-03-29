# Genetic Algorithm (C++)

## Description
This project implements a configurable genetic algorithm for solving graph-based combinatorial optimization problems (e.g. Traveling Salesman Problem).

The algorithm operates on a population of candidate solutions (paths) and iteratively improves them using evolutionary mechanisms such as selection, crossover, and mutation.

## Algorithm overview
1. **Initialization**
- Population is generated using a combination of greedy algorithms - Nearest Neighbour or Random.

2. **Evaluation**
- Each solution is evaluated based on total path cost in the graph.

3. **Selection**
- Tournament selection is used to choose parent solutions. 

4. **Crossover**
- Multiple crossover strategies are implemented:
   - PMX (Partially Mapped Crossover) 
   - Order Crossover (OX) 
   - Multipoint crossover

5. **Mutation**
- Several mutation operators are available:
   - Swap mutation
   - Inverse mutation
   - Scramble mutation

6. **Elitism and restart mechanism**
   - Best solution is continuously tracked
   - Population is partially restarted when stagnation is detected

7. **Termination**
   - Algorithm runs until a specified time limit is reached

## Architecture
The project follows a modular design using interfaces:
- `ICrossover` – crossover strategies
- `IMutator` – mutation strategies
- `IGreedy` – population initialization

This allows easy extension and experimentation with different algorithm variants.

## Configuration
All parameters are defined in an external configuration file:
- population size
- tournament size
- mutation and crossover rates
- algorithm variants (greedy, crossover, mutation)
- time limit

## Features
- Modular and extensible architecture
- Multiple genetic operators
- Configurable experiments and simulation mode
- Logging of performance and results
- Custom random number utilities

## Output
The algorithm returns:
- best path found
- total cost
- time when best solution was found
- total execution time
