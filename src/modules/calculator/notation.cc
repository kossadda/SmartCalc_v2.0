/**
 * @file notation.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief 
 * @version 1.0
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "./notation.h"

PolishNotation::PolishNotation(std::string infix) : infix_{infix}, size_{infix_.size()} {
  if(validate()) {
    infixToPostfix();
  } else {
    throw std::invalid_argument("PolishNotation: invalid infix expression");
  }
}

void PolishNotation::replaceSubStr(std::string from, std::string to) {
  size_t start_pos = 0;

  while ((start_pos = infix_.find(from, start_pos)) != std::string::npos) {
    infix_.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }
}

bool PolishNotation::validate() {
  replaceSubStr(std::string{"asin("}, std::string{"S("});
  replaceSubStr(std::string{"acos("}, std::string{"C("});
  replaceSubStr(std::string{"atan("}, std::string{"T("});
  replaceSubStr(std::string{"sqrt("}, std::string{"Q("});
  replaceSubStr(std::string{"sin("}, std::string{"s("});
  replaceSubStr(std::string{"cos("}, std::string{"c("});
  replaceSubStr(std::string{"tan("}, std::string{"t("});
  replaceSubStr(std::string{"log("}, std::string{"L("});
  replaceSubStr(std::string{"mod("}, std::string{"m("});
  replaceSubStr(std::string{"ln("}, std::string{"l("});

  bool valid = true;

  for(auto i : infix_) {
    if(kValidCh.find(i) == std::string::npos) {
      valid = false;
    }
  }

  return valid;
}

void PolishNotation::infixToPostfix() {
  std::stack<char> ops;
  size_ = infix_.size();

  for (std::size_t i{}; i < size_; ++i) {
    char c = infix_[i];
    if (isspace(c)) {
      continue;
    } else if (isdigit(c)) {
      std::string num;

      while (i < size_ && (isdigit(infix_[i]) || infix_[i] == '.')) {
        num += infix_[i];
        ++i;
      }

      postfix_ += num + ' ';
      --i;
    } else if (c == '(') {
      ops.push(c);
    } else if (c == ')') {
      while (!ops.empty() && ops.top() != '(') {
        postfix_ += ops.top();
        postfix_ += ' ';
        ops.pop();
      }

      ops.pop();
    } else if (isOperator(c)) {
      while (!ops.empty() && getPrecedence(ops.top()) >= getPrecedence(c)) {
        postfix_ += ops.top();
        postfix_ += ' ';
        ops.pop();
      }

      ops.push(c);
    }
  }

  while (!ops.empty()) {
    postfix_ += ops.top();
    postfix_ += ' ';
    ops.pop();
  }
}

double PolishNotation::evaluate() {
  std::stack<double> operands;
  std::istringstream iss(postfix_);
  std::string token;

  while (iss >> token) {
    if (isdigit(token[0]) || (token[0] == '.' && token.size() > 1 && isdigit(token[1]))) {
      operands.push(std::stof(token));
    } else if (isOperator(token[0])) {
      double right = operands.top();
      operands.pop();
      double left = operands.top();
      operands.pop();

      double result;
      switch (token[0]) {
        case '+':
          result = left + right;
          break;
        case '-':
          result = left - right;
          break;
        case '*':
          result = left * right;
          break;
        case '/':
          result = left / right;
          break;
      }

      operands.push(result);
    }
  }

  return operands.top();
}

int PolishNotation::getPrecedence(char op) {
  int priority = 0;

  if (op == '+' || op == '-') {
    priority = 1;
  } else if (op == '*' || op == '/') {
    priority = 2;
  }

  return priority;
}

bool PolishNotation::isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

bool PolishNotation::isFunction(char c) {
  return c == 's' || c == 'c' || c == 't' || c == 'S' || c == 'C' || c == 'T';
}

