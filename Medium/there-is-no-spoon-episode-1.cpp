#include <iostream>
#include <string>

using namespace std;

/**
 * Don't let the machines win. You are humanity's last hope...
 **/

int main() {
  int width;  // the number of cells on the X axis
  cin >> width;
  cin.ignore();
  int height;  // the number of cells on the Y axis
  cin >> height;
  cin.ignore();

  char tab[height][width];

  for (int i = 0; i < height; i++) {
    string line;
    getline(cin, line);  // width characters, each either 0 or .
    for (int j = 0; j < line.length(); j++) {
      tab[i][j] = line[j];
    }
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int k = 0;
      if (tab[i][j] == '0') {
        cout << j << " " << i << " ";
        for (k = j + 1; k < width; k++) {
          if (tab[i][k] == '0') {
            cout << k << " " << i << " ";
            break;
          }
        }
        if (k == width) {
          cout << "-1 -1 ";
        }

        for (k = i + 1; k < height; k++) {
          if (tab[k][j] == '0') {
            cout << j << " " << k << " " << endl;
            break;
          }
        }
        if (k == height) {
          cout << "-1 -1" << endl;
          ;
        }
      }
    }
  }
}
