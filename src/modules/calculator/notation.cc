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

Polish::Polish(std::string infix) : infix_{infix}, size_{infix_.size()} {
  if(validate()) {
    infixToPostfix();
  } else {
    throw std::invalid_argument("Polish: invalid infix expression");
  }
}

void Polish::replaceSubStr(std::string from, std::string to) {
  size_t start_pos = 0;

  while ((start_pos = infix_.find(from, start_pos)) != std::string::npos) {
    infix_.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }
}

bool Polish::validate() {
  replaceSubStr(std::string{"asin("}, std::string{"S("});
  replaceSubStr(std::string{"acos("}, std::string{"C("});
  replaceSubStr(std::string{"atan("}, std::string{"T("});
  replaceSubStr(std::string{"sqrt("}, std::string{"Q("});
  replaceSubStr(std::string{"sin("}, std::string{"s("});
  replaceSubStr(std::string{"cos("}, std::string{"c("});
  replaceSubStr(std::string{"tan("}, std::string{"t("});
  replaceSubStr(std::string{"log("}, std::string{"L("});
  replaceSubStr(std::string{"ln("}, std::string{"l("});
  replaceSubStr(std::string{"mod"}, std::string{"m"});

  bool valid = true;

  for(auto i : infix_) {
    if(kValidCh.find(i) == std::string::npos) {
      valid = false;
    }
  }

  return valid;
}

void Polish::infixToPostfix() {
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

      if(!ops.empty() && isFunction(ops.top())) {
        postfix_ += ops.top();
        postfix_ += ' ';
      }

      ops.pop();
    } else if (isOperator(c) || isFunction(c)) {
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

long double Polish::evaluate() {
  std::stack<long double> operands;
  std::istringstream iss(postfix_);
  std::string token;

  while (iss >> token) {
    if (isdigit(token[0]) || (token[0] == '.' && token.size() > 1 && isdigit(token[1]))) {
      operands.push(std::stof(token));
    } else if (isOperator(token[0])) {
      long double right = operands.top();
      operands.pop();
      long double left = operands.top();
      operands.pop();

      long double result;
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
        case 'm':
          result = std::fmod(left, right);
          break;
        case '^':
          result = std::pow(left, right);
          break;
      }

      operands.push(result);
    } else if (isFunction(token[0])) {
      long double top = operands.top();
      operands.pop();

      long double result;
      switch (token[0]) {
        case 's':
          result = std::sin(top);
          break;
        case 'c':
          result = std::cos(top);
          break;
        case 't':
          result = std::tan(top);
          break;
        case 'S':
          result = std::asin(top);
          break;
        case 'C':
          result = std::acos(top);
          break;
        case 'T':
          result = std::atan(top);
          break;
        case 'l':
          result = std::log(top);
          break;
        case 'L':
          result = std::log10(top);
          break;
        case 'Q':
          result = std::sqrt(top);
          break;
      }

      operands.push(result);
    }
  }

  return operands.top();
}

int Polish::getPrecedence(char op) {
  int priority = 0;

  if (op == '+' || op == '-') {
    priority = 1;
  } else if (op == '*' || op == '/' || op == 'm') {
    priority = 2;
  } else if (op == '^') {
    priority = 3;
  } else if (op == 's' || op == 'c' || op == 't' || op == 'S' || op == 'C' || op == 'T' || op == 'l' || op == 'L' || op == 'Q') {
    priority = 4;
  }

  return priority;
}

bool Polish::isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == 'm';
}

bool Polish::isFunction(char c) {
  return c == 's' || c == 'c' || c == 't' || c == 'S' || c == 'C' || c == 'T' || c == 'l' || c == 'L' || c == 'Q';
}

