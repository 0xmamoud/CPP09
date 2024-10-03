#include "PmergeMe.hpp"
#include <chrono>
#include <climits>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

static int findDuplicate(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    for (int j = i + 1; j < argc; j++) {
      if (std::stol(argv[i]) == std::stol(argv[j]))
        return 1;
    }
  }
  return 0;
}

static int parsing(int argc, char *argv[]) {
  if (findDuplicate(argc, argv))
    return 0;
  for (int i = 1; i < argc; i++) {
    if (!std::isdigit(argv[i][0]))
      return 0;
    if (std::strlen(argv[i]) > 10)
      return 0;
    if (std::stol(argv[i]) < 0 || std::stol(argv[i]) > INT_MAX)
      return 0;
  }
  return 1;
}

static int alreadySorted(int argc, char *argv[]) {
  for (int i = 1; i < argc - 1; i++) {
    if (std::stol(argv[i]) > std::stol(argv[i + 1]))
      return 0;
  }
  return 1;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: "
              << "PmergeMe"
                 "[argv list]"
              << std::endl;
  }
  if (!parsing(argc, argv)) {
    std::cerr << "Error: "
              << "Invalid input" << std::endl;
    return 1;
  }
  if (alreadySorted(argc, argv)) {
    std::cout << "Input already sorted: ";
    for (int i = 1; i < argc; i++) {
      std::cout << argv[i] << " ";
    }
    std::cout << std::endl;
    return 1;
  }
  if (argc == 2) {
    std::cout << argv[1] << std::endl;
    return 0;
  }

  std::vector<int> vec;

  for (int i = 1; i < argc; i++) {
    vec.push_back(std::stoi(argv[i]));
  }

  std::cout << "Before: ";
  for (int i = 1 + 1; i < argc; i++) {
    std::cout << argv[i] << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;

  PmergeMe p;
  std::chrono::high_resolution_clock::time_point start =
      std::chrono::high_resolution_clock::now();
  p.sortVec(vec);
  std::chrono::high_resolution_clock::time_point end =
      std::chrono::high_resolution_clock::now();
  std::cout << "After: ";
  p.printVec();
  std::cout << "time to proces a range of " << vec.size() << " elements: "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                   .count()
            << "ns" << std::endl;

  std::list<int> list;
  for (int i = 1; i < argc; i++) {
    list.push_back(std::stoi(argv[i]));
  }
  start = std::chrono::high_resolution_clock::now();
  p.sortList(list);
  end = std::chrono::high_resolution_clock::now();
  std::cout << "time to proces a range of " << list.size() << " elements: "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                   .count()
            << "ns" << std::endl;

  return 0;
}
