/**
 * @file calculator_model.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-08-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/calculator_model.h"

CalculatorModel::CalculatorModel(std::string infix, long double var) {
  add_expression(infix, var);
  to_postfix();
}

void CalculatorModel::add_expression(std::string infix, long double var) {
  variable_ = var;
  postfix_ = std::string{};
  infix_ = replaceNames(infix);
}

void CalculatorModel::to_postfix() {
  std::stack<char> ops;
  size_ = infix_.size();

  for (std::size_t i{}; i < size_; ++i) {
    char c = infix_[i];

    if (isdigit(c)) {
      std::string num;

      bool science{false};
      while (i < size_ &&
             (isdigit(infix_[i]) || infix_[i] == '.' || infix_[i] == 'e' ||
              (science && (infix_[i] == '+' || infix_[i] == '-')))) {
        num += infix_[i];
        ++i;

        if (i < size_ && infix_[i] == 'e') {
          science = true;
        }
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

      if (!ops.empty() && isFunction(ops.top())) {
        postfix_ += ops.top();
        postfix_ += ' ';
      }

      if (ops.size()) {
        ops.pop();
      }
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

bool CalculatorModel::validate() {
  const std::string valid_chars{"()^+-*/umsctSCTQLlPxe1234567890."};
  std::size_t open_br{};
  std::size_t close_br{};
  bool valid{(infix_.size()) ? true : false};
  bool in_number{false};
  std::size_t dot_count{};
  char ch;

  for (std::size_t i = 0; i < infix_.size() && valid; ++i) {
    ch = infix_[i];

    if (ch == '(') {
      ++open_br;
    } else if (ch == ')') {
      ++close_br;
    }

    if (valid_chars.find(infix_[i]) == std::string::npos) {
      valid = false;
    } else if (isOperator(ch) && i + 1 < infix_.size() &&
               isOperator(infix_[i + 1])) {
      valid = false;
    } else if (close_br > open_br) {
      valid = false;
    }

    if (isdigit(ch) || ch == '.') {
      if (!in_number) {
        in_number = true;
        dot_count = 0;
      }

      if (ch == '.') {
        ++dot_count;

        if (dot_count > 1) {
          valid = false;
        }
      }
    } else {
      in_number = false;
    }
  }

  if (open_br != close_br) {
    valid = false;
  }

  if (infix_.find("()") != std::string::npos) {
    valid = false;
  }

  return valid;
}

long double CalculatorModel::evaluate() {
  std::stack<long double> operands;
  std::istringstream iss{postfix_};
  std::string token;

  while (iss >> token) {
    if (isdigit(token[0]) ||
        (token[0] == '.' && token.size() && isdigit(token[1]))) {
      operands.push(std::stold(token));
    } else if (isOperator(token[0])) {
      long double right = operands.top();
      operands.pop();
      long double left = operands.top();
      operands.pop();

      switch (token[0]) {
        case '+':
          left += right;
          break;
        case '-':
          left -= right;
          break;
        case '*':
          left *= right;
          break;
        case '/':
          if (!right) throw std::invalid_argument("divide to zero");
          left /= right;
          break;
        case 'm':
          left = std::fmod(left, right);
          if (left < 0) left += right;
          break;
        case '^':
          left = std::pow(left, right);
          break;
      }

      operands.push((std::fabs(left) > kLdoubleMinVal) ? left : 0);
    } else if (isFunction(token[0])) {
      long double top = operands.top();
      operands.pop();

      switch (token[0]) {
        case 's':
          top = std::sin(top);
          break;
        case 'c':
          top = std::cos(top);
          break;
        case 't':
          top = std::tan(top);
          break;
        case 'S':
          if (std::fabs(top) > 1.0L)
            throw std::invalid_argument("asin: wrong range");
          top = std::asin(top);
          break;
        case 'C':
          if (std::fabs(top) > 1.0L)
            throw std::invalid_argument("acos: wrong range");
          top = std::acos(top);
          break;
        case 'T':
          top = std::atan(top);
          break;
        case 'l':
          if (top < 0.0L) throw std::invalid_argument("ln: negative number");
          top = std::log(top);
          break;
        case 'L':
          if (top < 0.0L) throw std::invalid_argument("log: negative number");
          top = std::log10(top);
          break;
        case 'Q':
          if (top < 0.0L) throw std::invalid_argument("sqrt: negative number");
          top = std::sqrt(top);
          break;
        case 'u':
          top *= -1.0L;
      }

      operands.push((std::fabs(top) > kLdoubleMinVal) ? top : 0);
    }
  }

  return operands.top();
}

