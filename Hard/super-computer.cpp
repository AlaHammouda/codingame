#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int current_step = 0;
int computations_done = 0;
vector<pair<int, float> > tasks;

bool sort_by_starting_day_and_duration(const pair<int, float>& a, const pair<int, float>& b) {
  return (a.second < b.second);
}

int main() {
  int number_of_calculations;
  int starting_day;
  int duration;

  cin >> number_of_calculations;
  cin.ignore();
  for (int i = 0; i < number_of_calculations; i++) {
    cin >> starting_day >> duration;
    cin.ignore();
    tasks.push_back(
        make_pair(starting_day * 1000 + duration, static_cast<float>(starting_day + duration) / 2));
  }

  sort(tasks.begin(), tasks.end(), sort_by_starting_day_and_duration);

  for (int i = 0; i < tasks.size(); i++) {
    if (current_step <= tasks[i].first / 1000) {
      current_step = tasks[i].first / 1000 + (tasks[i].first % 1000);
      computations_done += 1;
    }
  }
  cout << computations_done << endl;
}
