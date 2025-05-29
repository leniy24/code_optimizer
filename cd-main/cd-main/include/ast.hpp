#pragma once

#include <string>
#include <vector>
#include <memory>
#include <variant>
#include <iostream>

// Forward declarations
class ASTNode;
class Expression;
class Statement;
class VariableDeclaration;
class BinaryOperation;
class Constant;
class ReturnStatement;
class VariableReference;

// Type aliases for better readability
using ASTNodePtr = std::shared_ptr<ASTNode>;
using ExpressionPtr = std::shared_ptr<Expression>;
using StatementPtr = std::shared_ptr<Statement>;

// Base class for all AST nodes
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual std::string toString() const = 0;
};

// Base class for expressions
class Expression : public ASTNode {
public:
    virtual bool isConstant() const { return false; }
    virtual int evaluate() const { return 0; }
    virtual void optimize() {}
};

// Base class for statements
class Statement : public ASTNode {
public:
    virtual void optimize() = 0;
};

// Variable reference node
class VariableReference : public Expression {
public:
    std::string name;

    explicit VariableReference(const std::string& name) : name(name) {}

    std::string toString() const override {
        return name;
    }
};

// Variable declaration node
class VariableDeclaration : public Statement {
public:
    std::string name;
    ExpressionPtr initializer;

    VariableDeclaration(const std::string& name, ExpressionPtr initializer)
        : name(name), initializer(std::move(initializer)) {}

    std::string toString() const override {
        return "int " + name + " = " + initializer->toString() + ";";
    }

    void optimize() override {
        if (initializer) {
            initializer->optimize();
        }
    }
};

// Constant node
class Constant : public Expression {
public:
    int value;

    explicit Constant(int value) : value(value) {}

    std::string toString() const override {
        return std::to_string(value);
    }

    bool isConstant() const override { return true; }
    int evaluate() const override { return value; }
};

// Binary operation node
class BinaryOperation : public Expression {
public:
    enum class Operation {
        Add, Subtract, Multiply, Divide
    };

    Operation op;
    ExpressionPtr left;
    ExpressionPtr right;

    BinaryOperation(Operation op, ExpressionPtr left, ExpressionPtr right)
        : op(op), left(std::move(left)), right(std::move(right)) {}

    std::string toString() const override {
        if (!right) {
            return left->toString();
        }
        std::string opStr;
        switch (op) {
            case Operation::Add: opStr = "+"; break;
            case Operation::Subtract: opStr = "-"; break;
            case Operation::Multiply: opStr = "*"; break;
            case Operation::Divide: opStr = "/"; break;
        }
        return "(" + left->toString() + " " + opStr + " " + right->toString() + ")";
    }

    bool isConstant() const override {
        if (!right) {
            return left->isConstant();
        }
        return left->isConstant() && right->isConstant();
    }

    int evaluate() const override {
        if (!right) {
            return left->evaluate();
        }
        int leftVal = left->evaluate();
        int rightVal = right->evaluate();
        
        switch (op) {
            case Operation::Add: return leftVal + rightVal;
            case Operation::Subtract: return leftVal - rightVal;
            case Operation::Multiply: return leftVal * rightVal;
            case Operation::Divide: return rightVal != 0 ? leftVal / rightVal : 0;
        }
        return 0;
    }

    void optimize() override {
        // First optimize the children
        if (left) {
            left->optimize();
        }
        if (right) {
            right->optimize();
        }

        // Then try to fold constants
        if (isConstant()) {
            int result = evaluate();
            auto constant = std::make_shared<Constant>(result);
            left = std::static_pointer_cast<Expression>(constant);
            right = nullptr;
        }
    }
};

// Return statement node
class ReturnStatement : public Statement {
public:
    ExpressionPtr expression;

    explicit ReturnStatement(ExpressionPtr expression)
        : expression(std::move(expression)) {}

    std::string toString() const override {
        return "return " + (expression ? expression->toString() : "") + ";";
    }

    void optimize() override {
        if (expression) {
            expression->optimize();
        }
    }
};

// Function definition node
class FunctionDefinition : public ASTNode {
public:
    std::string name;
    std::vector<StatementPtr> body;

    FunctionDefinition(const std::string& name, std::vector<StatementPtr> body)
        : name(name), body(std::move(body)) {}

    std::string toString() const override {
        std::string result = "int " + name + "() {\n";
        for (const auto& stmt : body) {
            result += "    " + stmt->toString() + "\n";
        }
        result += "}";
        return result;
    }

    void optimize() {
        for (auto& stmt : body) {
            stmt->optimize();
        }
    }
};
