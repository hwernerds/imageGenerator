#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
#include"File.h"
#include"State.h"
#include"User.h"
#include<stdio.h>
//#include"Image.cpp"
#include"/usr/local/cs/cs251/react.h"
using namespace std;

void FileImage(int width, int height, int type, string id, string Title, string Creator, Pixel** MyImage, string prompt) {
    cout << "TOTAL MESSAGE:" << id << " " << Creator << endl;
    cout << "Title:";
    for(int i = 0; (i < Title.size()&&i<20); i++) {
        cout << Title[i];
    }
    cout << endl;
    Title.substr(0,15);
    //cout << "Reached The beginning" << endl;
    string temp;
    string imageId;
    //cout << "working" << endl;
    temp = "mkdir Images/" + id;
    system(temp.c_str());
    ofstream of;
    temp = "Images/" + id + "/ImageInfo.txt";
    of.open(temp.c_str());
    if (!of.good()) {
        cout << "Failure to create file" << endl;
        return;
    }
    char myType = ((char)type+'0');
    temp = id + " " + myType + " " + Title + " " + Creator + " |";
    time_t now = time(0);
    string date_time = ctime(&now);
    date_time[date_time.size()-1] = '|';
    temp = temp + date_time;
    User myUser(Creator);
    if (type == 0) {
        cout << "Type0" << endl;
        myUser.increment_ImagesDrawn();
    } else {
        myUser.increment_ImagesGenerated();
    }
    //cout << "Reached The Middle" << endl;
    //cout << "Temp is:" << temp << endl;
    of << temp;
    temp = "Images/" + id + "/ImageData.ppm";
    of.close();
    ofstream of2(temp);
    temp = "Images/" + id + "/ImageData.ppm";
    _write_image(temp.c_str(), reinterpret_cast<char **>(MyImage), width, height);
    //cout << "Past System" << endl;

    File myFile("Accounts/"+Creator);
    id = id + " ";
    myFile.AddToFile(id, -1);
    //cout << "Reached The End" << endl;
}

string GetImageInfo(int id) {
    string myId = "000";
    if (id/100 > 0) {
        myId[0] = (char)(id/100)+'0';
        id = id%100;
    }
    if (id/10 > 0) {
        myId[1] = (char)(id/10)+'0';
        id = id%10;
    }
    myId[2] = (char)(id)+'0';
    File myFile("Images/"+myId + "/ImageInfo");
    string temp = myFile.ReadFromFile();
    string returnValue = "Image Id: " + myId + "~|";
    stringstream ss(temp);
    ss >> temp;
    ss >> temp;
    if (temp == "0") {
        returnValue = returnValue + "Image Type: Drawn~|";
    } else  {
        returnValue = returnValue + "Image Type: Generated~|";
    }
    ss >> temp;
    returnValue = returnValue + temp + "~|";
    ss >> temp;
    returnValue = returnValue + "Creator: " + temp + "~|";
    getline(ss, temp, '|');
    getline(ss, temp, '|');
    returnValue = returnValue + "Date Created: " + temp + "~|";
    //cout << "ReturnValue:" << returnValue << endl;
    return returnValue;
}

string GetImagePath(int id) {
    string myId = "000";
    if (id/100 > 0) {
        myId[0] = (char)(id/100)+'0';
        id = id%100;
    }
    if (id/10 > 0) {
        myId[1] = (char)(id/10)+'0';
        id = id%10;
    }
    myId[2] = (char)(id)+'0';
    return "Images/" + myId + "/ImageData.png";
}

string ConvertImage(string id, string name) {
    if (id == "]Yor") {
        id = "000";
        cout << "Found the yor?" << endl;
    }
    cout << "id:" << id << endl;
    string temp = "convert Images/" + id + "/ImageData.ppm " + name + ".png";
    cout << temp << endl;
    system(temp.c_str());
    return name + ".png";
}