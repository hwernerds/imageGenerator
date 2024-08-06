#include<iostream>
#include<fstream>
using namespace std;
#include"State.h"
#include"File.h"

void _main_loop_early_draft() {
  ifstream fs("initial_state.txt");
  cout << "Testing1" << endl;
  State state(fs);
  cout << "Testing2" << endl;
  state.update("NEW_GAME");
  cout << "Testing3" << endl;
  display_text(state, cout);

  string input;
  getline(cin, input);

  state.update(input);
  display_text(state, cout);
}

int main() {
  cout << "testing0" << endl;
  _main_loop_early_draft();
}
