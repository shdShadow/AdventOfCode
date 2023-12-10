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
vector<int> getValues(string s){
  vector<string> fields = splitStringBy(s, ":");
  boost::trim(fields[1]);
  vector<string> values = splitStringBy(fields[1], " ");
  vector<int> v;
  for (int i = 0; i < values.size(); i++) {
    if (values[i] != ""){
      v.push_back(stoi(values[i]));
    }
  }
  return v;
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
  vector<int> times = getValues(lines[0]);
  vector<int> distances = getValues(lines[1]);
  vector<int> tots;
  for (int i = 0; i < times.size(); i++) {
    int wins = 0;
    for(int j = 0; j < times[i]; j++){
      int time_left = times[i] - j;
      int velocity = j;
      int distance_traveled = velocity * time_left;
      if (distance_traveled > distances[i]){
        wins++;
      }
    }
    tots.push_back(wins);
  }
  for (int i = 0; i < tots.size(); i++) {
        sum *= tots[i];
  }
  cout << sum << endl;
  
}
