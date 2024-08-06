#ifndef __STATE_H__
#define __STATE_H__
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include"File.h"
#include"/usr/local/cs/cs251/react.h"
using namespace std;

class State {
    bool LoggedIn;
    string user;
    string password;
    string current;
    string status_text;
    string Data;
    public:
        State(istream &i);
        void update();
        string get_Status_Text() const {return status_text;}
        bool get_show_buttons() const;
        void write_to(ostringstream &os);
        static const int offset;
        int get_username_offset() const;
        int get_mem_offset() const;
        string get_current() const {return current;}
        string get_user() const {return user;}
        string get_Data() const {return Data;}
};

void display(const State &s);
string create_image(int width, int height, int columns, int rows, int target);
string create_image();
string browse();

#endif