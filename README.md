# Principia-Lite: A 2D Physics Engine POC

![Language](https://img.shields.io/badge/language-C%2B%2B-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Status](https://img.shields.io/badge/status-Prototype-orange.svg)

## 1. Project Overview
Principia-Lite is a lightweight, deterministic 2D physics simulation engine built from scratch in C++. 
The goal of this project is to implement a discrete-time integration solver without relying on existing physics middleware (like Box2D or PhysX) to demonstrate a fundamental understanding of computational mechanics.

This is a "Proof of Concept" (POC) for a larger, high-performance engine currently in the planning phase.

## 2. Core Concepts & Mathematical Model
This engine focuses on the "First Principles" of motion:

### A. Semi-Implicit Euler Integration
Unlike standard Euler integration which is prone to energy drift, this engine uses a Semi-Implicit approach to conserve energy stability over time:
$$v_{t+1} = v_t + \frac{F}{m} \Delta t$$
$$x_{t+1} = x_t + v_{t+1} \Delta t$$

### B. Collision Detection (AABB)
Collision resolution is handled using Axis-Aligned Bounding Boxes (AABB) for efficiency, checking overlaps in spatial dimensions before calculating impulse responses.

### C. The Time Step (Delta Time)
The simulation is decoupled from the rendering frame rate to prevent "tunneling" (objects passing through walls due to high velocity).

## 3. Build Instructions
This project has zero external dependencies for the physics core.

```bash
# Clone the repository
git clone [https://github.com/JanithaIllankoon/Principia-Lite.git](https://github.com/JanithaIllankoon/Principia-Lite.git)

# Compile (using g++)
g++ -o physics_engine main.cpp src/*.cpp -std=c++17

# Run
./physics_engine

''' Roadmap
[ ] Implement Gravity and Drag
[ ] Circle-to-Circle Collision Resolution
[ ] Impulse Resolution (Conservation of Momentum)
[ ] Visual Debugger (rendering output)'''