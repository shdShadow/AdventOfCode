#include <cmath>
#include <fstream>
#include <iostream>
#include <istream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;
  struct Number {
    int value;
    int x;
    int y;
    Number(int v, int _x, int _y){
      value = v;
      x = _x;
      y = _y;
    }
  };
  bool checkIfSymbolNear(vector<Number> n, vector<string> matrix){
    bool isValid = false;
    for (int i = 0; i < n.size(); i ++){
      Number digit = n[i];
      //check North
      if(digit.y - 1 >= 0 ){
        char c = matrix[digit.y-1][digit.x];
        if(!(int(c) - 48>= 0 && int(c) - 48 <= 9)){
          if(matrix[digit.y-1][digit.x] != '.'){
            isValid = true;
            break;
        }
      }
    }
    //check South
    if(digit.y + 1 < matrix.size()){
      char c = matrix[digit.y+1][digit.x];
      if(!(int(c) - 48>= 0 && int(c) - 48 <= 9)){
        if(matrix[digit.y+1][digit.x] != '.'){
          isValid = true;
          break;
        }
      }
    }
    //checkEast
    if(digit.x + 1 < matrix[digit.y].length()){
      char c = matrix[digit.y][digit.x+1];
      if(!(int(c)- 48>= 0 && int(c) - 48<= 9)){
        if(matrix[digit.y][digit.x+1] != '.'){
          isValid = true;
          break;
        }
      }
    }
    //check West
    if(digit.x - 1 >= 0){
      char c = matrix[digit.y][digit.x-1];
      if(!(int(c) - 48>= 0 && int(c) - 48 <= 9)){
        if(matrix[digit.y][digit.x-1] != '.'){
          isValid = true;
          break;
        }
      }
    }
    //check NorthEast
    if(digit.y - 1 >= 0 && digit.x + 1 < matrix[digit.y].length()){
      char c = matrix[digit.y-1][digit.x+1];
      if(!(int(c)- 48>= 0 && int(c) - 48 <= 9)){
        if(matrix[digit.y-1][digit.x+1] != '.'){
          isValid = true;
          break;
        }
      }
    }
    //check NorthWest
    if(digit.y - 1 >= 0 && digit.x - 1 >= 0){
      char c = matrix[digit.y-1][digit.x-1];
      if(!(int(c) - 48>= 0 && int(c) - 48 <= 9)){
        if(matrix[digit.y-1][digit.x-1] != '.'){
          isValid = true;
          break;
        }
      }
    }
    //check SouthEast
    if(digit.y + 1 < matrix.size() && digit.x + 1 < matrix[digit.y].length()){
      char c = matrix[digit.y+1][digit.x+1];
      if(!(int(c)-48>= 0 && int(c) - 48 <= 9)){
        if(matrix[digit.y+1][digit.x+1] != '.'){
          isValid = true;
          break;
        }
      }
    }
    //check SouthWest
    if(digit.y + 1 < matrix.size() && digit.x - 1 >= 0){
      char c = matrix[digit.y+1][digit.x-1];
      if(!(int(c)- 48>= 0 && int(c) - 48 <= 9)){
        if(matrix[digit.y+1][digit.x-1] != '.'){
          isValid = true;
          break;
        }
      }
    }

  }

  return isValid;
}
int main(int argc, char *argv[]) {
  string line = "";
  ifstream file("input.txt");
  int sum = 0;
  int y = 0;
  int n = 0;
  vector<vector<Number>> numbers;
  vector<string> matrix;
  if (file.is_open()) {
    while (getline(file, line)) {
      bool isConsecutive = false;
      vector<Number> singleNumber;
      for(int i =0; i < line.length(); i++){
        char c = line[i];
        int converted_char = (int)c - 48;
        if(converted_char >= 0 && converted_char <= 9){
          Number n = Number(converted_char, i, y);
          singleNumber.push_back(n);
          isConsecutive = true;
        }else{
          isConsecutive = false;
        }

        if (isConsecutive == false && singleNumber.size() > 0){
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
    file.close();
  }
  for(int i =0; i < numbers.size(); i++){
    vector<Number> n = numbers[i];
    if(checkIfSymbolNear(n, matrix)){
      int tot = 0;
      for (int j =0; j < n.size(); j++){
        int multiplier = pow(10, n.size() - j - 1);
        tot += n[j].value * multiplier;
      }
      sum += tot;
      cout << sum << endl;
    }
  }
}
