/*
 * ----------------------------------------------------------------
 * Copyright (C) 2023, Ala Eddine Hammouda.
 * ----------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;

int main() {
  while (1) {
    int max_hight_index = 0;
    int max_hight = 0;
    for (int i = 0; i < 8; i++) {
      int mountain_h;  // represents the height of one mountain.
      cin >> mountain_h;
      cin.ignore();
      if (mountain_h > max_hight) {
        max_hight = mountain_h;
        max_hight_index = i;
      }
    }

    cout << max_hight_index << endl;  // The index of the mountain to fire on.
  }
}
