#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int W;  // width of the building.
  int H;  // height of the building.
  cin >> W >> H;
  cin.ignore();
  int N;  // maximum number of turns before game over.
  cin >> N;
  cin.ignore();
  int X0;
  int Y0;
  cin >> X0 >> Y0;
  cin.ignore();

  int minX = 0, minY = 0;
  int maxX = W - 1, maxY = H - 1;

  // game loop
  while (1) {
    string BOMB_DIR;  // the direction of the bombs from batman's current location (U, UR, R, DR, D,
                      // DL, L or UL)
    cin >> BOMB_DIR;
    cin.ignore();

    if (BOMB_DIR.find('U') != string::npos)
      maxY = Y0 - 1;
    if (BOMB_DIR.find('D') != string::npos)
      minY = Y0 + 1;
    if (BOMB_DIR.find('L') != string::npos)
      maxX = X0 - 1;
    if (BOMB_DIR.find('R') != string::npos)
      minX = X0 + 1;

    X0 = (maxX + minX) / 2;
    Y0 = (maxY + minY) / 2;

    cerr << minX << ' ' << minY << ' ' << maxX << ' ' << maxY << endl;
    cout << X0 << " " << Y0 << endl;  // the location of the next window Batman should jump to.
  }
}
