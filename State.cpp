#include"State.h"
#include<fstream>
#include<string>
#include<sstream>
#include<ctime>
#include"File.h"
#include<iostream>
//#include"Interface.h"
#include"User.h"
#include"/usr/local/cs/cs251/react.h"
using namespace std;

const int State::offset = 0;

State::State(istream &i) {
    string holder;
    string temp;
    //getline(i, temp, '[');
    //istringstream ss(temp);
    i >> temp;
    if (temp == "0") {
        LoggedIn = false;
        //cout << "Logged In" << endl;
    } else {
        LoggedIn = true;
       // cout << "Not Logged In" << endl;
    }

    i >> temp;
    user = temp;
    //cout << "User:" << user << endl;
    i >> temp;
    password = temp;
    //cout << "Password:" << password << endl;

    i >> temp;
    current = temp;
    cout << "Current:" << current << endl;

    getline(i, temp, '|');
    //cout << temp << endl;
    getline(i, temp, '|');
    cout << "Data:";
    for(int i = 0; (i < Data.size() && i < 100); i++) {
        cout << Data[i];
    }
    cout << endl;
    Data = temp;
    //cout << "Data:" << Data << endl;
    //ss >> temp;
    //cout << temp << endl;
    if (current == "Login1" || current == "Login3") {
        getline(i, temp, '|');
        getline(i, temp, '|');
        getline(i, user, '\0');
        stringstream ss(user);
        ss >> user;
        //user.erase(0,1);
        //cout << temp << ":User2:" << user << endl;
    } else if (current == "Login2") {
        getline(i, temp, '|');
        getline(i, temp, '|');
        getline(i, password, '\0');
        stringstream ss(password);
        ss >> password;
        //password.erase(0,1);
        //cout << temp << ":Password2:" << password << endl;
    }
}

void State::write_to(ostringstream &os) {
    os << LoggedIn;
    os << " ";
    os << user;
    os << " ";
    os << password;
    os << " ";
    os << current;
    os << " ";
    cout << "Data:";
    for(int i = 0; (i < Data.size() && i < 100); i++) {
        cout << Data[i];
    }
    cout << endl;
    string s = "|" + Data + "| |" + status_text;
    //cout << "status_text:" << status_text[10] << endl;
    os << s;
}

int State::get_mem_offset() const {
    //cout << user.length() << " " << password.length() << " " << current.length() << " " << CurrentImage.length() << endl;
    //int myOffset = 
    //cout << Data.length();
    return 2 + user.length() + 1 + password.length() + 1 + current.length() + 1 + Data.length() + 2 + 2;
}

bool State::get_show_buttons() const {
    return true;
}

/*string State::get_current() const{
    return current;
}*/

