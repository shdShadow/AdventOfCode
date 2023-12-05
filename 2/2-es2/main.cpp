#include <boost/algorithm/string/trim.hpp>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
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
  if (file.is_open()) {
    while (getline(file, line)) {
      //get the game id divided from the rest
      vector<string> line_fields = splitStringBy(line, ":");
      //get the game id and the word 'game' separated
      vector<string> game_fields = splitStringBy(line_fields[0], " ");
      //get the game id
      //All of this was usefull for the previous exercise
      //get the n 'games' in the line
      vector<string> matches = splitStringBy(line_fields[1], ";");
      vector<string> plays;
      int min_red = -1;
      int min_green = -1;
      int min_blue = -1;
      for (int i = 0; i < matches.size(); i++) {
        vector<single_play> single_plays;
        //trim extra spaces to avoid problems when splitting the string
        boost::algorithm::trim_left(matches[i]);
        // split the string to get the single plays Ex. "3 red"
        plays = splitStringBy(matches[i], ",");
        for (int j = 0; j < plays.size(); j++) {
          //trim extra spaces just to be sure
          boost::algorithm::trim(plays[j]);
          //separate the number of cubes from the color
          vector<string> tmp = splitStringBy(plays[j], " ");
          //create an object for it
          single_play sp(tmp[1], stoi(tmp[0]));
          single_plays.push_back(sp);
        }
        //get the maximum values for each color, which are the minumum values to play the game
        for (int x = 0; x < single_plays.size(); x++) {
          if (single_plays[x].color == "red") {
            if (single_plays[x].number > min_red) {
              min_red = single_plays[x].number;
            }
          }
          if (single_plays[x].color == "green") {
            if (single_plays[x].number > min_green) {
              min_green = single_plays[x].number;
            }
          }
          if (single_plays[x].color == "blue") {
            if (single_plays[x].number > min_blue) {
              min_blue = single_plays[x].number;
            }
          }
        }
      }
      //get the total
      sum += (min_red * min_green * min_blue);
      n++;
      cout << "Line: " << line << " sum: " << sum << " valid: " << endl;
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
