#include <algorithm>
#include <boost/algorithm/string/trim.hpp>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;
vector<string> splitStringBy(string s, string c) {
  regex rgx(c);
  sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
  sregex_token_iterator end;
  vector<string> fields(iter, end);
  return fields;
}
long long getValues(string s){
  vector<string> fields = splitStringBy(s, ":");
  boost::trim(fields[1]);
  vector<string> values = splitStringBy(fields[1], " ");
  vector<int> v;
  string string = "";
  for (int i = 0; i < values.size(); i++) {
    if (values[i] != ""){
      string += values[i];
    }
  }
  return stoll(string);
}
int main(int argc, char *argv[]) {
  string line;
  ifstream file("input.txt");
  int sum = 1;
  vector<string> lines;
  if (file.is_open()) {
    while (getline(file, line)) {
      lines.push_back(line);
    }
  }
  file.close();
  long long time = getValues(lines[0]);
  long long distances = getValues(lines[1]);
  long long wins = 0;
  for (long long i = 0LL; i < time; i++) {
      long long time_left = time - i;
      long long velocity = i;
      long long distance_traveled = velocity * time_left;
      if (distance_traveled > distances){
        wins++;
      }
  }
  cout << wins << endl;
  
}
