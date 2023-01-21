#include <iostream>
#include <string>
#include <vector>

using namespace std;

void next_room(int x, int y, string direction, int room_type) {
  cerr << "current room" << x << " " << y << " " << room_type;
  switch (room_type) {
    case (2):
      if (direction == "LEFT")
        x += 1;
      else
        x -= 1;
      break;
    case (4):
      if (direction == "RIGHT")
        y += 1;
      else
        x -= 1;
      break;
    case (5):
      if (direction == "LEFT")
        y += 1;
      else
        x += 1;
      break;
    case (6):
      if (direction == "LEFT")
        x += 1;
      else
        x -= 1;
      break;
    case (10):
      x -= 1;
      break;
    case (11):
      x += 1;
      break;
    default:
      y += 1;
  }

  cout << x << " " << y << endl;
}

int main() {
  int w;  // number of columns.
  int h;  // number of rows.
  cin >> w >> h;
  cin.ignore();

  int next_x;
  int next_y;

  int array[h][w];

  for (int i = 0; i < h; i++) {
    string line;
    getline(cin, line);  // represents a line in the grid and contains W integers. Each integer
                         // represents one room of a given type.
    for (int j = 0; j < w; j++) {
      array[i][j] = stoi(line.substr(0, line.find(" ")));
      line.erase(0, line.find(" ") + 1);
    }
  }

  int ex;  // the coordinate along the X axis of the exit (not useful for this first mission, but
           // must be read).
  cin >> ex;
  cin.ignore();

  // game loop
  while (1) {
    int xi;
    int yi;
    string pos;
    cin >> xi >> yi >> pos;
    cin.ignore();
    next_room(xi, yi, pos, array[yi][xi]);
  }
}
