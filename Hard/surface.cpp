#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int width;
int height;
char** map;
int** treated;
int count_water = 0;

int surface_area(int x, int y) {
  if (x >= width || x < 0 || y >= height || y < 0 || map[y][x] == '#')
    return 0;

  if (treated[y][x] == 1)
    return 0;
  treated[y][x] = 1;

  return 1 + surface_area(x + 1, y) + surface_area(x, y + 1) + surface_area(x, y - 1) +
         surface_area(x - 1, y);
}

int main() {
  cin >> width;
  cin.ignore();
  cin >> height;
  cin.ignore();

  map = new char*[height];
  treated = new int*[height];
  for (int i = 0; i < width; i++) {
    map[i] = new char[width];
    treated[i] = new int[width];
  }

  for (int i = 0; i < height; i++) {
    string row;
    getline(cin, row);
    for (int j = 0; j < width; j++) {
      map[i][j] = row[j];
      treated[i][j] = -1;
      if (map[i][j] == 'O')
        count_water += 1;
    }
  }

  int n;
  cin >> n;
  cin.ignore();
  for (int i = 0; i < n; i++) {
    int x;
    int y;
    cin >> x >> y;
    cin.ignore();

    if (count_water > (height * width * 9 / 10)) {
      cout << count_water << endl;
    } else {
      cout << surface_area(x, y) << endl;
    }

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        treated[i][j] = -1;
      }
    }
  }
}
