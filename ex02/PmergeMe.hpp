#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <list>
#include <string>
#include <utility>
#include <vector>

class PmergeMe {
private:
  std::list<int> _list;
  std::vector<int> _vec;
  std::string _vecTime;
  std::string _listTime;

  void setList(const std::list<std::pair<int, int>> &list);
  void setVec(const std::vector<std::pair<int, int>> &vec);

public:
  PmergeMe();
  PmergeMe(const PmergeMe &copy);
  PmergeMe &operator=(const PmergeMe &copy);
  ~PmergeMe();

  void sortList(std::list<int> &l);
  void sortVec(std::vector<int> &v);

  void printList();
  void printVec();
};

#endif // !PMERGEME_HPP
