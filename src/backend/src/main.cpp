#include "optimizer.hpp"
#include <iostream>
#include <string>
#include <filesystem>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::filesystem::path inputPath(inputFile);
    std::filesystem::path outputPath = std::filesystem::current_path() / "output" / ("optimized_" + inputPath.filename().string());

    CodeOptimizer optimizer;
    
    std::cout << "Loading and parsing code from " << inputFile << "..." << std::endl;
    if (!optimizer.loadCode(inputFile)) {
        std::cerr << "Error: Could not load or parse input file " << inputFile << std::endl;
        return 1;
    }

    std::cout << "Optimizing code..." << std::endl;
    if (!optimizer.optimize()) {
        std::cerr << "Error: Optimization failed" << std::endl;
        return 1;
    }

    std::cout << "Saving optimized code to " << outputPath << "..." << std::endl;
    if (!optimizer.saveOptimizedCode(outputPath.string())) {
        std::cerr << "Error: Could not save optimized code to " << outputPath << std::endl;
        return 1;
    }

    std::cout << "Optimization complete! Check " << outputPath << " for the optimized code." << std::endl;
    return 0;
}