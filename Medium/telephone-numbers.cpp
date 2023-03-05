#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class tree_node {
 public:
  char value;
  vector<tree_node*> children;

  explicit tree_node(char num) {
    value = num;
  }
};

class tree {
 public:
  tree_node* root_node;

  explicit tree(char value) {
    root_node = new tree_node(value);
  }

  bool add_new_phone_number(string phone_number) {
    tree_node* current_node;
    current_node = root_node;
    if (root_node->value != phone_number[0]) {
      return false;
    }

    for (int i = 1; i < phone_number.length(); i++) {
      bool digit_exists = false;
      for (int j = 0; j < current_node->children.size(); j++) {
        if (current_node->children[j]->value == phone_number[i]) {
          digit_exists = true;
          current_node = current_node->children[j];
        }
      }

      if (!digit_exists) {
        for (int k = i; k < phone_number.length(); k++) {
          tree_node* new_node = new tree_node(phone_number[k]);
          current_node->children.push_back(new_node);
          current_node = new_node;
        }
        break;
      }
    }

    return true;
  }

  int get_number_of_elements(tree_node* node) {
    int nb_elements = 1;

    if (node->children.size() == 0) {
      return 1;
    }

    for (int i = 0; i < node->children.size(); i++) {
      nb_elements += get_number_of_elements(node->children[i]);
    }

    return nb_elements;
  }

  // Just for debugging
  int display_tree(tree_node* node) {
    print_subtree(node, 0);
    return 0;
  }

 private:
  void print_subtree(tree_node* node, int depth) {
    // Print the current node's value and depth
    cerr << string(depth, ' ') << node->value << endl;

    // Recursively print each child subtree
    for (int i = 0; i < node->children.size(); i++) {
      print_subtree(node->children[i], depth + 1);
    }
  }
};

int main() {
  int n;
  vector<tree*> trees;
  bool new_root_tree = true;
  int number_of_elements = 0;

  cin >> n;
  cin.ignore();
  for (int i = 0; i < n; i++) {
    string telephone;
    cin >> telephone;
    cin.ignore();
    new_root_tree = true;

    if (trees.size() == 0) {
      trees.push_back(new tree(telephone[0]));
      trees[0]->add_new_phone_number(telephone);
    } else {
      for (int j = 0; j < trees.size(); j++) {
        if (trees[j]->add_new_phone_number(telephone)) {
          new_root_tree = false;
          break;
        }
      }
      if (new_root_tree) {
        trees.push_back(new tree(telephone[0]));
        trees[trees.size() - 1]->add_new_phone_number(telephone);
        cerr << "Added a new root tree" << endl;
      }
    }
  }

  // Display all the Trees
  for (int j = 0; j < trees.size(); j++) {
    trees[j]->display_tree(trees[j]->root_node);
  }

  // Calculate the elements in all the Trees
  for (int j = 0; j < trees.size(); j++) {
    number_of_elements += trees[j]->get_number_of_elements(trees[j]->root_node);
  }

  // The number of elements (referencing a number) stored in the structure.
  cout << number_of_elements << endl;
}
