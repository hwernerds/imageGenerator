#ifndef __USER_H__
#define __USER_H__

#include<fstream>
#include<iostream>
#include"File.h"
using namespace std;

class User {
    private:
        string username;
        string password;
        string date;
        string backgroundType;
        string imagesDrawn;
        string imagesGenerated;
    public:
        User(string FileName);
        string get_Username() const;
        string get_Password() const;
        string get_Date() const;
        string get_BackgroundType() const;
        string get_ImagesDrawn() const;
        string get_ImagesGenerated() const;
        string get_Images() const;
        void Change_Password(string newPassword);
        void Set_BackgroundType(char type);
        void increment_ImagesGenerated();
        void increment_ImagesDrawn();
};

#endif