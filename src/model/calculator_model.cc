/**
 * @file calculator_model.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief Implementation of the CalculatorModel class.
 * @version 1.0
 * @date 2024-08-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "include/model/calculator_model.h"

namespace s21 {

/**
 * @brief Adds an expression to the calculator model.
 * @param infix The infix expression.
 * @param var The variable value.
 */
void CalculatorModel::add_expression(std::string infix,
                                     long double var) noexcept {
  variable_ = var;
  postfix_ = std::string{};
  infix_ = replaceNames(infix);
}

/**
 * @brief Returns a reference to the variable value.
 * @return A reference to the variable value.
 */
long double &CalculatorModel::variable() noexcept { return variable_; }

/// @brief Converts the infix expression to postfix notation.
void CalculatorModel::to_postfix() noexcept {
  std::stack<char> ops;
  size_ = infix_.size();

  for (std::size_t i{}; i < size_; ++i) {
    char c = infix_[i];

    if (isdigit(c) || c == 'x') {
      std::string num;

      bool science{false};
      while (i < size_ &&
             (isdigit(infix_[i]) || infix_[i] == '.' || infix_[i] == 'e' ||
              (science && (infix_[i] == '+' || infix_[i] == '-')) ||
              infix_[i] == 'x')) {
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
      while (!ops.empty() &&
             ((c != '^' && getPrecedence(ops.top()) >= getPrecedence(c)) ||
              (c == '^' && getPrecedence(ops.top()) > getPrecedence(c)))) {
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

/**
 * @brief Validates the infix expression.
 * @return True if the expression is valid, false otherwise.
 */
bool CalculatorModel::validate() const noexcept {
  const std::string valid_chars{"()^+-*/msctSCTQLlPxe1234567890."};
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
    } else if (isOperator(ch) &&
               (isOperator(infix_[i + 1]) || infix_[i + 1] == ')')) {
      valid = false;
    } else if (close_br > open_br) {
      valid = false;
    } else if (isFunction(ch) && ch != 'P') {
      if (infix_[i + 1] != '(') {
        valid = false;
      }
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

/**
 * @brief Evaluates the postfix expression.
 * @return The result of the evaluation.
 */
long double CalculatorModel::evaluate() {
  std::stack<long double> operands;
  std::istringstream iss{postfix_};
  std::string token;

  while (iss >> token) {
    if (isdigit(token[0]) ||
        (token[0] == '.' && token.size() && isdigit(token[1])) ||
        token == "x") {
      if (token == "x") {
        operands.push(variable_);
      } else {
        operands.push(std::stold(token));
      }
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

      operands.push((std::fabs(left) > kLdoubleMinVal) ? left : 0.0L);
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
        case 'P':
          top *= -1.0L;
      }

      operands.push((std::fabs(top) > kLdoubleMinVal) ? top : 0.0L);
    }
  }

  return operands.top();
}

/**
 * @brief Evaluates the postfix expression and returns the result as a string.
 * @return The result of the evaluation as a string.
 */
std::string CalculatorModel::evaluate_str() {
  std::ostringstream stream;
  long double result{evaluate()};
  stream << std::fixed << std::setprecision(7) << result;
  std::string result_str{stream.str()};

  while (result_str.back() == '0' || result_str.back() == '.') {
    result_str.pop_back();
  }

  return result_str;
}

/**
 * @brief Replaces substrings in the given string.
 * @param str The input string.
 * @param from The substring to replace.
 * @param to The substring to replace with.
 * @return The modified string.
 */
std::string CalculatorModel::replaceSubstr(std::string str, const char *from,
                                           const char *to) const {
  std::string from_{from};
  std::string to_{to};
  size_t start_pos{};

  while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from_.length(), to);
    start_pos += to_.length();
  }

  return str;
}

/**
 * @brief Replaces variable names in the infix expression.
 * @param infix The infix expression.
 * @return The modified infix expression.
 */
std::string CalculatorModel::replaceNames(std::string infix) const noexcept {
  std::string result;

  for (auto i : infix) {
    if (i != ' ') result += i;
  }

  result = replaceSubstr(result, "π", "P");

  std::regex number_x_pattern{"(\\d+)x"};
  result = std::regex_replace(result, number_x_pattern, "$1*x");

  std::regex x_number_pattern{"x(\\d+)"};
  result = std::regex_replace(result, x_number_pattern, "x*$1");

  std::regex number_e_pattern{"(\\d+)e(\\d+|[+-])"};
  result = std::regex_replace(result, number_e_pattern, "$1E$2");

  result = replaceSubstr(result, "x", "(x)");
  result = replaceSubstr(result, "P", "(3.1415926535897932384626433)");

  if (result[0] == '-') {
    result[0] = 'P';
  }

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
  result = replaceSubstr(result, "(-", "((P1)*");

  std::regex digit_bracket{"(\\d)\\("};
  result = std::regex_replace(result, digit_bracket, "$1*(");

  std::regex bracket_digit{"\\)(\\d)"};
  result = std::regex_replace(result, bracket_digit, ")*$1");

  result = replaceSubstr(result, "e", "(2.7182818284590452353671352)");
  result = replaceSubstr(result, "E", "e");

  for (std::size_t i{}; i != result.size(); ++i) {
    if (isdigit(result[i]) && isFunction(result[i + 1]) && result[i] != 'P') {
      result.insert(++i, "*");
    }
  }

  return result;
}

/**
 * @brief Gets the precedence of an operator.
 * @param op The operator.
 * @return The precedence of the operator.
 */
int CalculatorModel::getPrecedence(char op) {
  int priority{};

  if (op == '+' || op == '-') {
    priority = 1;
  } else if (op == '*' || op == '/' || op == 'm') {
    priority = 2;
  } else if (op == '^') {
    priority = 3;
  } else if (op == 's' || op == 'c' || op == 't' || op == 'S' || op == 'C' ||
             op == 'T' || op == 'l' || op == 'L' || op == 'Q' || op == 'P') {
    priority = 4;
  }

  return priority;
}

/**
 * @brief Checks if a character is an operator.
 * @param c The character to check.
 * @return True if the character is an operator, false otherwise.
 */
bool CalculatorModel::isOperator(char c) const noexcept {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == 'm';
}

/**
 * @brief Checks if a character is a function.
 * @param c The character to check.
 * @return True if the character is a function, false otherwise.
 */
bool CalculatorModel::isFunction(char c) const noexcept {
  return c == 's' || c == 'c' || c == 't' || c == 'S' || c == 'C' || c == 'T' ||
         c == 'l' || c == 'L' || c == 'Q' || c == 'P';
}

}  // namespace s21
