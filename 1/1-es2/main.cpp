#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int getNumberFromLiteral(string literal);
int main(int argc, char *argv[]) {
  string line = "";
  string literals[] = {"one", "two",   "three", "four", "five",
                       "six", "seven", "eight", "nine"};
  ifstream file("input.txt");
  int sum = 0;
  int n = 0;
  if (file.is_open()) {
    while (getline(file, line)) {
      vector<int> numbers = vector<int>();
      for (int i = 0; i < line.length(); i++) {
        n = int(line.at(i)) - 48;
        if (n >= 1 && n <= 9) {
          numbers.push_back(n);
        } else {
          for (const auto &element : literals) {
            string substr = line.substr(i, element.length());
            if (substr == element) {
              int value = getNumberFromLiteral(element);
              numbers.push_back(value);
            }
          }
        }
      }
      int n1 = numbers.at(0);
      int n2 = numbers.at(numbers.size() - 1);
      sum += n1 * 10 + n2;
      cout << "line: " << line << " n1: " << n1 << " n2: " << n2
           << " sum: " << sum << endl;
    }
  }
  return 0;
}

int getNumberFromLiteral(string literal) {
  string literals[] = {"one", "two",   "three", "four", "five",
                       "six", "seven", "eight", "nine"};
  for (int i = 0; i < 9; i++) {
    if (literal == literals[i]) {
      return i + 1;
    }
  }
  return -1;
}
