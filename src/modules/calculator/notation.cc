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

Polish::Polish(std::string infix) {
  for (auto i : infix) {
    if (i != ' ') {
      infix_ += i;
    }
  }

  if (validate()) {
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
  if (infix_[0] == '-') {
    infix_[0] = 'u';
  }

  // replaceSubStr(std::string{"e"}, std::string{"(2.7182818284590452)"});
  replaceSubStr(std::string{"P"}, std::string{"(3.1415926535897932)"});
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
  replaceSubStr(std::string{")("}, std::string{")*("});
  replaceSubStr(std::string{"(+"}, std::string{"("});
  replaceSubStr(std::string{"(-"}, std::string{"(u"});

  // std::regex digit_function("(\\d)(\\w\\()");
  // infix_ = std::regex_replace(infix_, digit_function, "$1*$2");

  std::regex digit_bracket("(\\d)\\(");
  infix_ = std::regex_replace(infix_, digit_bracket, "$1*(");

  bool valid = true;

  for (auto i : infix_) {
    if (kValidCh.find(i) == std::string::npos) {
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

long double Polish::evaluate() {
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
          left /= right;
          break;
        case 'm':
          left = std::fmod(left, right);

          if (left < 0) {
            left += right;
          }
          break;
        case '^':
          left = std::pow(left, right);
          break;
      }

      operands.push((std::fabs(left) > 1.0e-15) ? left : 0);
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
          top = std::asin(top);
          break;
        case 'C':
          top = std::acos(top);
          break;
        case 'T':
          top = std::atan(top);
          break;
        case 'l':
          top = std::log(top);

          // if(top < 0)
          //   throw std::invalid_argument("log: negative number");

          break;
        case 'L':
          top = std::log10(top);

          // if(top < 0)
          //   throw std::invalid_argument("log: negative number");

          break;
        case 'Q':
          top = std::sqrt(top);
          break;
        case 'u':
          top *= -1.0L;
      }

      operands.push((std::fabs(top) > 1.0e-15) ? top : 0);
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
  } else if (op == 's' || op == 'c' || op == 't' || op == 'S' || op == 'C' ||
             op == 'T' || op == 'l' || op == 'L' || op == 'Q' || op == 'u') {
    priority = 4;
  }

  return priority;
}

bool Polish::isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == 'm';
}

bool Polish::isFunction(char c) {
  return c == 's' || c == 'c' || c == 't' || c == 'S' || c == 'C' || c == 'T' ||
         c == 'l' || c == 'L' || c == 'Q' || c == 'u';
}
