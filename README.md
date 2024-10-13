# Simulator for Public City Transport Network

## Project Task
**Area:** Object-Oriented Programming  
**Year:** 2020/2021  
**Language:** C++

## Functional Specification

Implement a simulator for the city transport network. It is necessary to write a set of classes with appropriate methods, constructors, operators, and destructors to realize the system.

### Loading Data about the City Transport Network
- Load from two text files:
  - **First file:** information about stops (format: `stop_id stop_name`)
  - **Second file:** information about transport lines (format: `line_id stop_ids_direction_A#stop_ids_direction_B`)

### Displaying Information about the City Transport Network
- Display information about a stop based on its ID.
- Display information about a line based on its identifier.
- Display statistical information about a line.

### Simulating Movement through the Transport Network
- Generate a route between selected stops using a graph structure for the network representation and its visits.
- **Route Finding Strategies:**
  1. **First Strategy (Mandatory):** Find any route between the starting and ending stops.
  2. **Second Strategy:** Find a route that passes through the fewest stops between the starting and ending stops.
  3. **Third Strategy:** Find a route that requires the fewest transfers between the starting and ending stops.

### User Interaction
- An interactive system for selecting options.

### Notes
The program system is implemented with detailed comments, a modular structure, and is easily extensible with new classes and operations. I implemented my own tests in addition to the ones provided in the task.
