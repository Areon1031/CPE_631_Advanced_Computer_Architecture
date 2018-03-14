#include <iostream>
#include <map>
#include <vector>
using namespace std;


struct monkey_count
{
  double n_gorilla;
  double n_chimp;
  double n_baboon;

  monkey_count() :
    n_gorilla(0),
    n_chimp(0),
    n_baboon(0) {}
};

void fill_monkey_table(std::map<int, monkey_count>& table)
{
  for (int i = 0; i < 10; i++)
  {
    monkey_count temp;
    temp.n_baboon = 3 + i;
    temp.n_chimp = 4;
    temp.n_gorilla = 5;
    table.insert(std::pair<int, monkey_count>(i, monkey_count()));
  }
}

void print_table(std::map<int, monkey_count>& table)
{
  for (std::map<int, monkey_count>::iterator it = table.begin(); it != table.end(); ++it)
  {
    cout << it->first << " => " << it->second.n_baboon << endl;
  }
}

int main(int argc, char* argv[])
{
  std::map<int, monkey_count> monkey_table;
  fill_monkey_table(monkey_table);
  print_table(monkey_table);

  std::vector<int> test;
  test.push_back(42);
  test.push_back(43);
  test.push_back(44);
  test.push_back(45);
  test.push_back(46);


  int updateIdx = 0;
  for (std::vector<int>::iterator it = test.begin(); it != test.end(); ++it)
  {
    if (*it == 44)
      updateIdx = std::distance(test.begin(), it);

  }

  std::vector<int>::iterator p = std::find(test.begin(), test.end(), 44);
  cout << "Index in vector: " << updateIdx << endl;
  



  if (monkey_table.count(3))
  {
    cout << "Found entry 3" << endl;
  }
  else
  {
    cout << "Didn't find entry 3" << endl;
  }

  if (monkey_table.count(42))
  {
    cout << "Found entry 42" << endl;
  }
  else
  {
    cout << "Didn't find entry 42" << endl;
  }

  cin.ignore();
  return 0;
}