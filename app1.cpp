#include<iostream>
#include<fstream>
using namespace std;
#include"State.h"

void _main_loop_draft() {
  ifstream fs("initial_state.txt");
  State state(fs);
  state.update("NEW_GAME");
  display_text(state, cout);
  while(1) {
    string input;
    if (!getline(cin, input)) break;
    if ("q" == input) break;

    state.update(!state.get_show_buttons() ? "NEW_GAME" : input);
    display_text(state, cout);
  }
}

int main() {
  _main_loop_draft();
}
