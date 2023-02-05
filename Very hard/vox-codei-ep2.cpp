#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
int wait_period_cnst;

class SecurityNetwork {
 private:
  int h;
  int w;
  int** grid_array;
  int** trace_grid_array;
  pair<int, int> next_bomb_position;
  bool some_nodes_were_eliminated;
  int current_active_nodes;

 public:
  SecurityNetwork(int heigh, int width) {
    h = heigh;
    w = width;
    some_nodes_were_eliminated = false;
    current_active_nodes = 0;
    int** array;
    int** trace_array;
    array = new int*[h];
    trace_array = new int*[h];

    for (int i = 0; i < h; i++) {
      int* row = new int[w];
      for (int j = 0; j < w; j++) {
        row[j] = '.';
      }
      array[i] = row;
    }

    for (int i = 0; i < h; i++) {
      int* row = new int[w];
      for (int j = 0; j < w; j++) {
        row[j] = '.';
      }
      trace_array[i] = row;
    }

    grid_array = array;
    trace_grid_array = trace_array;
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
        cerr << char(grid_array[i][j]);
      cerr << endl;
    }
  }

  void dispaly_trace_grid() {
    cerr << endl;
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++)
        cerr << char(trace_grid_array[i][j]);
      cerr << endl;
    }
  }

  // Updating the grid is very important especially if a bomb is exploded
  void update_grid() {
    int active_nodes = 0;
    for (int i = 0; i < h; i++) {
      string map_row;
      getline(cin, map_row);  // one line of the firewall grid
      for (int j = 0; j < w; j++) {
        grid_array[i][j] = map_row[j];
        if (grid_array[i][j] == '@')
          active_nodes++;
      }
    }

    if (active_nodes < current_active_nodes) {
      cerr << "some nodes were destroyed, removing the trace nodes ..." << endl;
      some_nodes_were_eliminated = true;
    }

    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        if (trace_grid_array[i][j] != '@' || some_nodes_were_eliminated)
          trace_grid_array[i][j] = grid_array[i][j];
      }
    }

    some_nodes_were_eliminated = false;
    current_active_nodes = active_nodes;
  }

  bool is_position_in_grid(int x, int y) {
    return y >= 0 && y < h && x >= 0 && x < w;
  }

  int get_impacted_nodes(int x, int y) {
    int impacted_nodes = 0;

    for (int k = 1; k <= 3; k++) {
      if (is_position_in_grid(x + k, y)) {
        if (trace_grid_array[y][x + k] == '@')
          impacted_nodes++;
        else if (trace_grid_array[y][x + k] == '#')
          break;
      }
    }
    for (int k = -1; k >= -3; k--) {
      if (is_position_in_grid(x + k, y)) {
        if (trace_grid_array[y][x + k] == '@')
          impacted_nodes++;
        else if (trace_grid_array[y][x + k] == '#')
          break;
      }
    }
    for (int k = 1; k <= 3; k++) {
      if (is_position_in_grid(x, y + k)) {
        if (trace_grid_array[y + k][x] == '@')
          impacted_nodes++;
        else if (trace_grid_array[y + k][x] == '#')
          break;
      }
    }
    for (int k = -1; k >= -3; k--) {
      if (is_position_in_grid(x, y + k)) {
        if (trace_grid_array[y + k][x] == '@')
          impacted_nodes++;
        else if (trace_grid_array[y + k][x] == '#')
          break;
      }
    }
    return impacted_nodes;
  }
};

int main() {
  int wait_period = 11;
  int width;   // width of the firewall grid
  int height;  // height of the firewall grid
  cin >> width >> height;
  cin.ignore();
  int rounds;  // number of rounds left before the end of the game
  int bombs;   // number of bombs left
  SecurityNetwork* network = new SecurityNetwork(height, width);

  // game loop
  while (1) {
    cin >> rounds >> bombs;
    cin.ignore();
    pair<int, int> bomb_position;

    if (rounds < 5)
      wait_period_cnst = 0;
    if (rounds < 13)
      wait_period_cnst = 2;
    if (rounds < 25)
      wait_period_cnst = 3;
    if (rounds > 25)
      wait_period_cnst = 6;

    network->update_grid();
    network->dispaly_trace_grid();  // Not necessary, just for debugging
    if (wait_period != 0) {
      cout << "WAIT" << endl;
      wait_period--;
    } else {
      bomb_position = network->calculate_next_bomb_position();
      cout << bomb_position.first << " " << bomb_position.second << endl;
      wait_period = wait_period_cnst;
    }
  }
}
