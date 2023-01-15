#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * The while loop represents the game.
 * Each iteration represents a turn of the game
 * where you are given inputs (the heights of the mountains)
 * and where you have to print an output (the index of the mountain to fire on)
 * The inputs you are given are automatically updated according to your last actions.
 **/

int main() {
  // game loop
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
