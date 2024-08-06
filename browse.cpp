#include <cstdlib>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include "State.h"
using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;


string create_image(int width, int height, int columns, int rows, int target){
    srand((int) time(0));
    string s;
    int** image;
    //cout << "ctesting1" << endl;
    image = new int*[height];
    for(int i = 0; i < height; i++){
        image[i] = new int[width];
    }
    //cout << "ctesting2" << endl;
    s = to_string(width) + ' ' + to_string(height) + ' ';
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            image[i][j] = rand()%4;;
        }
    }
    //cout << "ctesting3" << endl;
    for(int i = 0; i < rows; i++){
        int loc = rand()%height;
        for(int j = 0; j < width; j++){
            image[loc][j] = target;
        }
    }
    //cout << "ctesting4" << endl;
    for(int i = 0; i < columns; i++){
        int loc = rand()%width;
        for(int j = 0; j < height; j++){
            image[j][loc] = target;
        }
    }
    //cout << "ctesting5" << endl;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            s = s + to_string(image[i][j]) + ' ';
        }
    }
    //cout << s;
    return s;
}

string create_image(){
    srand((int) time(0));
    string s = "";
    int height = rand()%7+2;
    int width = rand()%7+2;
    int rows = rand()%4;
    int columns = rand()%4;
    int** image;
    image = new int*[height];
    for(int i = 0; i < height; i++){
        image[i] = new int[width];
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            image[i][j] = rand()%4;;
        }
    }
    for(int i = 0; i < rows; i++){
        int loc=rand()%height;
        for(int j = 0; j < width; j++){
            image[loc][j] = 0;
        }
    }
    for(int i = 0; i < columns; i++){
        int loc = rand()%width;
        for(int j = 0; j < height; j++){
            image[j][loc] = 0;
        }
    }
    for(int i = 0; i < height; i++){
        s = s + "\t\t[";
        for(int j = 0; j < width; j++){
            s = s +" "+ to_string(image[i][j]);
        }
        s = s+"]\n";
    }
    return s;
}

string browse(){
    string s = "";
    s += "\n";
    int max = 4;
    for(int i = 0; i < max; i++){
        s+=create_image();
        s+="\n";
        sleep_for(1s);
    }
    return s;
}

/*int main() {
    cout << create_image(10,1,2,1,0) << endl;
}*/