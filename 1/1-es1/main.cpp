#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;
int main(int argc, char *argv[]) {
  string line = "";
  ifstream file("input.txt");
  int sum = 0;
  int n = 0;
  if (file.is_open()) {
    while (getline(file, line)) {
      vector<int> *numbers = new vector<int>();
      for (int i = 0; i < line.length(); i++) {
        n = int(line.at(i)) - 48;
        if (n >= 0 && n <= 9) {
	  numbers->push_back(n);
        }
	
      }
      int n1 = numbers->at(0);
      int n2 = numbers->at(numbers->size()-1);
      sum = sum + n1 *10 + n2;
      cout << "line: " << line << "n1:" << n1 << " n2:" << n2 << "sum: " << sum << endl;
    }
    file.close();
  }
  cout << sum << endl;
  return 0;
}
