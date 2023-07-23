#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

class CardGame {
 private:
  vector<string> cards = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
  string result = "WINNER";
  int winner;
  int nb_rounds;
  queue<string> cardp_1;
  queue<string> cardp_2;
  queue<string> war_queue_1;
  queue<string> war_queue_2;
  bool war_active;
  int war_queue_size;
  int card_comparison;

  void display_queue(queue<string> q) {
    while (!q.empty()) {
      cerr << q.front() << ", ";
      q.pop();
    }
    cerr << endl;
  }

  void add_cards_to_winning_player(queue<string>* winning_player_queue) {
    if (!war_active) {
      winning_player_queue->push(cardp_1.front());
      winning_player_queue->push(cardp_2.front());
      cardp_1.pop();
      cardp_2.pop();
    } else {
      war_queue_size = war_queue_1.size();
      for (int i = 0; i < war_queue_size; i++) {
        winning_player_queue->push(war_queue_1.front());
        war_queue_1.pop();
      }
      winning_player_queue->push(cardp_1.front());
      cardp_1.pop();
      war_queue_size = war_queue_2.size();
      for (int i = 0; i < war_queue_size; i++) {
        winning_player_queue->push(war_queue_2.front());
        war_queue_2.pop();
      }
      winning_player_queue->push(cardp_2.front());
      cardp_2.pop();
      war_active = false;
    }
  }

 public:
  CardGame() {
    winner = 1;
    nb_rounds = 0;
    war_active = false;
  }

  void initialize_card_game() {
    int n;  // the number of cards for player 1
    string card;
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++) {
      cin >> card;
      cin.ignore();
      card.pop_back();
      cardp_1.push(card);
    }
    int m;  // the number of cards for player 2
    cin >> m;
    cin.ignore();
    for (int i = 0; i < m; i++) {
      cin >> card;
      cin.ignore();
      card.pop_back();
      cardp_2.push(card);
    }
  }

  void run_card_game() {
    while (!cardp_1.empty() && !cardp_2.empty()) {
      card_comparison = compare_two_cards(cardp_1.front(), cardp_2.front());
      if (card_comparison > 0) {
        add_cards_to_winning_player(&cardp_1);
      } else if (card_comparison < 0) {
        add_cards_to_winning_player(&cardp_2);
      } else {
        war_active = true;
        if (cardp_1.size() < 4 || cardp_2.size() < 4) {
          cerr << "one player run out of cards during a war !!!!!" << endl;
          result = "PAT";
          break;
        }
        for (int i = 0; i < 4; i++) {
          war_queue_1.push(cardp_1.front());
          cardp_1.pop();
        }
        for (int i = 0; i < 4; i++) {
          war_queue_2.push(cardp_2.front());
          cardp_2.pop();
        }
      }
      if (!war_active)
        nb_rounds++;
    }
  }

  int compare_two_cards(string card1, string card2) {
    ptrdiff_t value1 = std::find(cards.begin(), cards.end(), card1) - cards.begin();
    ptrdiff_t value2 = std::find(cards.begin(), cards.end(), card2) - cards.begin();
    return value1 - value2;
  }

  void display_player_cards() {
    display_queue(cardp_1);
    display_queue(cardp_2);
  }

  void display_result() {
    if (war_active) {
      cerr << "exited, but war is still active, PAT !!" << endl;
      result = "PAT";
    }
    if (result == "WINNER") {
      if (cardp_1.empty())
        winner = 2;
      cout << winner << " " << nb_rounds << endl;
    } else {
      cout << "PAT" << endl;
    }
  }
};

int main() {
  CardGame* game = new CardGame();
  game->initialize_card_game();
  game->display_player_cards();
  game->run_card_game();
  game->display_result();
}
