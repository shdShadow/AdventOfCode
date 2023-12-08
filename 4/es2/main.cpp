//WARNING! THIS CODE IS QUITE INEFFICIENT AND TAKES ABOUT 20-30 SECONDS TO FULLY RUN
//I MIGHT TRY TO OPTIMIZE IT IN THE FUTURE
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
vector<int> getIntsFromStrings(vector<string> strings) {
  vector<int> ints;
  for (int i = 0; i < strings.size(); i++) {
    if (strings[i] != "") {
      ints.push_back(stoi(strings[i]));
    }
  }
  return ints;
}
struct single_card {
  int card_number;
  int winning_numbers_count;
  single_card(int card_number, int winning_numbers_count) {
    this->card_number = card_number;
    this->winning_numbers_count = winning_numbers_count;
  }
};
single_card findCardByGameNumber(vector<single_card> cards, int game_number) {
  for (int i = 0; i < cards.size(); i++) {
    if (cards[i].card_number == game_number) {
      return cards[i];
    }
  }
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
  vector<single_card> sample_cards;
  for (int i = 0; i < lines.size(); i++) {
    // get the card number
    vector<string> seperate_game = splitStringBy(lines[i], ":");
    boost::algorithm::trim(seperate_game[0]);
    boost::algorithm::trim(seperate_game[1]);
    vector<string> card_fields = splitStringBy(seperate_game[0], " ");
    int card_number = 0;
    for (int x = 0; x < card_fields.size(); x++) {
      if (card_fields[x] != "") {
        if (card_fields[x] != "Card") {
          card_number = stoi(card_fields[x]);
          break;
        }
      }
    }
    // get the sets of numbers
    vector<string> numbers_sets = splitStringBy(seperate_game[1], "\\|");
    vector<int> winning_numbers =
        getIntsFromStrings(splitStringBy(numbers_sets[0], " "));
    vector<int> played_numbers =
        getIntsFromStrings(splitStringBy(numbers_sets[1], " "));
    int counter = 0;
    ////Now that we got the set of numbers, we check how many winning numbers
    /// are in the played numbers
    for (int j = 0; j < winning_numbers.size(); j++) {
      for (int k = 0; k < played_numbers.size(); k++) {
        if (winning_numbers[j] == played_numbers[k]) {
          counter++;
        }
      }
    }
    single_card card(card_number, counter);
    sample_cards.push_back(card);
  }
  // Now that we go the sample cards we can now think about how many cards
  // should we generate
  vector<single_card> total_generated_cards = sample_cards;
  for (int i = 0; i < total_generated_cards.size(); i++) {
    int winning_numbers = total_generated_cards[i].winning_numbers_count;
    int card_number = total_generated_cards[i].card_number;
    //if its the last card, we dont need to generate more cards
    if (i == total_generated_cards.size() - 1) {
      break;
    }
    //if the card number is equal to the highest card number we cant generate cards
    if (card_number == sample_cards[sample_cards.size() - 1].card_number) {
      continue;
    }
    for (int i = 1; i <= winning_numbers; i++) {
      single_card card = findCardByGameNumber(sample_cards, card_number + i);
      total_generated_cards.push_back(card);
    }
  }
  cout << total_generated_cards.size() << endl;
}
