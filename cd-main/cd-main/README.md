# C++ Code Optimizer

This project is a C++ code optimizer that performs various optimizations on C source code including constant folding, dead code elimination, and arithmetic optimization.

## Prerequisites

- C++ compiler (GCC/G++ 13.3.0 or higher)
- CMake (version 3.0 or higher)
- Make

## Project Structure
```
.
├── include/           # Header files
│   ├── ast.hpp       # AST node definitions
│   ├── optimizer.hpp # Optimizer class definition
│   └── parser.hpp    # Parser class definition
├── src/              # Source files
│   ├── main.cpp      # Program entry point
│   ├── ast.cpp       # AST node implementations
│   ├── optimizer.cpp # Optimization logic
│   └── parser.cpp    # Parser implementation
├── input/            # Input C source files
│   ├── test.c        # Simple test case
│   └── complex_test.c # Complex test case
├── output/           # Optimized output files
├── build/            # Build directory (created during build)
├── CMakeLists.txt    # CMake configuration
└── README.md         # This file
```

## Building the Project

1. **Clone the repository** (if you haven't already):
   ```bash
   git clone <repository-url>
   cd <repository-name>
   ```

2. **Create and enter the build directory**:
   ```bash
   mkdir -p build
   cd build
   ```

3. **Generate build files with CMake**:
   ```bash
   cmake ..
   ```

4. **Build the project**:
   ```bash
   make
   ```

## Running the Optimizer

1. **Basic Usage**:
   ```bash
   ./code_optimizer <input-file>
   ```
   Example:
   ```bash
   ./code_optimizer ../input/test.c
   ```

2. **View the Optimized Output**:
   The optimized code will be saved in the `output` directory with the prefix "optimized_".
   Example:
   ```bash
   cat ../output/optimized_test.c
   ```

## Example Test Cases

1. **Simple Test** (test.c):
   ```c
   int main() {
       int a = 2 + 3;
       int b = 4 + 6;
       int c = a + b;
       return 0;
   }
   ```

2. **Complex Test** (complex_test.c):
   ```c
   int main() {
       int x = 10;
       int y = 20;
       int z = x + y * 2;
       if (false) {
           int unused = 100;
       }
       return z;
   }
   ```

## Expected Output

For the simple test case, the optimizer will produce:
```c
int main() {
    int a = 5;        // 2 + 3 folded to 5
    int b = 10;       // 4 + 6 folded to 10
    int c = (a + b);  // Kept as is (depends on variables)
    return 0;
}
```

## Troubleshooting

1. **CMake Cache Issues**:
   If you encounter CMake cache issues, clean the build directory:
   ```bash
   rm -rf build
   mkdir build
   cd build
   cmake ..
   make
   ```

2. **Permission Issues**:
   If you get permission errors, make sure the output directory is writable:
   ```bash
   chmod -R 755 output/
   ```

3. **Build Errors**:
   If you encounter build errors:
   - Make sure you have the required dependencies
   - Check that your compiler version is compatible
   - Verify that all source files are present

