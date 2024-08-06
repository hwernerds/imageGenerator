#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
#include"/usr/local/cs/cs251/react.h"
#include"State.h"

/*class State {
    int num;

public:
    static const int offset;

    State(istream &is) { is >> num; }
    int get_num() const { return num; }
    void write_to(ostream &os) const { os << num << endl; }
    int size_in_bytes() const { ostringstream oss; write_to(oss); return oss.str().size(); }
    void update() { if (_received_event() && 'a' == _global_mem[100]) ++num; }
};

const int State::offset = 1;*/

/*void display(const State &state) {
    //string s = "num is " + to_string(state.get_num());
    //int i = 1 + state.size_in_bytes();
    //_put_tilde_terminated_string(s, _global_mem + i);
    _add_yaml("count.yaml", {{"top_index", i}, {"input_index", 100}});
    if (current == "Home") {
        
    }
}*/

void _receive_and_send() {
    // initialization
    _read_event_info_file("event_info");
    if (_just_starting()) {_read_global_mem_from_file("startup_mem");
    /*cout << "startup_mem" << endl;*/ }
    else _read_global_mem_from_file("begin_mem");

    istringstream iss(_global_mem + State::offset);
    State state(iss);
    istringstream jss(_global_mem + State::offset);
    if (!_just_starting()) {
        char temp;
        cout << state.get_mem_offset() << "jss:";
        for(int i = 0; i < 200; i++) {
            temp = _global_mem[i];
            cout << temp;
        }
        cout << endl;
    }

    // event handling and display
    state.update();
    cout << "Displaying:" << state.get_current() << endl;
    display(state);

    // write out the end state 
    ostringstream oss;
    state.write_to(oss);
    string s = oss.str();
    //cout << s.get_Status_Text() << "||s" << endl;
    s.copy(_global_mem + 0, s.length());

    _write_global_mem_to_file("end_mem");
    _write_global_yaml_to_file("react.yaml");
    delete [] _global_mem;
}

int main() {
    _receive_and_send();
}
