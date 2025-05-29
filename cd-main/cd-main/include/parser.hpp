#pragma once

#include "ast.hpp"
#include <string>
#include <vector>
#include <memory>

class Parser {
public:
    Parser(const std::string& source) : source(source), pos(0) {}

    std::shared_ptr<FunctionDefinition> parseFunction();
    StatementPtr parseStatement();
    ExpressionPtr parseExpression();
    ExpressionPtr parseTerm();
    ExpressionPtr parseFactor();

private:
    std::string source;
    size_t pos;

    char peek() const;
    char advance();
    void skipWhitespace();
    bool match(char expected);
    bool isDigit(char c) const;
    bool isAlpha(char c) const;
    bool isAlphaNumeric(char c) const;
    std::string parseIdentifier();
    int parseNumber();
}; 