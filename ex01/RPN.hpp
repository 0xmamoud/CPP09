#ifndef RPN_HPP
#define RPN_HPP

#include <exception>
#include <stack>
#include <string>

class RPN {
private:
  std::stack<int> _stack;

public:
  RPN();
  RPN(const RPN &copy);
  RPN &operator=(const RPN &copy);
  ~RPN();

  int rpnOperation(const std::string &str);
  int arithmeticOperation(const int a, const int b, const char op);

  class RPNException : public std::exception {
  public:
    virtual const char *what() const throw();
  };
};

#endif // !RPN_HPP