void State::update() {
    /*istringstream(_global_mem + State::get_mem_offset)
    string temp;
    getline(i, temp, '~');
    getline(i, temp, '\0');*/
    //Start
    //cout << "testing5" << endl;

    if (current == "Beginnings") {
        //cout << "Testing4" << endl;
        status_text = "Go~Image Generator~i| Username~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~";
        current = "Login1";
        //cout << current << " Current " << endl;
    }
    //Logins
    else if (current == "Login1") {
        //user = i;
        current = "Login2";
        status_text = "Go~Image Generator~i| Password~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~";
    } else if (current == "Login2") {
        //password = i;
        //cout << "YYYYYY" << endl;
        string myUser = user;
        string myPassword = password;
        //cout << "The Password is: " << password << endl;
        string holder = "Accounts/" + user + ".txt";
        cout << holder << endl;
        fstream f;
        f.open("Accounts/" + user + ".txt");
        if (f.good()) {
            cout << "F is good" << endl;
            f >> holder;
            cout << "First:" << holder << endl;
            f >> holder;
            cout << "Second:" << holder << endl;
            if (holder != password) {
                current = "Login3";
                status_text = "Go~ Wrong Password~i| Username~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~";
                user = "-";
                //password = "-";
            } else {
                current = "Home";
                status_text = "Browse~Create Image~Search~";
                password = "-";
            }
        } else {
            //cout << "SDASDSADSA: " << current << endl;
            current = "Login5";
            status_text = "No Account Found, Create One?~No~Yes~";
        }
        f.close();
    } else if (current == "Login3") {
        current = "Login2";
        status_text = "Go~ Wrong Password~i|   Password~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ~";
    } else if (current == "Login5") {
        //cout << "XXXXXX" << endl;
        if (_event_id_is("button_1")) {
            string holder = "Accounts/" + user + ".txt";
            ofstream of(holder);
            fstream f;
            f.open(holder);
            of.close();
            string temp2 = "";

            time_t now = time(0);
            string date_time = ctime(&now);
            date_time[date_time.size()-1] = '|';
            temp2 = "|" + date_time;
            string output = user + " " + password + " " + temp2 + " 0 0 0\n";
            f << output;

            password = "-";

            current = "Home";
            status_text = "Browse~Create Image~Search~";
            f.close();
        } else if (_event_id_is("button_2")) {
            //cout << "WWWWWWW" << endl;
            current = "Login1";
            status_text = "Go~Image Generator~i|   Username~";
        }
    } 
    
    //Home
    
    else if (current == "Home") {
        int buttonId;
        if(_received_event()) { 
            for(int i = 0; i < 17; i++) {
                if (_event_id_is("button_",i)) {
                    buttonId = i;
                    break;
                }
            }
        } 
        if (buttonId == 1) {
            current = "CreateImage";
            status_text = "Draw Image~Generate Image~Home~~~~~~~~~~~~~";
            Data = "~";
        } else if (buttonId == 2) {
            current = "Search";
            //cout << "Searching" << endl;
            string temp;
            stringstream ss(_global_mem);
            getline(ss, temp, '|');
            getline(ss, temp, '\0');
            
            
            //CurrentImage = "1 " + InitiateSearchFunction(temp);

            //user.erase(0,1);
            //cout << temp << ":User2:" << user << endl;
            status_text = "Random~Create an Image~|           Search~";
            //XXXXXXXXXXX_CALL_FUNCTION_XXXXXXXXXXX
        } else if (buttonId == 5) {
            cout << "We Doin The Menu" << endl;
            current = "Menu1";
            status_text = "Profile~Settings~Home~";
        }
    } /*else if (current == "ImageChoice1") {
       /if (buttonId == 1) {
            status_text = "Width~Height~Columns~Rows~Target~| ~~~~~~~~| ~~~~~~~~| ~~~~~~~~| ~~~~~~~~| ~~~~~~~~Generate Image~";
        }
    }*/
    /*else if (current == "Browse") {
        if (i == "1") {
            status_text = browse() + "Go to the next page (1) or return to home (2)? ";
            //XXXXXXXXXXX_CALL_FUNCTION_XXXXXXXXXXX
        } else {
            current = "Home";
            status_text = "Welcome "  + user + ", would you like to create an image (1), browse (2), access the menu (3), or exit the program (q)? ";
        }
    }*/ else if (current == "Menu1") {
        if (_event_id_is("button_", 1)) {
            current = "Menu2";
            User myUser(user);
            int total_Images = stoi(myUser.get_ImagesDrawn()) + stoi(myUser.get_ImagesGenerated());
            cout << "TOTAL_IMAGES" << total_Images << endl;
            char ones;
            char tens;
            char hundreds;
            string total_images = " ";
            if (total_Images/100 > 0) {
                hundreds = (total_Images/100) + '0';
                total_Images = total_Images%100;
                total_images = total_images + hundreds;
            }
            cout << "TOTALIMAGES4" << total_images << endl;
            if ((total_Images/10 > 0) || (hundreds > 0)) {
                tens = (total_Images/10) + '0';
                total_Images = total_Images%10;
                total_images = total_images + tens;
            }
            cout << "TOTALIMAGES3" << total_images << endl;
            ones = ((total_Images) + '0');
            total_images = total_images + ones;
            total_images.erase(0,1);
            cout << "TOTALIMAGES2:" << total_images << endl;
            cout << "The Date:" << myUser.get_Date() << endl;
            status_text = "View Images~Total Images:~Images Generated:~Date Created:~Images Drawn:~Home~|" + user + "~|" + myUser.get_Date() + "~|" + myUser.get_ImagesGenerated() + "~|" + myUser.get_ImagesDrawn() + "~|" + total_images + "~|";
        } else if (_event_id_is("button_", 2)) {
            status_text =status_text = "Background Color~Change Password~[0Old Password~~~~~~~~~~]Home~";
            current = "Menu3";
        } else {
            status_text = "Browse~Create Image~Search~";
            current = "Home";
        }
    } else if (current == "Menu2") {
        if (_event_id_is("button_1")) {
            current = "Home";
            status_text = "Browse~Create Image~Search~";
        } else {
            User myUser(user);
            string holder = "[0 ";
            holder = holder + myUser.get_Images();
            current = "YourImages";
            status_text = holder + "]Your Images~Previous~Next~Profile~";
            /*File savedImages(user+"Images");
            string temp = savedImages.findSavedImages();
            current = "Menu1";
            status_text = "Here are your saved images:\n\n" + temp + "Would you like to access your Profile (1), Settings (2), or return to home (3)? ";*/
        }
    }  else if(current == "YourImages") {
            if(_event_id_is("button_profile")) {
                current = "Menu2";
                User myUser(user);
                cout << "Testing3" << endl;
                int total_Images = stoi(myUser.get_ImagesDrawn()) + stoi(myUser.get_ImagesGenerated());
                cout << "Testing4" << endl;
                cout << "TOTAL_IMAGES" << total_Images << endl;
                char ones;
                char tens;
                char hundreds;
                string total_images = " ";
                if (total_Images/100 > 0) {
                    hundreds = (total_Images/100) + '0';
                    total_Images = total_Images%100;
                    total_images = total_images + hundreds;
                }
                cout << "TOTALIMAGES4" << total_images << endl;
                if ((total_Images/10 > 0) || (hundreds > 0)) {
                    tens = (total_Images/10) + '0';
                    total_Images = total_Images%10;
                    total_images = total_images + tens;
                }
                cout << "TOTALIMAGES3" << total_images << endl;
                ones = ((total_Images) + '0');
                total_images = total_images + ones;
                total_images.erase(0,1);
                cout << "TOTALIMAGES2:" << total_images << endl;
                cout << "The Date:" << myUser.get_Date() << endl;
                status_text = "View Images~Total Images:~Images Generated:~Date Created:~Images Drawn:~Home~|" + user + "~|" + myUser.get_Date() + "~|" + myUser.get_ImagesGenerated() + "~|" + myUser.get_ImagesDrawn() + "~|" + total_images + "~|";
            } else if (_event_id_is("button_next")) {
                User myUser(user);
                int length = myUser.get_Images().length()/4;
                stringstream ss (_global_mem + get_mem_offset());
                string temp;
                getline(ss, temp, '[');
                ss >> temp;
                int holder = stoi(temp);
                holder++;
                if (holder > (length/4)) {
                    holder = 0;
                }
                char ones = 0;
                char tens = 0;
                char hundreds = 0;
                temp = " ";
                if (holder/100 > 0) {
                    hundreds = holder/100 + '0';
                    holder = holder%100;
                    temp = temp + hundreds;
                }
                cout << temp << endl;
                if ((holder/10 > 0) || (hundreds > 0)) {
                    tens = holder/10 + '0';
                    holder = holder%10;
                    temp = temp + tens;
                }
                ones = holder + '0';
                cout << ones << endl;
                temp = temp + ones;
                temp.erase(0,1);
                current = "YourImages";
                status_text = "[" + temp + " " + myUser.get_Images() + "]Your Images~Previous~Next~Profile~";
            } else if (_event_id_is("button_previous")) {
                User myUser(user);
                int length = myUser.get_Images().length()/4;
                stringstream ss (_global_mem + get_mem_offset());
                string temp;
                getline(ss, temp, '[');
                ss >> temp;
                int holder = stoi(temp);
                holder--;
                if (holder < 0) {
                    holder = (length/4);
                }
                char ones = 0;
                char tens = 0;
                char hundreds = 0;
                temp = " ";
                if (holder/100 > 0) {
                    hundreds = holder/100 + '0';
                    holder = holder%100;
                    temp = temp + hundreds;
                }
                cout << temp << endl;
                if ((holder/10 > 0) || (hundreds > 0)) {
                    tens = holder/10 + '0';
                    holder = holder%10;
                    temp = temp + tens;
                }
                ones = holder + '0';
                cout << ones << endl;
                temp = temp + ones;
                temp.erase(0,1);
                current = "YourImages";
                status_text = "[" + temp + " " + myUser.get_Images() + "]Your Images~Previous~Next~Profile~";
            } else {
                cout << endl;
                for(int i = 1; i < 5; i++) {
                    if (_event_id_is("button_", i)) {
                        cout << "I FOUND THE BUTTON:" << i << endl;
                        User myUser(user);
                        int max = myUser.get_Images().size()/4;
                        string temp;
                        stringstream ss(_global_mem + get_mem_offset());
                        ss.get();
                        ss >> temp;
                        int index = stoi(temp); 
                        cout << "Index:" << index << endl;
                        cout << "SSTESTING:";
                        int total = index*4 + i;
                        cout << "Going to:" << total << "| Max Is:" << max << endl;
                        for(int j = 0; j < index*4; j++) {
                            ss >> temp;
                            cout << temp;
                            max--;
                        }
                        for(int j = 0; j < i; j++) {
                            ss >> temp;
                            max--;
                        }
                        if (max < 0) {
                            temp = "000";
                            cout << "Found Max" << endl;
                        }
                        current = "ImagePage";
                        status_text = temp + "|" + GetImageInfo(stoi(temp));
                    }
                    cout << "nothing?" << endl;
                }
            }
    } else if (current == "Menu3") {
        for(int i = 2; i < 10; i++) {
            if (_event_id_is("button_", i)) {
                User myUser(user);
                char temp = ((char)(i-2)) + '0';
                myUser.Set_BackgroundType(temp);
            }
        }
        if (_event_id_is("button_", 1)) {
            current = "Home";
            status_text = "Browse~Create Image~Search~";
        } else {
            stringstream ss(_global_mem + get_mem_offset());
            User myUser(user);
            string holder = "New Password";
            string Pass1;
            string temp;
            getline(ss, temp, '[');
            char tester;
            ss >> tester;
            getline(ss, temp, ']');
            cout << "Temp:" << temp << endl;;
            stringstream ss1(temp);
            ss1 >> Pass1;
            stringstream ss2(Pass1);
            getline(ss2, Pass1, '~');
            cout << "Pass1:" << Pass1 << endl;
            if (tester == '0') {
                if (myUser.get_Password() == Pass1) {
                    current = "Menu3";
                    status_text = "Background Color~Change Password~[1New Password~~~~~~~~~~]Home~";
                } else if ((Pass1 == "Old") || (Pass1 == "Wrong") || (Pass1 == "Changed")) {
                    current = "Menu3";
                    status_text = "Background Color~Change Password~[0Old Password~~~~~~~~~~]Home~";
                }
                else {
                    current = "Menu3";
                    status_text = "Background Color~Change Password~[0Wrong Password~~~~~~~~~~]Home~";
                }
            } else {
                if (Pass1 != "New") {
                    current = "Menu3";
                    status_text = "Background Color~Change Password~[0Changed Password~~~~~~~~~~]Home~";
                    myUser.Change_Password(Pass1);
                } else {
                    current = "Menu3";
                    status_text = "Background Color~Change Password~[1New Password~~~~~~~~~~]Home~";
                }
            }
        }
    } else if (current == "CreateImage") {
        if (_event_id_is("button_", 1)) {
            Data = "7";
            for(int i = 0; i < 10*10; i++) {
                Data = Data + "1";
            }
            cout << "DATASIZE:" << Data.size() << endl;
            current = "Drawing";
            status_text = "Create Image~|Untitled~~~~~~~~~" + '\0';
        } else if(_event_id_is("button_", 2)) {
            current = "Generate1";
            status_text = "Height~Width~Number of Paths~Number of Pixels~Path Color~Create Image~Home~|50~~~~~~~~~|50~~~~~~~|4~~~~~~~|1000~~~~~~~";
        }
        else {
            current = "Home";
            status_text = "Browse~Create Image~Search~~~~~~";
        }
    } else if (current == "Drawing") {
        for(int i = 0; i < 10*10; i++) {
            if (_event_id_is("button_", 100 + i)) {
                cout << "Thing I'm changing:" << (i + 1) << endl; 
                //cout << Data[0] << ":Data0" << endl;
                cout << "Data.size():" << Data.size() << endl;
                //cout << "Data:" << Data << endl;
                cout << "I+1:" << i + 1 << endl;
                Data[i+1] = Data[0];
                current = "Drawing";
                string title;
                stringstream ss(_global_mem + get_mem_offset());
                ss.get();
                getline(ss, title, '|');
                cout << "Title" << title << endl;
                title = "";
                getline(ss, title, '\0');
                status_text = "Create Image~|" + title + "~~~~" + '\0' +"~~~~~~~~~|~";
            }
        }
        for(int i = 9; i < 17; i++) {
            if (_event_id_is("button_", i)) {
                cout << "Bad Allocation?" << endl; 
                Data[0] = ((char)(i-9) + '0');
                cout << ((int)Data[0]) << ":Data0" << endl;
                current = "Drawing";
                string title = "";
                stringstream ss(_global_mem + get_mem_offset());
                ss.get();
                getline(ss, title, '|');
                cout << "Title" << title << endl;
                title = "";
                getline(ss, title, '\0');
                //ss >> title;
                status_text = "Create Image~|" + title  + "~~~~" + '\0' +"~~~~~~~~~|~";
            }
        }
        if (_event_id_is("button_", 5)) {
            current = "DrawingCheck";
            string title;
            stringstream ss(_global_mem + get_mem_offset());
            ss.get();
            getline(ss, title, '|');
            cout << "Title" << title << endl;
            title = "";
            getline(ss, title, '\0');
            status_text = "Are you sure? Your Image won't be saved~No~Yes~[" + title + "]";
        }
        if (_event_id_is("button_", 3)) {
            string Colors[] = {"aliceblue", "white", "gold", "deepskyblue", "darkorchid", "lime", "red", "black"};
            cout << "ImageTesting2" << endl;
            File myFile("Images/ImageCounter");
            string temp = myFile.ReadFromFile();
            int ImageCounter = stoi(temp);
            ImageCounter++;
            char hundreds = ((char)((ImageCounter/100)+'0'));
            char tens = ((char)(((ImageCounter%100)/10)+'0'));
            char ones = ((char)(((ImageCounter%10)/1)+'0'));
            temp = "";
            temp = temp + hundreds + tens + ones + " ";
            myFile.AddToFile(temp);
            temp = "";
            temp = temp + hundreds + tens + ones;
            Data.erase(0,1);
            cout << "ImageTesting3" << endl;
            Pixel** myImage = new Pixel*[100];
            for(int i = 0; i < 100; i++) {
                myImage[i] = new Pixel[100];
                for(int j = 0; j < 100; j++) {
                    if (Data[((j/10)*10)+(i/10)] == '0') {
                        myImage[i][j].red = 240;
                        myImage[i][j].green = 248;
                        myImage[i][j].blue = 255;
                    } else if (Data[((j/10)*10)+(i/10)] == '1') {
                        myImage[i][j].red = 255;
                        myImage[i][j].green = 255;
                        myImage[i][j].blue = 255;
                    } else if (Data[((j/10)*10)+(i/10)] == '2') {
                        myImage[i][j].red = 255;
                        myImage[i][j].green = 215;
                        myImage[i][j].blue = 0;
                    } else if (Data[((j/10)*10)+(i/10)] == '3') {
                        myImage[i][j].red = 0;
                        myImage[i][j].green = 191;
                        myImage[i][j].blue = 255;
                    } else if (Data[((j/10)*10)+(i/10)] == '4') {
                        myImage[i][j].red = 153;
                        myImage[i][j].green = 50;
                        myImage[i][j].blue = 204;
                    } else if (Data[((j/10)*10)+(i/10)] == '5') {
                        myImage[i][j].red = 50;
                        myImage[i][j].green = 255;
                        myImage[i][j].blue = 8;
                    } else if (Data[((j/10)*10)+(i/10)] == '6') {
                        myImage[i][j].red = 255;
                        myImage[i][j].green = 0;
                        myImage[i][j].blue = 0;
                    } else if (Data[((j/10)*10)+(i/10)] == '7') {
                        myImage[i][j].red = 0;
                        myImage[i][j].green = 0;
                        myImage[i][j].blue = 0;
                    }
                }
            }
            cout << "ImageTesting4" << endl;
            string title;
            stringstream ss(_global_mem + get_mem_offset());
            ss.get();
            getline(ss, title, '|');
            cout << "Title" << title << endl;
            title = "";
            getline(ss, title, '\0');
            stringstream tss(title);
            getline(tss, title, '~');
            //stringstream ss2(title);
            //ss2 >> title;
            Data = "-";
            FileImage(100, 100, 0, temp, title, user, myImage, "");
            current = "ImagePage";
            //temp = GetImageInfo(stoi(temp));
            temp = "";
            temp = temp + hundreds + tens + ones;
            status_text = temp + "|" + GetImageInfo(stoi(temp));
        }
        //100-355 = Pixels;
    } else if (current == "DrawingCheck") {
        if (_event_id_is("button_", 1)) {
            current = "Drawing";
            string title;
            stringstream ss(_global_mem + get_mem_offset());
            stringstream oss(_global_mem + get_mem_offset());
            char holder;
            cout << "oss:";
            for(int i = 0; i < 100; i++) {
                oss >> holder;
                cout << holder;
            }
            cout << endl;
            ss.get();
            getline(ss, title, '[');
            cout << "Title:" << title << endl;
            title = "";
            getline(ss, title, ']');
            //cout << "TITLE:" << title << endl;
            status_text = "Create Image~|" + title + "~~~" + '\0' + " |~";
        } else if (_event_id_is("button_", 2)) {
            current = "Home";
            Data = "_";
            status_text = "Browse~Create Image~Search~";
        }
    } else if (current == "ImagePage") {
        if (_event_id_is("button_", 5)) {
            current = "Home";
            status_text = "Browse~Create Image~Search~";
        }
    } else if (current == "Generate1") {
        if(_event_id_is("button_generate")){
            current = "ImagePage";
            string Colors[] = {"aliceblue", "white", "gold", "deepskyblue", "darkorchid", "lime", "red", "black"};
            cout << "ImageTesting2" << endl;
            File myFile("Images/ImageCounter");
            string temp = myFile.ReadFromFile();
            int ImageCounter = stoi(temp);
            ImageCounter++;
            char hundreds = ((char)((ImageCounter/100)+'0'));
            char tens = ((char)(((ImageCounter%100)/10)+'0'));
            char ones = ((char)(((ImageCounter%10)/1)+'0'));
            temp = "";
            temp = temp + hundreds + tens + ones + " ";
            myFile.AddToFile(temp);
            temp = "";
            temp = temp + hundreds + tens + ones;
                        string title;
            stringstream ss(_global_mem + get_mem_offset());
            ss.get();
            getline(ss, title, '|');
            cout << "Title" << title << endl;
            title = "";
            getline(ss, title, '\0');
            stringstream tss(title);
            getline(tss, title, '~');
            //stringstream ss2(title);
            //ss2 >> title;
            Data = "-";
            current = "ImagePage";
            //temp = GetImageInfo(stoi(temp));
            temp = "";
            temp = temp + hundreds + tens + ones;
            status_text = temp + "|" + GetImageInfo(stoi(temp)); 
        }
        //Data = i + "~";
        //status_text = "Width~Height~Columns~Rows~Target~4~4~2~1~3~Generate Image~Home";
        //ss.close();
    }
    /**    current = "Generate2";
    } else if (current == "Generate2") {
        Data[Data.size()-1] = " ";
        //Data = Data + i + "~";
        status_text = "Width~Height~Columns~Rows~Target~4~4~2~1~3~Generate Image~Home";
        //ss.close();
        current = "Generate3";
    } else if (current == "Generate3") {
        Data[Data.size()-1] = " ";
        //Data = Data + i + "~";
        status_text = "Width~Height~Columns~Rows~Target~4~4~2~1~3~Generate Image~Home";
        //ss.close();
        current = "Generate4";
    } else if (current == "Generate4") {
        Data[Data.size()-1] = " ";
        //Data = Data + i + "~";
        status_text = "Width~Height~Columns~Rows~Target~4~4~2~1~3~Generate Image~Home";
        //ss.close();
        current = "Generate5";
    } else if (current == "Generate5") {
        if (_event_id_is("button_generate")){
            Data[Data.size()-1] = " ";
            Data = Data + i + "~";
            stringstream ss(Data);
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
            status_text = "Here is your image:\n"+tempstr+"\nWould you like to save your image (y or n)?";*/
            /*current = "Generate6";
        } else if(_event_id_is("button_home")){
            current = "Home";
            status_text = "Create Image~Browse~";
        }
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
    */
    cout << endl;
    for(int i = 0; (i < status_text.size() && i < 100); i++) {
        cout << status_text[i];
    }
    cout << endl;
}

/*string State::get_Status_Text() const {
    return status_text;
}*/
