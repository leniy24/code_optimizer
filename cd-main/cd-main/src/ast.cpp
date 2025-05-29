#include "ast.hpp"
#include <iostream>

void ASTNode::print(int indent) {
    for (int i = 0; i < indent; ++i) std::cout << "  ";
    std::cout << type << ": " << value << std::endl;
    for (ASTNode* child : children) {
        child->print(indent + 1);
    }
}