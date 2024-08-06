#ifndef __INTERFACE_H_
#define __INTERFACE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
#include"Interface.h"

class User{
    string user;
    string password;
public:
    User();
    string get_user();
    string get_password();
};

class Program{
    User bob;
public:
    Program(){}
    void welcome();
    void createImage();
    void browse();
    void menu();
    void saveImage(int** img, int h, int w);
    void profile();
    void settings();
    int** createArray(int h, int w);
    int** createArray1(int h, int w);
    int** createArray2(int h, int w);
    int** createArray3(int h, int w);
    void printSavedImages();
    void print(int** img, int h, int w);
    int moveUpColumn(int** image, int x, int y);
    void FindColumns(int** image);
    int moveAcrossRow(int** image, int x, int y);
    void FindRows(int** image);
};

#endif