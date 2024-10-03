#include "PmergeMe.hpp"
#include <iostream>
#include <utility>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &copy) { *this = copy; }

PmergeMe &PmergeMe::operator=(const PmergeMe &copy) {
  if (this != &copy) {
    this->_list = copy._list;
    this->_vec = copy._vec;
  }
  return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::sortVec(std::vector<int> &v) {

  int number = -1;
  if (v.size() % 2) {
    number = v.back();
    v.pop_back();
  }

  std::vector<std::pair<int, int>> pairs;
  for (int i = 0; i < v.size(); i += 2) {
    pairs.push_back(std::make_pair(v[i], v[i + 1]));
  }

  for (int i = 0; i < pairs.size(); i++) {
    if (pairs[i].first > pairs[i].second) {
      std::swap(pairs[i].first, pairs[i].second);
    }
  }

  for (int i = 0; i < pairs.size(); i++) {
    for (int j = i + 1; j < pairs.size(); j++) {
      if (pairs[i].second > pairs[j].second) {
        std::swap(pairs[i], pairs[j]);
      }
    }
  }

  this->setVec(pairs);
  if (number != -1) {
    auto it = std::lower_bound(this->_vec.begin(), this->_vec.end(), number);
    this->_vec.insert(it, number);
  }
}

void PmergeMe::setVec(const std::vector<std::pair<int, int>> &vec) {

  for (int i = 0; i < vec.size(); i++) {
    if (i == 0) {
      this->_vec.push_back(vec[i].first);
      this->_vec.push_back(vec[i].second);
    } else {
      this->_vec.push_back(vec[i].second);
    }
  };

  for (int i = 1; i < vec.size(); i++) {
    auto it =
        std::lower_bound(this->_vec.begin(), this->_vec.end(), vec[i].first);
    this->_vec.insert(it, vec[i].first);
  };
}

void PmergeMe::printVec() {
  for (int i = 0; i < this->_vec.size(); i++) {
    std::cout << this->_vec[i] << " ";
  }
  std::cout << std::endl;
}

void PmergeMe::sortList(std::list<int> &l) {

  int number = -1;
  if (l.size() % 2) {
    number = l.back();
    l.pop_back();
  }

  std::list<std::pair<int, int>> pairs;
  for (auto it = l.begin(); it != l.end(); it++) {
    pairs.push_back(std::make_pair(*it, *(++it)));
  }

  for (auto it = pairs.begin(); it != pairs.end(); it++) {
    if (it->first > it->second) {
      std::swap(it->first, it->second);
    }
  }

  for (auto it = pairs.begin(); it != pairs.end(); it++) {
    for (auto it2 = it; it2 != pairs.end(); it2++) {
      if (it->second > it2->second) {
        std::swap(*it, *it2);
      }
    }
  }

  this->setList(pairs);
  if (number != -1) {
    auto it = std::lower_bound(this->_list.begin(), this->_list.end(), number);
    this->_list.insert(it, number);
  }
}

void PmergeMe::setList(const std::list<std::pair<int, int>> &list) {

  for (auto it = list.begin(); it != list.end(); it++) {
    if (it == list.begin()) {
      this->_list.push_back(it->first);
      this->_list.push_back(it->second);
    } else {
      this->_list.push_back(it->second);
    }
  };

  for (auto it = ++list.begin(); it != list.end(); it++) {
    auto it2 =
        std::lower_bound(this->_list.begin(), this->_list.end(), it->first);
    this->_list.insert(it2, it->first);
  };
}
