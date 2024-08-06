#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include"File.h"
using namespace std;
 
class User{
    string user;
    string password;
public:
    User(){
        while (true) {
            cout << "Username: ";
            cin >> user;
            cout << "  Password: ";
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
                cout << endl;
                if (temp == 'Y') {
                    accounts.AddToFile("|-- " + user + " " + password + " --|", -1);
                    cout << "Account Created" << endl;
                    break;
                }
            }
        }
    }
    string get_user(){
        return user;
    }
 
    string get_password(){
        return password;
    }
};
 
class Program{
    User bob;
public:
    Program(){}
 
    ~Program(){}
 
    void welcome(){
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
 
    void createImage(){
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
        cout << "This is your image!" << endl;
        print(img, 4, 4);
        //INFO ABOUT IMAGE
        cout << "Would you like to save your image? (y for Yes and n for No)";
        cin >> c;
        if (c=='y'){
            saveImage(img, 4, 4);
        } else if (c=='n'){
            return;
        }
    }
    void browse(){
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
        //INFO ABOUT IMAGE
        cout << "Would you like to save your image? (y for Yes and n for No)";
        cin >> c;
        if (c=='y'){
            saveImage(img, 4, 4);
        } else if (c=='n'){
            return;
        }
    }
    void menu(){
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
 
    void saveImage(int** img, int h, int w){
        ofstream os(bob.get_user()+".txt", ios_base::app);
        os << h << ' ' << w << ' ';
        for (int i = 0; i < h; i++){
            for (int j = 0; j < w; j ++){
                os << img[i][j];
            }
        }
        os << endl;
    }
 
    void profile(){
        char c;
        cout << "Here is some information about your profile: " << endl;
        cout << "Your username is: " << bob.get_user() << endl;
        cout << "Would you like to access your saved images? (y for Yes, n for No)";
        cin >> c;
        if (c=='y'){
          ifstream is(bob.get_user()+".txt");  
          printSavedImages(is);
          return;  
        } else if (c=='n'){
            return;
        }
    }
 
    void settings(){
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
 
    int** createArray(int h, int w){
        int** image;
        image = new int*[h];
        for(int i = 0; i < h; i++){
            image[i] = new int[w];
        }
        return image;
    }
       
    int** createArray1(int h, int w){
        int** image=createArray(h, w);
        for(int i=0; i < h; i++){
            for(int j=0; j < w; j++){
                image[i][j]=i;
            }
        }
        return image;
    }
       
    int** createArray2(int h, int w){
        int** image=createArray(h, w);
        for(int i=0; i < h; i++){
            for(int j=0; j < w; j++){
                image[i][j]=j;
            }
        }
        return image;
    }
       
    int** createArray3(int h, int w){
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
 
    void printSavedImages(ifstream &is){
        string line;
        int height, width;
        char tmp;
 
        while(getline(is, line)){
            stringstream ss(line);
            ss >> height;
            ss.get();
            ss >> width;
            ss.get();
            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    ss >> tmp;
                    cout << tmp << ' ';
                }
                cout << endl;
            }
            cout << endl;
        }
    }
 
    void print(int** img, int h, int w){
        for(int i=0; i < h; i++){
            for(int j=0; j < w; j++){
                cout << img[i][j] << " ";
            }
            cout << endl;
        }
    }
};
 
int main(){
    Program p1;
    p1.welcome();
}
 
