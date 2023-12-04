#include <string>
#include <iostream>
using namespace std;

int main (int argc, char *argv[]) {
  string line = "abcdefg";
  cout << line.substr(1,3);
  return 0;
}
