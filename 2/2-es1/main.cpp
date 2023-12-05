#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <boost/algorithm/string/trim.hpp>
using namespace std;
struct single_play {
  string color;
  int number;
  single_play(string c, int n) {
    color = c;
    number = n;
  }
};
vector<string> splitStringBy(string s, string c);
int main(int argc, char *argv[]) {
  string line = "";
  ifstream file("input.txt");
  int sum = 0;
  int n = 0;
  int max_red = 12;
  int max_green = 13;
  int max_blue = 14;
  std::string token;
  std::vector<std::string> tokens;
  if (file.is_open()) {
    while (getline(file, line)) {
      vector<string> line_fields = splitStringBy(line, ":");
      vector<string> game_fields = splitStringBy(line_fields[0], " ");
      vector<string> matches = splitStringBy(line_fields[1], ";");
      vector<string> plays;
      int current_game_number = stoi(game_fields[1]);
      bool valid = true;
      for (int i = 0; i < matches.size(); i++) {
        vector<single_play> single_plays;
        boost::algorithm::trim_left(matches[i]);
        plays = splitStringBy(matches[i], ",");
        for (int j = 0; j < plays.size(); j++) {
          boost::algorithm::trim(plays[j]);
          vector<string> tmp = splitStringBy(plays[j], " ");
          single_play sp(tmp[1], stoi(tmp[0]));
          single_plays.push_back(sp);
        }
        for (int x =0; x < single_plays.size(); x++){
          if (single_plays[x].color == "red" && single_plays[x].number > max_red){
            valid = false;
          }else if(single_plays[x].color == "green" && single_plays[x].number > max_green){
            valid = false;
          }else if(single_plays[x].color == "blue" && single_plays[x].number > max_blue){
            valid = false;
          }
        }
        
      }
      if (valid) {
        sum += current_game_number;
        n++;
      }
      cout << "Line: " << line << " sum: " << sum << " valid: " << valid << endl;
    }
  }
  file.close();
  return 0;
}

vector<string> splitStringBy(string s, string c) {
  regex rgx(c);
  sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
  sregex_token_iterator end;
  vector<string> fields(iter, end);
  return fields;
}
