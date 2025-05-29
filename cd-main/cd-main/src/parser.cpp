#include "parser.hpp"
#include <stdexcept>
#include <iostream>

char Parser::peek() const {
    return pos < source.length() ? source[pos] : '\0';
}

char Parser::advance() {
    return pos < source.length() ? source[pos++] : '\0';
}

void Parser::skipWhitespace() {
    while (peek() == ' ' || peek() == '\t' || peek() == '\n' || peek() == '\r') {
        advance();
    }
}

bool Parser::match(char expected) {
    if (peek() == expected) {
        advance();
        return true;
    }
    return false;
}

bool Parser::isDigit(char c) const {
    return c >= '0' && c <= '9';
}

bool Parser::isAlpha(char c) const {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Parser::isAlphaNumeric(char c) const {
    return isAlpha(c) || isDigit(c);
}

std::string Parser::parseIdentifier() {
    std::string result;
    while (isAlphaNumeric(peek())) {
        result += advance();
    }
    return result;
}

int Parser::parseNumber() {
    int result = 0;
    while (isDigit(peek())) {
        result = result * 10 + (advance() - '0');
    }
    return result;
}

ExpressionPtr Parser::parseFactor() {
    skipWhitespace();
    if (isDigit(peek())) {
        return std::make_shared<Constant>(parseNumber());
    } else if (peek() == '(') {
        advance();
        auto expr = parseExpression();
        if (!match(')')) {
            throw std::runtime_error("Expected ')'");
        }
        return expr;
    } else if (isAlpha(peek())) {
        return std::make_shared<VariableReference>(parseIdentifier());
    }
    throw std::runtime_error("Unexpected token in factor: " + std::string(1, peek()));
}

ExpressionPtr Parser::parseTerm() {
    auto left = parseFactor();
    skipWhitespace();
    
    while (peek() == '*' || peek() == '/') {
        char op = advance();
        auto right = parseFactor();
        if (op == '*') {
            left = std::make_shared<BinaryOperation>(BinaryOperation::Operation::Multiply, left, right);
        } else {
            left = std::make_shared<BinaryOperation>(BinaryOperation::Operation::Divide, left, right);
        }
        skipWhitespace();
    }
    
    return left;
}

ExpressionPtr Parser::parseExpression() {
    auto left = parseTerm();
    skipWhitespace();
    
    while (peek() == '+' || peek() == '-') {
        char op = advance();
        auto right = parseTerm();
        if (op == '+') {
            left = std::make_shared<BinaryOperation>(BinaryOperation::Operation::Add, left, right);
        } else {
            left = std::make_shared<BinaryOperation>(BinaryOperation::Operation::Subtract, left, right);
        }
        skipWhitespace();
    }
    
    return left;
}

StatementPtr Parser::parseStatement() {
    skipWhitespace();
    
    if (source.substr(pos, 3) == "int") {
        pos += 3;
        skipWhitespace();
        std::string name = parseIdentifier();
        skipWhitespace();
        if (!match('=')) {
            throw std::runtime_error("Expected '=' after variable declaration");
        }
        auto expr = parseExpression();
        if (!match(';')) {
            throw std::runtime_error("Expected ';' after expression");
        }
        return std::make_shared<VariableDeclaration>(name, expr);
    } else if (source.substr(pos, 6) == "return") {
        pos += 6;
        skipWhitespace();
        auto expr = parseExpression();
        if (!match(';')) {
            throw std::runtime_error("Expected ';' after return statement");
        }
        return std::make_shared<ReturnStatement>(expr);
    }
    
    throw std::runtime_error("Unexpected statement: " + source.substr(pos, 10));
}

std::shared_ptr<FunctionDefinition> Parser::parseFunction() {
    skipWhitespace();
    if (source.substr(pos, 3) != "int") {
        throw std::runtime_error("Expected 'int' at start of function");
    }
    pos += 3;
    skipWhitespace();
    
    std::string name = parseIdentifier();
    skipWhitespace();
    
    if (!match('(') || !match(')')) {
        throw std::runtime_error("Expected '()' after function name");
    }
    skipWhitespace();
    
    if (!match('{')) {
        throw std::runtime_error("Expected '{' after function declaration");
    }
    
    std::vector<StatementPtr> body;
    while (peek() != '}') {
        body.push_back(parseStatement());
        skipWhitespace();
    }
    
    if (!match('}')) {
        throw std::runtime_error("Expected '}' at end of function");
    }
    
    return std::make_shared<FunctionDefinition>(name, body);
} 