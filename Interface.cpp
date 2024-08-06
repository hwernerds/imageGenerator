#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
using namespace std;
#include"Interface.h"
#include"File.h"

User::User() {
    while (true) {
        cout << "Username: ";
        cin >> user;
        cout << "Password: ";
        cin >> password;
        cout << endl;
        File accounts("Accounts");
        string Search = accounts.SearchForAccount(user, password);
        if (Search == "Wrong Password") {
            cout << Search << ". Please try again" << endl;
            continue;
        } else if (Search == "Logged in") {
            cout << Search << endl;
            break;
        } else {
            cout << Search << ". Want to create an account with that Username and Password? (Y or N)" << endl;
            char temp;
            cin >> temp;
            if (temp == 'Y') {
                accounts.AddToFile("|-- " + user + " " + password + " --|", -1);
                cout << "Account Created" << endl;
                break;
            } else {
                cout << "Alright, please try logging in again" << endl;
            }
        }
    }
}

string User::get_user(){
    return user;
}

string User::get_password(){
    return password;
}

void Program::welcome(){
    int x;
    cout << "Welcome " << bob.get_user() << ", would you like to create an image (1), browse (2), access the menu (3), or exit the program (4)?";
    cin >> x;
    if(x==1){
        createImage();
        welcome();
    } else if (x==2){
        browse();
        welcome();
    } else if (x==3){
        menu();
        welcome();
    } else if (x==4){
        return;
    }
}

void Program::createImage(){
    int x;
    char c;
    int** img;
    cout << "Enter an integer between 1 and 3: ";
    cin >> x;
    if (x==1){
        img=createArray1(4, 4);
    } else if (x==2){
        img=createArray2(4, 4);
    } else if (x==3){
        img=createArray3(4, 4);
    }
    print(img, 4, 4);
    cout << "Would you like to save your image? (y for Yes and n for No)";
    cin >> c;
    if (c=='y'){
        saveImage(img, 4, 4);
    } else if (c=='n'){
        return;
    }
}

void Program::browse(){
    char x;
    char c;
    int** img;
    cout << "What prompt would you like to use? (r for rows, c for columns, s for squares)";
    cin >> x;
    if (x=='r'){
        img=createArray1(4, 4);
    } else if (x=='c'){
        img=createArray2(4, 4);
    } else if (x=='s'){
        img=createArray3(4, 4);
    }
    print(img, 4, 4);
    cout << "Would you like to save your image? (y for Yes and n for No)";
    cin >> c;
    if (c=='y'){
        saveImage(img, 4, 4);
    } else if (c=='n'){
        return;
    }
}

void Program::menu(){
    char c;
    cout << "Would you like to access your Profile (p) or Settings (s)?";
    cin >> c;
    if (c=='p'){
        profile();
        return;
    } else if(c=='s'){
        settings();
        return;
    }
}
void Program::saveImage(int** img, int h, int w){
    File file(bob.get_user());
    ostringstream oss;
    oss << "|-- " << h << " " << w << " ";
    char temp;
    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j ++){
            oss << img[i][j];
        }
    }
    oss << "--|";
    string s = oss.str();
    cout << "Image: " << s << endl;
    file.AddToFile(s, -1);
}

void Program::profile(){
    char c;
    cout << "Here is some information about your profile: " << endl;
    cout << "Your username is: " << bob.get_user() << endl;
    cout << "Would you like to access your saved images? (y for Yes, n for No)";
    cin >> c;
    cout << endl;
    if (c=='y'){
        //ifstream is(bob.get_user()+".txt");  
        printSavedImages();
        return;  
    } else if (c=='n'){
        return;
    }
}

void Program::settings(){
    char c;
    cout << "Would you like to change the Font(f) or Brightness(b) or None (n)?";
    cin >> c;
    if(c=='f'){
        return;
    } else if (c=='b'){
        return;
    } else if (c=='n'){
        return;
    }
}

int** Program::createArray(int h, int w){
    int** image;
    image = new int*[h];
    for(int i = 0; i < h; i++){
        image[i] = new int[w];
    }
    return image;
}
    
int** Program::createArray1(int h, int w){
    int** image=createArray(h, w);
    for(int i=0; i < h; i++){
        for(int j=0; j < w; j++){
            image[i][j]=i;
        }
    }
    return image;
}
    
int** Program::createArray2(int h, int w){
    int** image=createArray(h, w);
    for(int i=0; i < h; i++){
        for(int j=0; j < w; j++){
            image[i][j]=j;
        }
    }
    return image;
}
    
int** Program::createArray3(int h, int w){
    int** image=createArray(h, w);
    for(int i=0; i < h/2; i++){
        for(int j=0; j < w; j++){
            image[i][j]=1;
        }
    }
    for(int i=h/2; i < h; i++){
        for(int j=0; j < w; j++){
            image[i][j]=2;
        }
    }   
    return image;
}

