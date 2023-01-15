#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Budgets {
 public:
  vector<int> budgets;
  int nb_contributors;

  int total_budget() {
    int total = 0;
    for (int c = 0; c < nb_contributors; c++) {
      total += budgets.at(c);
    }
    return total;
  }

  vector<int> get_solution(int gift_price) {
    vector<int> solution;
    int remaining_nb_contributors = nb_contributors;
    sort(budgets.begin(), budgets.end());

    cerr << "reversed sorted budgets" << endl;
    for (int i = 0; i < budgets.size(); i++) {
      cerr << budgets.at(i) << endl;
    }

    // Get the solution
    for (int i = 0; i < nb_contributors; i++) {
      int curr_average_contribution = static_cast<int>(gift_price / remaining_nb_contributors);
      if (budgets.at(i) < curr_average_contribution) {
        solution.push_back(budgets.at(i));
      } else {
        solution.push_back(curr_average_contribution);
      }
      gift_price = gift_price - solution.at(i);
      remaining_nb_contributors -= 1;
    }
    return solution;
  }
};

int main() {
  int n;
  cin >> n;
  cin.ignore();
  int c;
  cin >> c;
  cin.ignore();
  Budgets contributions;
  vector<int> solution;

  contributions.nb_contributors = n;
  for (int i = 0; i < n; i++) {
    int b;
    cin >> b;
    cin.ignore();
    contributions.budgets.push_back(b);
  }

  if (contributions.total_budget() < c) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    solution = contributions.get_solution(c);
    for (int i = 0; i < solution.size(); i++) {
      cout << solution.at(i) << endl;
    }
  }
}
