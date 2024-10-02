#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Error: could not open file" << std::endl;
  }

  try {
    BitcoinExchange exchange(argv[1]);
    exchange.handlePricesFile();
    exchange.handleAmountsFile();
  } catch (BitcoinExchange::InvalidFile &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
