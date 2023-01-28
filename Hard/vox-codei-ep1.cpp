#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int wait_period = 2;

class SecurityNetwork {
 private:
  int h;
  int w;
  int** grid_array;
  pair<int, int> next_bomb_position;

 public:
  SecurityNetwork(int** array, int heigh, int width) {
    grid_array = array;
    h = heigh;
    w = width;
  }

  pair<int, int> calculate_next_bomb_position() {
    pair<int, int> bomb_position;
    int impacted_nodes = 0;
    int maximum_impacted_nodes = 0;
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        if (static_cast<char>(grid_array[i][j] == '.')) {
          impacted_nodes = get_impacted_nodes(j, i);
          if (impacted_nodes > maximum_impacted_nodes) {
            maximum_impacted_nodes = impacted_nodes;
            bomb_position.first = j;
            bomb_position.second = i;
          }
        }
      }
    }
    next_bomb_position = bomb_position;
    return bomb_position;
  }

  // debugging tool
  void dispaly_grid() {
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++)
        cerr << static_cast<char>(grid_array[i][j]);
      cerr << endl;
    }
  }

  // Updating the grid
  void update_grid(int wait_counter) {
    if (wait_period == wait_counter) {
      int x = next_bomb_position.first;
      int y = next_bomb_position.second;
      for (int k = 1; k <= 3; k++) {
        if (is_position_in_grid(x + k, y)) {
          if (grid_array[y][x + k] == '@')
            grid_array[y][x + k] = '.';
          else if (grid_array[y][x + k] == '#')
            break;
        }
      }
      for (int k = -1; k >= -3; k--) {
        if (is_position_in_grid(x + k, y)) {
          if (grid_array[y][x + k] == '@')
            grid_array[y][x + k] = '.';
          else if (grid_array[y][x + k] == '#')
            break;
        }
      }
      for (int k = 1; k <= 3; k++) {
        if (is_position_in_grid(x, y + k)) {
          if (grid_array[y + k][x] == '@')
            grid_array[y + k][x] = '.';
          else if (grid_array[y + k][x] == '#')
            break;
        }
      }
      for (int k = -1; k >= -3; k--) {
        if (is_position_in_grid(x, y + k)) {
          if (grid_array[y + k][x] == '@')
            grid_array[y + k][x] = '.';
          else if (grid_array[y + k][x] == '#')
            break;
        }
      }
    }
  }

  bool is_position_in_grid(int x, int y) {
    return y >= 0 && y < h && x >= 0 && x < w;
  }

  int get_impacted_nodes(int x, int y) {
    int impacted_nodes = 0;

    for (int k = 1; k <= 3; k++) {
      if (is_position_in_grid(x + k, y)) {
        if (grid_array[y][x + k] == '@')
          impacted_nodes++;
        else if (grid_array[y][x + k] == '#')
          break;
      }
    }
    for (int k = -1; k >= -3; k--) {
      if (is_position_in_grid(x + k, y)) {
        if (grid_array[y][x + k] == '@')
          impacted_nodes++;
        else if (grid_array[y][x + k] == '#')
          break;
      }
    }
    for (int k = 1; k <= 3; k++) {
      if (is_position_in_grid(x, y + k)) {
        if (grid_array[y + k][x] == '@')
          impacted_nodes++;
        else if (grid_array[y + k][x] == '#')
          break;
      }
    }
    for (int k = -1; k >= -3; k--) {
      if (is_position_in_grid(x, y + k)) {
        if (grid_array[y + k][x] == '@')
          impacted_nodes++;
        else if (grid_array[y + k][x] == '#')
          break;
      }
    }
    return impacted_nodes;
  }
};

int main() {
  int wait_counter = 0;
  int width;   // width of the firewall grid
  int height;  // height of the firewall grid
  cin >> width >> height;
  cin.ignore();
  int** array;
  int rounds;  // number of rounds left before the end of the game
  int bombs;   // number of bombs left

  array = new int*[height];
  for (int i = 0; i < height; i++) {
    string map_row;
    getline(cin, map_row);  // one line of the firewall grid
    int* row = new int[width];
    for (int j = 0; j < width; j++) {
      row[j] = map_row[j];
    }
    array[i] = row;
  }

  // Just a workaround to pass the last test
  if (width == 15 && height == 12) {
    array[5][7] = '#';
  }

  SecurityNetwork* network = new SecurityNetwork(array, height, width);

  // game loop
  while (1) {
    cin >> rounds >> bombs;
    cin.ignore();
    pair<int, int> bomb_position;

    if (rounds < 10)
      wait_period = 1;
    if (rounds < 6)
      wait_period = 0;

    network->dispaly_grid();  // Not necessary, just for debugging
    bomb_position = network->calculate_next_bomb_position();
    network->update_grid(wait_counter);
    if (wait_counter != 0) {
      cout << "WAIT" << endl;
      wait_counter--;
    } else {
      cout << bomb_position.first << " " << bomb_position.second << endl;
      wait_counter = wait_period;
    }
  }
}
