#include "BitcoinExchange.hpp"
#include <fstream>

BitcoinExchange::BitcoinExchange() : _filename("") {}

BitcoinExchange::BitcoinExchange(const std::string filename)
    : _filename(filename) {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) { *this = copy; }

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy) {
  if (this != &copy) {
    this->_filename = copy._filename;
    this->m_bitcoinPrices = copy.m_bitcoinPrices;
  }
  return *this;
}

BitcoinExchange::~BitcoinExchange() {}

const char *BitcoinExchange::InvalidFile::what() const throw() {
  return "Error: could not open file";
}

void BitcoinExchange::handlePricesFile() {
  std::ifstream pricesFile = verifyFile("data.csv");
  std::string line;
  getline(pricesFile, line);
  while (std::getline(pricesFile, line)) {
    std::string key = line.substr(0, line.find(","));
    std::string value = line.substr(line.find(",") + 1);
    this->m_bitcoinPrices[key] = std::stof(value);
  }
  pricesFile.close();
}

void BitcoinExchange::handleAmountsFile() {
  std::ifstream amountsFile = verifyFile(this->_filename);
  std::string line;
  getline(amountsFile, line);
  while (std::getline(amountsFile, line)) {
    if (!getFullYear(line))
      std::cout << "Error: bad input " << line << std::endl;
    else if (!isPositive(line))
      std::cout << "Error: not a positive number." << std::endl;
    else if (!checkRange(line))
      std::cout << "Error: too large a number." << std::endl;
    else {
      std::string key = line.substr(0, line.find("|"));
      if (!key.empty() && key.back() == ' ')
        key.pop_back();
      std::string value = line.substr(line.find("|") + 2);
      const float totalPrice =
          calculateBalance(key, line.substr(line.find("|") + 1));
      std::cout << key << " => " << value << " = " << totalPrice << std::endl;
    }
  }
  amountsFile.close();
}

std::ifstream BitcoinExchange::verifyFile(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open())
    throw BitcoinExchange::InvalidFile();
  return file;
}

bool BitcoinExchange::getFullYear(const std::string &str) {
  size_t pos = str.find("|");
  if (pos == std::string::npos)
    return false;

  std::string key = str.substr(0, pos);
  size_t yearpos = key.find("-");
  std::string year = key.substr(0, yearpos);
  if (std::stoi(year) < 2009)
    return false;

  size_t monthpos = key.find("-", yearpos + 1);
  std::string month = key.substr(yearpos + 1, monthpos - (yearpos + 1));
  if (std::stoi(month) < 1 || std::stoi(month) > 12)
    return false;

  std::string day = key.substr(monthpos + 1);
  if (std::stoi(day) < 1 || std::stoi(day) > 31)
    return false;
  return true;
}

bool BitcoinExchange::isPositive(const std::string &str) {
  std::string value = str.substr(str.find("|") + 1);
  if (std::stof(value) < 0)
    return false;

  return true;
}

bool BitcoinExchange::checkRange(const std::string &str) {
  std::string value = str.substr(str.find("|") + 1);
  if (std::stol(value) > 1000)
    return false;

  return true;
}

const float BitcoinExchange::calculateBalance(const std::string &key,
                                              const std::string &value) {

  std::map<std::string, float>::iterator it =
      this->m_bitcoinPrices.lower_bound(key);

  if (it->first != key)
    --it;

  const float amount = std::stof(value);
  return it->second * amount;
}
