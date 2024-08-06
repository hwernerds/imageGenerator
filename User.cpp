#include<string>
#include<fstream>
#include<iostream>
#include<sstream>
#include"User.h"
#include"File.h"
using namespace std;

User::User(string FileName) {
    string temp = "Accounts/" + FileName;
    File myFile(temp);
    stringstream ss(myFile.ReadFromFile());
    ss >> username;
    if (ss.eof()) {
        cout << "Error With Account File .... User::User function" << endl;
    } else {
        ss >> password;
        getline(ss, temp, '|');
        getline(ss, temp, '|');
        date = temp;
        ss >> backgroundType;
        ss >> imagesDrawn;
        ss >> imagesGenerated;
    }
}

string User::get_Username() const {
    return username;
}

string User::get_Password() const {
    return password;
}

string User::get_Date() const {
    return date;
}

string User::get_BackgroundType() const {
    return backgroundType;
}

string User::get_ImagesDrawn() const {
    return imagesDrawn;
}

string User::get_ImagesGenerated() const {
    return imagesGenerated;
}

string User::get_Images() const {
    fstream f("Accounts/" + username + ".txt");
    string temp;
    getline(f, temp);
    string holder = "";
    while(!f.eof()) {
        getline(f, temp);
        holder = holder + temp;
    }
    return holder;
}

void User::Change_Password(string newPassword) {
    string file = "Accounts/" + username + ".txt";
    fstream f(file);
    string beginning;
    string temp;
    string end;
    f >> beginning;
    f >> temp;
    getline(f, end, '\0');
    f.close();
    ofstream of(file);
    of << beginning << " " << newPassword << end;
    cout << "Changed Password To:" << newPassword << endl;
    of.close();
}

void User::Set_BackgroundType(char type) {
    string file = "Accounts/" + username + ".txt";
    fstream f(file);
    string beginning;
    string temp;
    string end;
    getline(f, beginning, '|');
    getline(f, temp, '|');
    beginning = beginning + "|" + temp + "|";
    f >> temp;
    getline(f, end, '\0');
    f.close();
    ofstream of(file);
    of << beginning << " " << type << end;
    of.close();
}

void User::increment_ImagesDrawn() {
    string file = "Accounts/" + username + ".txt";
    fstream f(file);
    string beginning;
    string temp;
    string end;
    getline(f, beginning, '|');
    beginning = beginning + "|";
    getline(f, temp, '|');
    beginning = beginning + temp + "| ";
    f >> temp;
    //cout << "Temp:" << temp << endl;
    beginning = beginning + temp;
    f >> temp;
    //cout << "Temp:" << temp << endl;
    int holder = stoi(temp);
    //cout << "Holder:" << holder << endl;
    holder++;
    char ones = 0;
    char tens = 0;
    char hundreds = 0;
    temp = " ";
    //cout << "Holder:" << holder << endl;
    if (holder/100 > 0) {
        //cout << "HLSJADAJSD" << endl;
        hundreds = holder/100 + '0';
        //cout << "HUNDREDS:" << holder/100 << endl;
        holder = holder%100;
        
        temp = temp + hundreds;
        
    }
    cout << temp << endl;
    if ((holder/10 > 0) || (hundreds > 0)) {
        tens = holder/10 + '0';
        holder = holder%10;
        temp = temp + tens;
        //cout << "TENS:" << tens << endl;
    }
    //cout << "HOlder" << holder << endl;
    ones = holder + '0';
    cout << ones << endl;
    //cout << "TEMP:" << temp << endl;
    temp = temp + ones;
    //cout << "TEMP:" << temp << endl;
    getline(f, end, '\0');
    f.close();
    ofstream of(file);
    of << beginning << temp << end;
    of.close();
}

void User::increment_ImagesGenerated() {
    string file = "Accounts/" + username + ".txt";
    fstream f(file);
    string beginning;
    string temp;
    string end;
    getline(f, beginning, '|');
    beginning = beginning + "|";
    getline(f, temp, '|');
    beginning = beginning + temp + "| ";
    f >> temp;
    //cout << "Temp:" << temp << endl;
    beginning = beginning + temp + " ";
    f >> temp;
    beginning = beginning + temp;
    f >> temp;
    //cout << "Temp:" << temp << endl;
    int holder = stoi(temp);
    //cout << "Holder:" << holder << endl;
    holder++;
    char ones = 0;
    char tens = 0;
    char hundreds = 0;
    temp = " ";
    //cout << "Holder:" << holder << endl;
    if (holder/100 > 0) {
        //cout << "HLSJADAJSD" << endl;
        hundreds = holder/100 + '0';
        //cout << "HUNDREDS:" << holder/100 << endl;
        holder = holder%100;
        
        temp = temp + hundreds;
        
    }
    cout << temp << endl;
    if ((holder/10 > 0) || (hundreds > 0)) {
        tens = holder/10 + '0';
        holder = holder%10;
        temp = temp + tens;
        //cout << "TENS:" << tens << endl;
    }
    //cout << "HOlder" << holder << endl;
    ones = holder + '0';
    cout << ones << endl;
    //cout << "TEMP:" << temp << endl;
    temp = temp + ones;
    //cout << "TEMP:" << temp << endl;
    getline(f, end, '\0');
    f.close();
    ofstream of(file);
    of << beginning << temp << end;
    of.close();
}