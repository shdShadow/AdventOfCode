#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Number {
  int value;
  int x;
  int y;
  Number(int v, int _x, int _y) {
    value = v;
    x = _x;
    y = _y;
  }
};
struct Symbol {
  char value;
  int x;
  int y;
  Symbol(char v, int _x, int _y) {
    value = v;
    x = _x;
    y = _y;
  }
};
vector<Number> searchInNumbers(vector<vector<Number>> numbers, Number n){
  //Simple function to search a number in the vector of all the nubers
  vector<Number> found;
  for ( int i = 0; i < numbers.size(); i++){
    vector<Number> tmp = numbers[i];
    for ( int j = 0; j < tmp.size(); j++){
      if (tmp[j].x == n.x && tmp[j].y == n.y){
        found = tmp;
      }
    }
  }
  return found;
}
bool alreadyExist(vector<vector<Number>> numbers, vector<Number> n){
  //Simple function to check if a number already exist in the vector found numbers
  bool exist = false;
  for(int i =0; i < numbers.size() ; i ++){
    vector<Number> tmp = numbers[i];
    if (tmp.size() == n.size()){
      int counter = 0;
      for (int j = 0 ; j < tmp.size(); j++){
        if (tmp[j].x == n[j].x && tmp[j].y == n[j].y && tmp[j].value == n[j].value){
          counter++;
        }
      }
      if (counter == tmp.size()){
        exist = true;
      }
    }
  }
  return exist;
}
int calculateNumber(vector<Number> n){
  //Simple function to calculate the number from the vector of digits
  int tot = 0;
  for (int i = 0 ; i < n.size(); i++){
    int multiplier = pow(10, n.size() - i - 1);
    tot += n[i].value * multiplier;
  }
  return tot;
}
vector<vector<Number>> checkNumbersNearSymbols(vector<vector<Number>> numbers, Symbol s, vector<string> matrix){
  //This function check if there are numbers near the symbol in every direction
  vector<vector<Number>> tmp;
  vector<Number> numberFound;
  //North
  if(s.y -1 >= 0){
    int c = int(matrix[s.y-1][s.x]) - 48;
    if(c >= 0 && c <= 9){
      Number n = Number(c, s.x, s.y-1);
      numberFound = searchInNumbers(numbers, n);
      if (!alreadyExist(tmp, numberFound)){
        tmp.push_back(numberFound);
      }
    }
  }
  //South
  if(s.y + 1 < matrix.size()){
    int c = int(matrix[s.y+1][s.x]) - 48;
    if(c >= 0 && c <= 9){
      Number n = Number(c, s.x, s.y+1);
      numberFound = searchInNumbers(numbers, n);
      if(!alreadyExist(tmp, numberFound)){
        tmp.push_back(numberFound);
      }
    }
  }
  //West
  if(s.x - 1 >= 0){
    int c = int(matrix[s.y][s.x-1]) - 48;
    if(c >= 0 && c <= 9){
      Number n = Number(c, s.x-1, s.y);
      numberFound = searchInNumbers(numbers, n);
      if(!alreadyExist(tmp, numberFound)){
        tmp.push_back(numberFound);
      }
    }
  }
  //East
  if(s.x + 1 < matrix[s.y].length()){
    int c = int(matrix[s.y][s.x+1]) - 48;
    if(c >= 0 && c <= 9){
      Number n = Number(c, s.x+1, s.y);
      numberFound = searchInNumbers(numbers, n);
      if(!alreadyExist(tmp, numberFound)){
        tmp.push_back(numberFound);
      }
    }
  }
  //North-West
  if (s.y -1 >= 0 && s.x - 1 >= 0){
    int c = int(matrix[s.y-1][s.x-1]) - 48;
    if(c >= 0 && c <= 9){
      Number n = Number(c, s.x-1, s.y-1);
      numberFound = searchInNumbers(numbers, n);
      if(!alreadyExist(tmp, numberFound)){
        tmp.push_back(numberFound);
      }
    }
  }
  //South-East
  if (s.y + 1 < matrix.size() && s.x + 1 < matrix[s.y].length()){
    int c = int(matrix[s.y+1][s.x+1]) - 48;
    if(c >= 0 && c <= 9){
      Number n = Number(c, s.x+1, s.y+1);
      numberFound = searchInNumbers(numbers, n);
      if(!alreadyExist(tmp, numberFound)){
        tmp.push_back(numberFound);
      }
    }
  }
  //South-West
  if (s.y - 1 >= 0 && s.x + 1 < matrix[s.y].length()){
    int c = int(matrix[s.y-1][s.x+1]) - 48;
    if(c >= 0 && c <= 9){
      Number n = Number(c, s.x+1, s.y-1);
      numberFound = searchInNumbers(numbers, n);
      if(!alreadyExist(tmp, numberFound)){
        tmp.push_back(numberFound);
      }
    }
  }
  //North-East
  if (s.y + 1 < matrix.size() && s.x - 1 >= 0){
    int c = int(matrix[s.y+1][s.x-1]) - 48;
    if(c >= 0 && c <= 9){
      Number n = Number(c, s.x-1, s.y+1);
      numberFound = searchInNumbers(numbers, n);
      if(!alreadyExist(tmp, numberFound)){
        tmp.push_back(numberFound);
      }
    }
  }
  return tmp;
}
int main(int argc, char *argv[]) {
  string line;
  ifstream file("input.txt");
  int sum = 0;
  int y = 0;
  //Vector containing all the numbers found in the file
  vector<vector<Number>> numbers;
  //Vector containing all the lines of the file
  vector<string> matrix;
  //Vector containing all the symbols found in the file
  vector<Symbol> symbols;
  if (file.is_open()) {
    while (getline(file, line)) {
      //This part is identical to the first exercise
      bool isConsecutive = false;
      vector<Number> singleNumber;
      for (int i = 0; i < line.length(); i++) {
        char c = line[i];
        int converted_char = (int)c - 48;
        if (converted_char >= 0 && converted_char <= 9){
          Number n = Number(converted_char, i, matrix.size());
          singleNumber.push_back(n);
          isConsecutive = true;
        }else{
          if (c == '*'){
            Symbol s = Symbol(c, i, y);
            symbols.push_back(s);
          }
          isConsecutive = false;
        }
        if(isConsecutive == false && singleNumber.size() > 0){
          numbers.push_back(singleNumber);
          singleNumber.clear();
        }
        if (i == line.length() - 1 && singleNumber.size() > 0){
          numbers.push_back(singleNumber);
          singleNumber.clear();
        }
      }
      y++;
      matrix.push_back(line);
    }
  }
  for (int i = 0; i < symbols.size(); i++){
    vector<vector<Number>> results;
    Symbol s = symbols[i];
    //Check how many numbers are near the symbol
    results = checkNumbersNearSymbols(numbers, s, matrix);
    int tot = 0;
    //If there are 2 and only two, we can calculate the result. Result = n1 * n2
    if (results.size() == 2){
      vector<int> values;
      for (int j = 0 ; j < results.size();j ++){
        vector<Number> n = results[j];
        values.push_back(calculateNumber(n));
      }
      tot = values[0] * values[1];
    }
    sum += tot;
  }
  cout << sum << endl;
  return 0;
}
