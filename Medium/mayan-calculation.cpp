#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int64_t get_number(int l, int h, string array[20]) {
  int s;
  cin >> s;
  cin.ignore();
  string str = "";
  int count = 0;
  int64_t number = 0;
  int power = s / h - 1;
  for (int i = 0; i < s; i++) {
    string num_line;
    cin >> num_line;
    cin.ignore();
    str += num_line;
    if (count == l - 1) {
      count = -1;
      for (int k = 0; k < 20; k++) {
        if (array[k] == str)
          number += k * pow(20, power);
      }
      power--;
      str = "";
    }
    count++;
  }
  return number;
}

int main() {
  int l;
  int h;
  string array[20] = { "" };
  cin >> l >> h;
  cin.ignore();
  for (int i = 0; i < h; i++) {
    string numeral;
    cin >> numeral;
    cin.ignore();
    for (int j = 0; j < 20; j++) {
      array[j] = array[j] + numeral.substr(j * l, l);
    }
  }

  int64_t number1 = get_number(l, h, array);
  int64_t number2 = get_number(l, h, array);

  string operation;
  cin >> operation;
  cin.ignore();

  int64_t resultat = 0;

  if (operation == "+") {
    resultat = number2 + number1;
  } else if (operation == "-") {
    resultat = number1 - number2;
  } else if (operation == "*") {
    resultat = number1 * number2;
  } else if (operation == "/") {
    resultat = number1 / number2;
  }

  vector<int> powers;
  int64_t power = 1;
  if (resultat == 0) {
    powers.push_back(0);
  } else {
    while (resultat > 0) {
      int64_t k_power = (resultat % (power * 20)) / power;
      resultat -= k_power * power;
      powers.push_back(k_power);
      power *= 20;
    }
  }

  reverse(powers.begin(), powers.end());

  for (int i = 0; i < powers.size(); i++) {
    cerr << powers.at(i) << endl;
  }

  for (int i = 0; i < powers.size(); i++) {
    string output = "";
    for (int j = 0; j < h; j++) {
      output += array[powers.at(i)].substr(j * l, l) + "\n";
    }
    cout << output;
    output = "";
  }
}
