#include "RPN.hpp"

RPN::RPN() {};

RPN::RPN(const RPN &copy) : _stack(copy._stack) {};

RPN &RPN::operator=(const RPN &copy) {
  if (this != &copy) {
    _stack = copy._stack;
  }
  return *this;
}

RPN::~RPN() {};

int RPN::rpnOperation(const std::string &str) {
  for (size_t i = 0; i < str.size(); i++) {
    if (str[i] == ' ')
      continue;
    if (isdigit(str[i])) {
      long number = std::stol(&str[i]);
      if (number > 9 || number < 0)
        throw RPN::RPNException();
      _stack.push(std::stoi(&str[i]));
    } else if (str[i] == '+' || str[i] == '-' || str[i] == '*' ||
               str[i] == '/') {
      if (_stack.size() < 2)
        throw RPN::RPNException();
      int a = _stack.top();
      _stack.pop();
      int b = _stack.top();
      _stack.pop();
      _stack.push(arithmeticOperation(a, b, str[i]));
    } else
      throw RPN::RPNException();
  }
  if (_stack.size() != 1)
    throw RPN::RPNException();
  return _stack.top();
}

int RPN::arithmeticOperation(const int a, const int b, const char op) {
  switch (op) {
  case '+':
    return a + b;
  case '-':
    return b - a;
  case '*':
    return a * b;
  case '/':
    if (a == 0)
      throw RPN::RPNException();
    return b / a;
  default:
    throw RPN::RPNException();
  }
}

const char *RPN::RPNException::what() const throw() {
  return "Error: invalide input";
}
