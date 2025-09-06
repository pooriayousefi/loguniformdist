# Log-Uniform Distribution

[![Build Status](https://github.com/pooriayousefi/loguniformdist/actions/workflows/ci.yml/badge.svg)](https://github.com/pooriayousefi/loguniformdist/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B20)
[![CMake](https://img.shields.io/badge/CMake-3.20%2B-green.svg)](https://cmake.org/)

A modern C++20 library for generating log-uniform distributed random numbers. Log-uniform distribution is useful for sampling values that span several orders of magnitude, commonly used in hyperparameter optimization and scientific computing.

## 🚀 Features

- **C++20 Standard**: Modern C++ with concepts and constraints
- **Type Safety**: Template constraints for floating-point types
- **Dual Seeding**: Automatic hardware-based or manual seeding options
- **Parameter Validation**: Runtime checks for mathematical validity
- **High Performance**: Efficient implementation using STL algorithms
- **Cross-Platform**: Works on Linux (g++), macOS (clang++), and Windows (MSVC)

## 🎯 Quick Start

```cpp
#include "loguniformdist.hpp"
#include <iostream>

int main() {
    try {
        // Generate 100 log-uniform samples between 1.5 and 20.06
        auto samples = loguniform::distributor(1.5, 20.06, 100, automatic::seeder());
        
        for (const auto& sample : samples) {
            std::cout << sample << std::endl;
        }
        
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
```

## 📚 API Reference

### Core Functions

#### `loguniform::distributor<T>(minval, maxval, count, seed)`

Generates a vector of log-uniform distributed random numbers.

**Parameters:**
- `minval`: Minimum value (must be > 0)
- `maxval`: Maximum value (must be > 0)
- `count`: Number of samples to generate
- `seed`: Random seed value

**Returns:** `std::vector<T>` containing the generated samples

#### `loguniform::simulator<T>(minval, maxval)`

Creates a log-uniform distribution function object.

**Parameters:**
- `minval`: Minimum value (must be > 0)
- `maxval`: Maximum value (must be > 0)

**Returns:** Lambda function that generates samples when called with RNG

### Seeding Options

#### `automatic::seeder()`

Generates a seed automatically using hardware random device if available, or pseudo-random generation based on thread ID and system time.

#### `manual::seeder(unsigned seed)`

Uses a manually specified seed value.

## 🔬 Mathematical Foundation

Log-uniform distribution transforms uniform random variables using exponential function:

```
X ~ LogUniform(a, b) if log(X) ~ Uniform(log(a), log(b))
```

This is equivalent to: `X = exp(U * (log(b) - log(a)) + log(a))` where `U ~ Uniform(0,1)`

## 🏗️ Building from Source

```bash
# Clone repository
git clone https://github.com/pooriayousefi/loguniformdist.git
cd loguniformdist

# Build with CMake
cmake --preset=default
cmake --build build/default

# Run example
./build/default/loguniformdist_example
```

## 📊 Use Cases

- **Hyperparameter Optimization**: Learning rates, regularization parameters
- **Scientific Computing**: Physical constants spanning multiple orders of magnitude
- **Monte Carlo Simulations**: Sampling from scale-invariant distributions
- **Financial Modeling**: Asset prices and volatility modeling

## 🔧 Requirements

- C++20 compatible compiler (GCC 11+, Clang 13+, MSVC 2022+)
- CMake 3.20 or later

## 📄 License

This project is licensed under the MIT License - see the [LICENSE.txt](LICENSE.txt) file for details.

---

**Author**: [Pooria Yousefi](https://github.com/pooriayousefi)  
**Repository**: [https://github.com/pooriayousefi/loguniformdist](https://github.com/pooriayousefi/loguniformdist)
