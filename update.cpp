#include"State.h"
using namespace std;

void State::update(string input) {
  if ("NEW_GAME" == input) {
    cout << "true" << endl;
    show_buttons = true;
    // set show_buttons to true and num_moves to zero
    num_moves = 0;
    // initialize the status_text
    status_text = "0/25 moves.";
    // initialize the grid randomly
    grid.randomize();
  } else {
    if (input[0] >= '0' && input[0] <= '6') {
    // check if the input is a number from 0 to 5
    //    if so, increment num_moves and call handle_button_event()
      num_moves++;
      handle_button_event((int)(input[0]-'0'));
    //    otherwise, print a warning message
    } else {
      cout << "a warning message" << endl;
    }
  }
}
