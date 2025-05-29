#include "optimizer.hpp"
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <vector>
#include <stdexcept>

void run_optimizer(const std::string& filepath) {
    std::ifstream input(filepath);
    if (!input.is_open()) {
        std::cerr << "[!] Failed to open input file.\n";
        return;
    }

    std::cout << "[*] Reading input C code...\n";

    std::ofstream output("output/optimized_test.c");
    std::string line;

    // Simple regex to match: int var = number + number;
    std::regex constantExprPattern(R"(^\s*int\s+(\w+)\s*=\s*(\d+)\s*\+\s*(\d+)\s*;)");
    std::smatch match;

    while (std::getline(input, line)) {
        if (std::regex_match(line, match, constantExprPattern)) {
            std::string varName = match[1];
            int left = std::stoi(match[2]);
            int right = std::stoi(match[3]);
            int result = left + right;

            std::string optimizedLine = "int " + varName + " = " + std::to_string(result) + ";";
            output << optimizedLine << std::endl;
            std::cout << "[+] Optimized: " << line << " → " << optimizedLine << std::endl;
        } else {
            output << line << std::endl; // write unchanged
        }
    }

    input.close();
    output.close();

    std::cout << "[✔] Optimization complete! Output saved to output/optimized_test.c\n";
}

CodeOptimizer::CodeOptimizer() : ast(nullptr) {}

bool CodeOptimizer::loadCode(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    sourceCode = buffer.str();
    std::cout << "Loaded source code:\n" << sourceCode << std::endl;

    try {
        Parser parser(sourceCode);
        ast = parser.parseFunction();
        std::cout << "Successfully parsed AST" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error: Failed to parse code: " << e.what() << std::endl;
        return false;
    }
}

bool CodeOptimizer::optimize() {
    if (!ast) {
        std::cerr << "Error: No AST available for optimization" << std::endl;
        return false;
    }

    try {
        // Apply optimization passes
        ast->optimize();
        constantFolding();
        deadCodeElimination();
        optimizeArithmetic();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error during optimization: " << e.what() << std::endl;
        return false;
    }
}

bool CodeOptimizer::saveOptimizedCode(const std::string& filename) {
    if (!ast) {
        std::cerr << "Error: No optimized AST available" << std::endl;
        return false;
    }

    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing" << std::endl;
        return false;
    }

    try {
        file << ast->toString();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error while saving optimized code: " << e.what() << std::endl;
        return false;
    }
}

void CodeOptimizer::constantFolding() {
    // Constant folding is now handled by the AST nodes themselves
    // This method is kept for future extensions
}

void CodeOptimizer::deadCodeElimination() {
    // Dead code elimination is now handled by the AST nodes themselves
    // This method is kept for future extensions
}

void CodeOptimizer::optimizeArithmetic() {
    // Arithmetic optimization is now handled by the AST nodes themselves
    // This method is kept for future extensions
}
