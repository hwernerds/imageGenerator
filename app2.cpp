#include<iostream>
#include<fstream>
using namespace std;
#include"State.h"

void _main_loop() {
  bool just_starting = true;
  while(1) {
    string input;
    if (!just_starting) {
      if (!getline(cin, input)) break;
      if ("q" == input) break;
    }

    ifstream fs;
    if (just_starting) fs.open("initial_state.txt");
    else fs.open("curr_state");
    State state(fs);
    fs.close();
    state.update((just_starting || !state.get_show_buttons()) ? "NEW_GAME" : input);
    display_text(state, cout);

    ofstream fs2("curr_state");
    state.write_to(fs2);

    just_starting = false;
  }
}

int main() {
  _main_loop();
}
