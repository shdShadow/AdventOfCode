#include <fstream>
#include <regex>
#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string/trim.hpp>
using namespace std;
vector<string> splitStringBy(string s, string c) {
  regex rgx(c);
  sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
  sregex_token_iterator end;
  vector<string> fields(iter, end);
  return fields;
}
vector<int> getIntsFromStrings(vector<string> strings) {
  vector<int> ints;
  for (int i = 0; i < strings.size(); i++) {
    if(strings[i] != ""){
     ints.push_back(stoi(strings[i]));
    }
  }
  return ints;
}
int main(int argc, char *argv[]) {
  string line;
  ifstream file("input.txt");
  int sum = 0;
  vector<string> lines;
  if (file.is_open()) {
    while (getline(file, line)) {
      lines.push_back(line);
    }
  }
  file.close();
  //Now that we read all the file
  for(int i = 0 ; i < lines.size(); i++){
    int card_total = 0;
    vector<string> seperate_game = splitStringBy(lines[i], ":");
    //Now that i separated the string containing the card numbers, we split to get the two sets of numbers
    boost::algorithm::trim(seperate_game[1]);
    vector<string> numbers_sets = splitStringBy(seperate_game[1], "\\|");
    boost::algorithm::trim(numbers_sets[0]);
    boost::algorithm::trim(numbers_sets[1]);
    vector<int> winning_numbers = getIntsFromStrings(splitStringBy(numbers_sets[0], " "));
    vector<int> played_numbers = getIntsFromStrings(splitStringBy(numbers_sets[1], " "));
    //Now that we got the set of numbers, we check how many winning numbers are in the played numbers
    for(int j = 0; j < winning_numbers.size(); j++){
      for(int k = 0; k < played_numbers.size(); k++){
        if(winning_numbers[j] == played_numbers[k]){
          if (card_total == 0){
            card_total = 1;
          }else{
            card_total = card_total * 2;
          }
        }
      }
    }
    sum += card_total;
  }
  cout << sum << endl;
}
