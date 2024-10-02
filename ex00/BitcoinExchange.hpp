#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

class BitcoinExchange {
private:
  std::string _filename;
  std::map<std::string, float> m_bitcoinPrices;

public:
  BitcoinExchange();
  BitcoinExchange(const std::string filename);
  BitcoinExchange(const BitcoinExchange &copy);
  BitcoinExchange &operator=(const BitcoinExchange &copy);
  ~BitcoinExchange();

  std::map<std::string, float> getBalances(void) const;

  std::ifstream verifyFile(const std::string &filename);
  bool getFullYear(const std::string &str);
  bool isPositive(const std::string &str);
  bool checkRange(const std::string &str);
  const float calculateBalance(const std::string &key,
                               const std::string &value);
  void handlePricesFile();
  void handleAmountsFile();

  class InvalidFile : public std::exception {
  public:
    virtual const char *what() const throw();
  };
};

#endif // !BITCOINEXCHANGE_HPP
