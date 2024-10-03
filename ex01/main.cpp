#include "RPN.hpp"
#include <iostream>

int main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <RPN expression>" << std::endl;
    exit(EXIT_FAILURE);
  }

  try {
    RPN rpn;
    std::cout << rpn.rpnOperation(argv[1]) << std::endl;

  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }

  return 0;
}
