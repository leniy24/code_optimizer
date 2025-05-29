#pragma once

#include "ast.hpp"
#include "parser.hpp"
#include <string>
#include <memory>

class CodeOptimizer {
public:
    CodeOptimizer();
    ~CodeOptimizer() = default;

    // Load and parse code from a file
    bool loadCode(const std::string& filename);
    
    // Optimize the loaded code
    bool optimize();
    
    // Save the optimized code to a file
    bool saveOptimizedCode(const std::string& filename);

private:
    std::string sourceCode;
    std::shared_ptr<FunctionDefinition> ast;
    
    // Helper methods for optimization
    void constantFolding();
    void deadCodeElimination();
    void optimizeArithmetic();
}; 