std::string CalculatorModel::replaceSubstr(std::string str, const char *from,
                                           const char *to) {
  std::stringstream ss;
  std::string from_{from};
  std::string to_{to};
  size_t start_pos{};

  while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from_.length(), to);
    start_pos += to_.length();
  }

  ss << str;

  return ss.str();
}

std::string CalculatorModel::replaceNames(std::string infix) {
  std::string result;
  std::size_t max_length{25};
  std::unique_ptr<char[]> var_str{new char[max_length]};
  std::snprintf(var_str.get(), max_length, "(%Lf)", variable_);

  for (auto i : infix) {
    if (i != ' ') result += i;
  }

  if (result[0] == '-') {
    result[0] = 'u';
  }

  std::regex number_x_pattern{"(\\d+)x"};
  result = std::regex_replace(result, number_x_pattern, "$1*x");

  std::regex x_number_pattern{"x(\\d+)"};
  result = std::regex_replace(result, x_number_pattern, "x*$1");

  std::regex number_e_pattern{"(\\d+)e(\\d+|[+-])"};
  result = std::regex_replace(result, number_e_pattern, "$1E$2");

  result = replaceSubstr(result, "x", var_str.get());
  result = replaceSubstr(result, "P", "(3.1415926535897932384626433)");
  result = replaceSubstr(result, "asin(", "S(");
  result = replaceSubstr(result, "acos(", "C(");
  result = replaceSubstr(result, "atan(", "T(");
  result = replaceSubstr(result, "sqrt(", "Q(");
  result = replaceSubstr(result, "sin(", "s(");
  result = replaceSubstr(result, "cos(", "c(");
  result = replaceSubstr(result, "tan(", "t(");
  result = replaceSubstr(result, "log(", "L(");
  result = replaceSubstr(result, "ln(", "l(");
  result = replaceSubstr(result, "mod", "m");
  result = replaceSubstr(result, ")(", ")*(");
  result = replaceSubstr(result, "(+", "(");
  result = replaceSubstr(result, "(-", "((u1)*");

  std::regex digit_bracket{"(\\d)\\("};
  result = std::regex_replace(result, digit_bracket, "$1*(");

  std::regex bracket_digit{"\\)(\\d)"};
  result = std::regex_replace(result, bracket_digit, ")*$1");

  result = replaceSubstr(result, "e", "(2.7182818284590452353671352)");
  result = replaceSubstr(result, "E", "e");

  return result;
}

int CalculatorModel::getPrecedence(char op) {
  int priority{};

  if (op == '+' || op == '-') {
    priority = 1;
  } else if (op == '*' || op == '/' || op == 'm') {
    priority = 2;
  } else if (op == '^') {
    priority = 3;
  } else if (op == 's' || op == 'c' || op == 't' || op == 'S' || op == 'C' ||
             op == 'T' || op == 'l' || op == 'L' || op == 'Q' || op == 'u') {
    priority = 4;
  }

  return priority;
}

bool CalculatorModel::isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == 'm';
}

bool CalculatorModel::isFunction(char c) {
  return c == 's' || c == 'c' || c == 't' || c == 'S' || c == 'C' || c == 'T' ||
         c == 'l' || c == 'L' || c == 'Q' || c == 'u';
}
