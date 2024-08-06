#include"State.h"
#include"User.h"
#include<string>
#include"File.h"
#include"/usr/local/cs/cs251/react.h"
using namespace std;

void display(const State &s) {
    
    //cerr << s.get_current() << " Its Working!!!! " /* << s.get_Status_Text()*/ <<endl;
    //_add_yaml("Login0.yaml");
    //cout << "Current =" << s.get_current() << endl;
    string BColor = "azure";
    int offset = s.get_mem_offset();
    string current = s.get_current();
    if (current != "Login1" && current != "Login2" && current != "Login3" && current != "Login4" && current != "Login5") {
        cout << "BCOLOR:" << BColor << endl;
        User theUser(s.get_user());
        BColor = theUser.get_BackgroundType();
        if (BColor == "0") {
            BColor = "azure";
        } else if (BColor == "1") {
            BColor = "khaki";
        } else if (BColor == "2") {
            BColor = "palegreen";
        } else if (BColor == "3") {
            BColor = "mediumturquoise";
        } else if (BColor == "4") {
            BColor = "lightpink";
        } else if (BColor == "5") {
            BColor = "darksalmon";
        } else if (BColor == "6") {
            BColor = "rgb(245,245,220)";
        } else if (BColor == "7") {
            BColor = "darkkhaki";
        }
    }

    string Colors[] = {"aliceblue", "white", "gold", "deepskyblue", "darkorchid", "lime", "red", "black"};
    
    //cout << s.get_Status_Text() << endl;

    /*_add_yaml("DrawBase.yaml", {{"BColor", BColor}, {"index_1", 13 + offset}, {"index_2", 0 + offset}});
        string data = s.get_Data();
        for(int x = 0; x < 10; x++) {
            for(int y = 0; y < 10; y++) {
                char hundreds = ((char)(((x*10)+y)/100)+'1');
                char tens = ((char)((((x*10)+y)%100)/10)+'0');
                char ones = ((char)((((x*10)+y)%10)/1)+'0');
                string id = "button_";
                id = id + hundreds + tens + ones;
                _add_yaml("DrawButton.yaml", {{"id", id}, {"Color", Colors[data[(x*10)+y+1]-'0']}, {"XValue", (10 + (30*x))}, {"YValue", (10 + 30*y)}});
            }
        }*/


    if (s.get_current() == "Login1" || s.get_current() == "Login2" || s.get_current() == "Login3") {
        _add_yaml("Login1.yaml", {{"index_1", 3 + offset}, {"index_2", 0 + offset}, {"index_3", 22 + offset}});
    } else if (s.get_current() == "Login5") {
        cout << "indexing maker" << endl;
        _add_yaml("Login5.yaml", {{"index_1", 0 + offset}, {"index_2", 33 + offset},{"index_3", 30 + offset}});
        //_add_yaml("Login5.yaml", {{"index_1", 0 + s.get_mem_offset()}, {"index_2", 303 + s.get_mem_offset()}, {"index_3", 30 + s.get_mem_offset()}});
    } else if (s.get_current() == "Home"){
        _add_yaml("Home.yaml", {{"BColor", BColor}, {"index_1", 7 + offset}, {"index_2", 0 + offset}, {"index_3", 20 + offset}});
    } else if (s.get_current() == "Menu1") {
        //cout << "Menu1!!!!" << endl;
        _add_yaml("Menu1.yaml", {{"BColor", BColor}, {"index_1", 0 + offset}, {"index_2", 8 + offset}, {"index_3", 17 + offset}});
    } else if (s.get_current() == "Menu2") {
        //User theUser(s.get_user());
        string temp;
        stringstream ss(s.get_Status_Text());
        getline(ss, temp, '|');
        int username_offset = temp.size() + 1 + offset;
        getline(ss, temp, '|');
        int date_offset = temp.size() + 1 + username_offset;
        getline(ss, temp, '|');
        int generated_offset = temp.size() + 1 + date_offset;
        getline(ss, temp, '|');
        int drawn_offset = temp.size() + 1 + generated_offset;
        
        getline(ss, temp, '|');
        int total_offset = temp.size() + 1 + drawn_offset;
        //int image_Offset = temp.size() + 1 + drawn_offset;
        _add_yaml("Menu2.yaml", {{"BColor", BColor}, {"index_1", username_offset}, {"index_2", generated_offset}, {"index_3", drawn_offset}, {"index_4", total_offset}, {"index_5", date_offset}, {"index_6", 44+offset}, {"index_7", 26 +offset}, {"index_8", 58 + offset}, {"index_9", 12 + offset}, {"index_10", 72 + offset}, {"index_11", 0 + offset}});
    } else if (s.get_current() == "YourImages") {
        string holder = s.get_Status_Text();
        cout << "Testing4:" << holder << "|" << endl;
        User myUser(s.get_user());
        stringstream ss(holder);
        getline(ss, holder, '[');
        cout << "Testing3:" << holder << "|" << endl;
        ss >> holder;
        cout << "Testing1:" << holder << "|" << endl;
        int CurrentPage = stoi(holder);
        cout << "Testing2" << endl;
        int max = myUser.get_Images().size()/4;
        int counter = 0;
        for(int i = 0; (i < CurrentPage) && (i*4 < max); i++) {
            ss >> holder;
            ss >> holder;
            ss >> holder;
            ss >> holder;
            counter = i*4;
        }
        char ImageCounter = '0';
        //string temp = "| Test: Image_" + ((char)ImageCounter + '0');
        cout << "Counter:" << counter << "| Max:" << max << endl;
        if (max - counter > 4) {
            max = counter + 4;
        }
        string temp2 = "Image_";
        string temp = temp2 + ImageCounter;
        while(counter < max) {
            temp = temp2 + ImageCounter;
            cout << "XXXXX |" << temp << endl;
            ss >> holder;
            holder.erase(3, 1);
            ConvertImage(holder, temp);
            ImageCounter++;
            counter++;
        }
        temp2 = "Image_";
        temp = temp2 + ImageCounter;
        cout << "ImageCounter:" << ImageCounter << endl;
        string temp3 = "000";
        while (ImageCounter < '4') {
            temp = temp2 + ImageCounter;
            cout << "TEMP:" << temp << endl;
            ConvertImage(temp3, temp);
            ImageCounter++;
        }
        int ImageOffset = offset;
        holder = s.get_Status_Text();
        stringstream tss(holder);
        getline(tss, holder, ']');
        ImageOffset += holder.size() + 1;

        _add_yaml("your_images.yaml", {{"BColor", BColor}, {"img1", "Image_0.png"}, {"img2", "Image_1.png"},{"img3", "Image_2.png"},{"img4", "Image_3.png"}, {"index_1", 0 + ImageOffset}, {"index_2", 12 + ImageOffset}, {"index_3", 21 + ImageOffset}, {"index_4", 26 + ImageOffset}});
    } else if (s.get_current() == "Menu3") {
        stringstream ss(s.get_Status_Text());
        cout << "Global:";
        for(int i = 0; (i < 100); i++) {
            cout << _global_mem[i];
        }
        cout << endl;
        string temp;
        getline(ss, temp, '[');
        cout << "Temp:";
        for(int i = 0; (i < 100 && i < temp.size()); i++) {
            cout << temp[i];
        }
        cout << endl;
        int OldIndex = temp.size() + 2 + offset;
        getline(ss, temp, ']');
        cout << "Temp:";
        for(int i = 0; (i < 100 && i < temp.size()); i++) {
            cout << temp[i];
        }
        cout << endl;
        int HomeIndex = temp.size() + OldIndex;

        _add_yaml("Menu3.yaml", {{"BColor", BColor}, {"index_1", 0 + offset}, {"index_3", OldIndex}, {"index_4", HomeIndex}, {"index_5", 17 + offset}});
    } else if (current == "CreateImage") {
        _add_yaml("CreateImage.yaml", {{"BColor", BColor}, {"index_1", 0 + offset}, {"index_2", 11 + offset}, {"index_3", 26 + offset}});
    } else if (current == "Drawing") {
        _add_yaml("DrawBase.yaml", {{"BColor", BColor}, {"index_1", 14 + offset}, {"index_2", 0 + offset}});
        string data = s.get_Data();
        //cout << "Data[1]:" << (int)data[1] << endl;
        //cout << Colors[(data[(5*10)+4+1]-'0')] << endl;
        //cout << "Middle" << endl;
        for(int x = 0; x < 10; x++) {
            for(int y = 0; y < 10; y++) {
                char hundreds = ((char)(((x*10)+y)/100)+'1');
                char tens = ((char)((((x*10)+y)%100)/10)+'0');
                char ones = ((char)((((x*10)+y)%10)/1)+'0');
                string id = "button_";
                id = id + hundreds + tens + ones;
                if (((int)(data[(x*10)+y+1]-'0') > 7) || ((int)(data[(x*10)+y+1]-'0') < 0)) {
                    cout << "I FOUND THE THING:" << (int)(data[(x*10)+y+1]-'0') << endl;
                    int temp = (int)(data[(x*10)+y+1]-'0');
                    cout << "X:" << x << "  Y:" << y << endl;
                    cout << temp << endl;
                }
                //cout << "Testing3:" << (int)(data[(x*10)+y+1]-'0') << endl;
                if ((int)data[1] < 47) {
                    //cout << "COlors :) :" << Colors[(int)(data[(x*10)+y+1])] << endl;
                    _add_yaml("DrawButton.yaml", {{"id", id}, {"Color", Colors[(int)(data[(x*10)+y+1])]}, {"XValue", (1 + (30*x))}, {"YValue", (2 + 30*y)}});
                } else {
                    //cout << "COlors :( :" << Colors[(int)(data[(x*10)+y+1]-'0')] << endl;
                    _add_yaml("DrawButton.yaml", {{"id", id}, {"Color", Colors[(int)(data[(x*10)+y+1]-'0')]}, {"XValue", (1 + (30*x))}, {"YValue", (2 + 30*y)}});
                }
            }
        }
        //cout << "Finished" << endl;
    } else if (current == "DrawingCheck") {
        _add_yaml("DrawingCheck.yaml", {{"BColor", BColor}, {"index_1", 0 + offset}, {"index_2", 40 + offset}, {"index_3", 43 + offset}});
    } else if (current == "ImagePage") {
        //cout << "Status:" << s.get_Status_Text() << endl;
        stringstream ss(s.get_Status_Text());
        string temp;
        string holder;
        getline(ss, holder, '|');
        cout << "Holder:" << holder << endl;
        int ImageOffset = 0 + offset;
        int IdOffset = holder.size() + 1 + ImageOffset;
        getline(ss, temp, '|');
        int TypeOffset = temp.size() + 5 + ImageOffset;
        holder = ConvertImage(holder, "Image_1");
        getline(ss, temp, '|');
        int NameOffset = temp.size() + 1 + TypeOffset;
        getline(ss, temp, '|');
        cout << "Name Size:" << temp.size() << " :" << temp << endl;
        int CreatorOffset = temp.size() + 1 + NameOffset;
        getline(ss, temp, '|');
        cout << "Creator Size:" << temp.size() << " :" << temp << endl;
        int DateOffset = temp.size() + 1 + CreatorOffset;
        _add_yaml("ImagePage.yaml", {{"BColor", BColor}, {"img_1", holder}, {"index_1", NameOffset}, {"index_2", CreatorOffset}, {"index_3", TypeOffset}, {"index_4", IdOffset}, {"index_5", DateOffset}});
    } else if (current == "Generate1"){
        _add_yaml("GenerateImage.yaml", {{"BColor", BColor}, {"index_0", 0 + offset}, {"index_1", 7 + offset}, {"index_2", 13 + offset}, {"index_3", 29 + offset}, {"index_4", 46 + offset}, {"index_5", 57 + offset}, {"index_6", 70 + offset}, {"index_7", 76 + offset}, {"index_8", 88 + offset}, {"index_9", 98 + offset}, {"index_10", 107 + offset}});
    }
}
