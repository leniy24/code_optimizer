#pragma once

#include "ast.hpp"
#include "parser.hpp"
#include <string>
#include <memory>

class CodeOptimizer {
public:
    CodeOptimizer();
    ~CodeOptimizer() = default;

    bool loadCode(const std::string& filename);
    bool optimize();
    bool saveOptimizedCode(const std::string& filename);

private:
    std::string sourceCode;
    std::shared_ptr<FunctionDefinition> ast;
    
    void constantFolding();
    void deadCodeElimination();
    void optimizeArithmetic();
};