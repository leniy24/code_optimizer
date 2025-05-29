#include "optimizer.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

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

    try {
        Parser parser(sourceCode);
        ast = parser.parseFunction();
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
    // Handled by AST nodes
}

void CodeOptimizer::deadCodeElimination() {
    // Handled by AST nodes
}

void CodeOptimizer::optimizeArithmetic() {
    // Handled by AST nodes
}