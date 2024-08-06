#include"State.h"
#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
#include"Interface.h"
#include"/usr/local/cs/cs251/react.h"
using namespace std;

const int State::offset = 0;

State::State(istream &i) {
    string holder;
    string temp;
    getline(i, temp, '~');
    istringstream ss(temp);
    ss >> temp;
    if (temp == "0") {
        LoggedIn = false;
    } else {
        LoggedIn = true;
    }
    ss >> temp;
    user = temp;
    ss >> temp;
    password = temp;
    ss >> temp;
    current = temp;
    getline(i, CurrentImage, '~');
    if (current == "Login1") {
        getline(i, temp, '~');
        getline(i, user, '\0');
    } else if (current == "Login2") {
        getline(i, temp, '~');
        getline(i, password, '\0');
    }
}

void State::write_to(ostringstream &os) {
    os << LoggedIn;
    os << user;
    os << password;
    os << current;
    string s = CurrentImage + "~" + status_text;
    os << s;
}

int State::get_username_offset() const {
    return 1+1;
}

int State::get_mem_offset() const {
    return get_username_offset() + password.length() + 1 + current.length() + 1 + CurrentImage.length() + 1;
}

bool State::get_show_buttons() const {
    return true;
}

void State::update() {
    istringstream(_global_mem + State::get_mem_offset);
    string temp;
    getline(i, temp, '~');
    getline(i, temp, '\0');
    
    //Start
    bool is_new_game = _received_event() && _event_id_is("new_game");
    if (_just_starting() || is_new_game) {
        //cout << "Testing4" << endl;
        status_text = "  Go\0 Image Generator\0i~   Username\0";
        current = "Login1";
    } 
    
    //Logins
    else if (_event_id_is("button_go")) {
        //user = i;
        current = "Login2";
        status_text ="   Go\0 Image Generator\0i~   Password\0";
    } else if (_event_id_is("button_go2")) {
        //password = i;
        //cout << "YYYYYY" << endl;
        File accounts("Accounts");
        string Search = accounts.SearchForAccount(user, password);
        if (Search == "Wrong Password") {
            current = "Login1";
            status_text = "Go\0 Wrong Password\0i~   Username\0";
            password = "-";
        } else if (Search == "Logged in") {
            current = "Home";
            status_text = "Welcome " + user + ", would you like to create an image (1), browse (2), access the menu (3), or exit the program (q)? ";
            password = "-";
        } else {
            //cout << "SDASDSADSA: " << current << endl;
            current = "Login3";
            status_text = "No Account Found, Create One?\0       No\0     Yes\0";
        }
    } else if (current == "Login3") {
        //cout << "XXXXXX" << endl;
        if (_event_id_is("yes")) {
            File accounts("Accounts");
            accounts.AddToFile("|-- " + user + " " + password + " --|", -1);
            password = "-";

            current = "Home";
            status_text = "Create Image\0Browse\0";
        } else if (_event_id_is("no")) {
            //cout << "WWWWWWW" << endl;
            current = "Login1";
            status_text ="   Go\0 Image Generator\0i~   Username\0";
        }
    } 
    
    //Home
    else if (current == "Home") {
        if (_event_id_is("create")) {
            current = "Generate1";
            status_text = "Please enter the width of the image: ";
            CurrentImage = "~";
        } else if (i == "2") {
            current = "Browse";
            //cout << "Browsing" << endl;
            status_text = browse() + "Go to the next page (1) or return to home (2)? ";
            //XXXXXXXXXXX_CALL_FUNCTION_XXXXXXXXXXX
        } else if (i == "3") {
            current = "Menu1";
            status_text = "Would you like to access your Profile (1), Settings (2), or return to home (3)? ";
        }
    } else if (current == "Browse") {
        if (i == "1") {
            status_text = browse() + "Go to the next page (1) or return to home (2)? ";
            //XXXXXXXXXXX_CALL_FUNCTION_XXXXXXXXXXX
        } else {
            current = "Home";
            status_text = "Welcome "  + user + ", would you like to create an image (1), browse (2), access the menu (3), or exit the program (q)? ";
        }
    } else if (current == "Menu1") {
        if (i == "1") {
            current = "Menu2";
            status_text = "Would you like to view your saved images (1) or return to the menu (2)? ";
        } else if (i == "2") {
            status_text = "No settings are available as of yet, returning back to the menu\n\nWould you like to access your Profile (1), Settings (2), or return to home (3)? ";
            current = "Menu1";
        } else if (i == "3") {
            status_text = "Returning to home\n\nWelcome "  + user + ", would you like to create an image (1), browse (2), access the menu (3), or exit the program (q)? ";
            current = "Home";
        }
    } else if (current == "Menu2") {
        if (i == "1") {
            File savedImages(user+"Images");
            string temp = savedImages.findSavedImages();
            current = "Menu1";
            status_text = "Here are your saved images:\n\n" + temp + "Would you like to access your Profile (1), Settings (2), or return to home (3)? ";
        }
    } else if (current == "Generate1") {
        CurrentImage = i + "~";
        status_text = "Please enter the height of the image: ";
        //ss.close();
        current = "Generate2";
    } else if (current == "Generate2") {
        CurrentImage[CurrentImage.size()-1] = " ";
        CurrentImage = CurrentImage + i + "~";
        status_text = "Please enter the number of Columns for the image: ";
        //ss.close();
        current = "Generate3";
    } else if (current == "Generate3") {
         CurrentImage[CurrentImage.size()-1] = " ";
        CurrentImage = CurrentImage + i + "~";
        status_text = "Please enter the number of Rows for the image: ";
        //ss.close();
        current = "Generate4";
    } else if (current == "Generate4") {
        CurrentImage[CurrentImage.size()-1] = " ";
        CurrentImage = CurrentImage + i + "~";
        status_text = "Please enter the number of value you want to fill the image with: ";
        //ss.close();
        current = "Generate5";
    } else if (current == "Generate5") {
         CurrentImage[CurrentImage.size()-1] = " ";
        CurrentImage = CurrentImage + i + "~";
        stringstream ss(CurrentImage);
        int width;
        ss >> width;
        //width = (int)width - '0';
        int height;
        ss >> height;
        //height = (int)height - '0';
        int columns;
        ss >> columns;
        //columns = (int)columns - '0';
        int rows;
        ss >> rows;
        //rows = (int)rows - '0';
        int value;
        ss >> value;
        //value = (int)value - '0';
        //ss.close();
        //cout << "testing" << endl;
        //cout << "Width: " << width << "  Height: " << height << "  Columns: " << columns << "  Rows: " << rows << "  Target: " << value << endl;
        CurrentImage = create_image(width, height, columns, rows, value);
        string tempstr = "";
        char temp;
        //cout << "testing2" << endl;
        stringstream t(CurrentImage);
        ss.swap(t);
        ss >> temp;
        width = (int)(temp-'0');
        cout << "Width: " << width << endl;;
        ss >> temp;
        height = (int)(temp-'0');
        cout << "Height: " << height << endl;;
        for(int i = 0; i < height; i++) {
            tempstr += "\t\t[";
            for(int j = 0; j < width; j++) {
                ss >> temp;
                tempstr = tempstr + " " + temp;
            }
            tempstr += "]\n";
        }
        status_text = "Here is your image:\n"+tempstr+"\nWould you like to save your image (y or n)?";
        current = "Generate6";
    } else if (current == "Generate6") {
        if (i == "y") {
            File SavedImages(user+"Images");
            SavedImages.AddToFile(("| " + CurrentImage), -1);
            status_text = "Saving... Would you like to create another image (1) or return to home (2)?: ";
        } else {
            status_text = "Alright, would you like to create another image (1) or return to home (2)?: ";
        }
        current = "Generate7";
    } else if (current == "Generate7") {
        if (i == "1") {
            current = "Generate1";
            status_text = "Please enter the width of the image: ";
            CurrentImage = "";
        } else {
            status_text = "Welcome "  + user + ", would you like to create an image (1), browse (2), access the menu (3), or exit the program (q)? ";
            current = "Home";
        }
    }
}

string State::get_Status_Text() const {
    return status_text;
}