void Program::printSavedImages(){
    File file(bob.get_user());
    int counter = 0;
    string line = file.ReadFromFile(counter);
    int height, width;
    char tmp;
    //cout << "Line: " << line << endl;
    string temp;
    

    while(line != "End"){
        if (line[0] != '|') {
            line = file.ReadFromFile();
            //cout << "Continuing" << endl;
            continue;
        }
        stringstream ss(line);
        ss >> temp;
        //cout << temp << endl;
        //ss.get();
        ss >> height;
        //cout << height << endl;
        //ss.get();
        ss >> width;
        //cout << width << endl;
        //s.get();
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                ss >> tmp;
                cout << tmp << ' ';
            }
            cout << endl;
        }
        cout << endl;
        counter++;
        line = file.ReadFromFile();
        //cout << "Line2" << line << endl;
    }
}

void Program::print(int** img, int h, int w){
    cout << "This is your image!" << endl << endl;
    for(int i=0; i < h; i++){
        for(int j=0; j < w; j++){
            cout << img[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << "Here is some information about your image: " << endl;
    FindColumns(img);
    FindRows(img);
}

int Program::moveUpColumn(int** image, int x, int y) {
    int holder = 1;
    if (x > 0) {
        if (image[x][y] == image[x-1][y]) {
            holder += moveUpColumn(image, x-1, y);
            //cout << "Holder: " << holder << "  X: " << x << "  Y: " << y << endl;
            return holder;
        }
    }
    //cout << "Holder: " << holder << "  X: " << x << "  Y: " << y << endl;
    return holder;
}

void Program::FindColumns(int** image) {
    /*for(int i = 0; i < 3; i++) {
        cout << "[";
        for(int j = 0; j < 3; j++) {
            cout << " " << image[i][j];
        }
        cout << "]" << endl;
    }*/
    int height = 3;
    //while (image[height++]) {}
    int width = 3;
    //while (image[0][width++]) {}
    vector<string> holder;
    //cout << "hw " << height << " " << width << endl;
    int bottom[3];
    for(int i = 0; i < 3; i++) {
        bottom[i] = height-1;
    }
    //cout << bottom[1] << endl;
    int lengthOfColumn = 0;
    int counter = 0;
    for(int i = height-1; i > 0; i--) {
        //cout << "testing 2" << endl;
        lengthOfColumn = 1;
        //cout << "testingi " << i << endl;
        for(int j = 0; j < width && i == bottom[j]; j++) {
            lengthOfColumn = moveUpColumn(image, i, j);
            //cout << "testingj " << j << " " << lengthOfColumn << endl;
            if (lengthOfColumn > 1) {
                //cout << "Pushing Back" << endl;
                counter++;
                cout << "|-- Column Value: " + to_string(image[i][j]) + "  X: " + to_string(j) + "  Y: "+ to_string(i-lengthOfColumn+1) + "  Length: " + to_string(lengthOfColumn) + " --|" << endl;
            }
            bottom[j] -= lengthOfColumn;
        }
    }
}

int Program::moveAcrossRow(int** image, int x, int y) {
    int holder = 1;
    //cout << "Start: " << holder << "  X: " << x << "  Y: " << y << endl;
    if (y > 0) {
        if (image[x][y] == image[x][y-1]) {
            //cout << "Holder: " << holder << "  X: " << x << "  Y: " << y << endl;
            holder += moveAcrossRow(image, x, y-1);
        }
    }
    //cout << "Holder: " << holder << "  X: " << x << "  Y: " << y << endl;
    return holder;
}

void Program::FindRows(int** image) {
    /*for(int i = 0; i < 3; i++) {
        cout << "[";
        for(int j = 0; j < 3; j++) {
            cout << " " << image[i][j];
        }
        cout << "]" << endl;
    }*/
    int height = 3;
    //while (image[height++]) {}
    int width = 3;
    //while (image[0][width++]) {}
    vector<string> holder;
    //cout << "hw " << height << " " << width << endl;
    int right[3];
    for(int i = 0; i < 3; i++) {
        right[i] = width;
    }
    //cout << right[1] << endl;
    int lengthOfRow = 0;
    int counter = 0;
    for(int i = 0; i < height; i++) {
        //cout << "testing 2" << endl;
        lengthOfRow = 1;
        //cout << "testingi " << i << endl;
        for(int j = width-1; j >=0 && j < right[i]; j--) {
            //cout << "i: " << i << "  j: " << j << endl;
            lengthOfRow = moveAcrossRow(image, i, j);
            //cout << "testingj " << j << " " << lengthOfRow << endl;
            if (lengthOfRow > 1) {
                //cout << "Pushing Back" << endl;
                counter++;
                cout << "|-- Row Value: " + to_string(image[i][j]) + "  X: " + to_string(j-lengthOfRow+1) + "  Y: "+ to_string(i) + "  Length: " + to_string(lengthOfRow) + " --|" << endl;
            }
            right[i] -= lengthOfRow;
        }
    }
}
