#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  int nb_floors;  // number of floors
  int width;      // width of the area
  int nb_rounds;  // maximum number of rounds
  int exit_floor;
  int exit_pos;         // position of the exit on its floor
  int nb_total_clones;  // number of generated clones
  int nb_additional_elevators;
  int nb_elevators;

  int exit_path;
  int clone_floor;
  int clone_pos;
  string direction;

  cin >> nb_floors >> width >> nb_rounds >> exit_floor >> exit_pos >> nb_total_clones >>
      nb_additional_elevators >> nb_elevators;
  cin.ignore();
  int elevator_for_floor_n[nb_floors];  // NOLINT

  for (int i = 0; i < nb_elevators; i++) {
    int elevator_floor;  // floor on which this elevator is found
    int elevator_pos;    // position of the elevator on its floor
    cin >> elevator_floor >> elevator_pos;
    cin.ignore();
    elevator_for_floor_n[elevator_floor] = elevator_pos;
  }

  while (1) {
    cin >> clone_floor >> clone_pos >> direction;
    cin.ignore();
    if (clone_floor < exit_floor)
      exit_path = elevator_for_floor_n[clone_floor];
    else
      exit_path = exit_pos;

    if ((exit_path > clone_pos && direction == "LEFT") ||
        (exit_path < clone_pos && direction == "RIGHT"))
      cout << "BLOCK" << endl;
    else
      cout << "WAIT" << endl;
  }
}
