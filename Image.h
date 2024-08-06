#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
#include <ctime>
#include "File.h"
#include "/usr/local/cs/cs251/show_mem.h"
using namespace std;

/*class Image {
    protected:
        int width;
        int height;
        string id;
        string Title;
        string Date;
        string Creator;
    public:
        Image(int i)
        virtual int get_Type();
        virtual string get_Info();

}


//type 0
class Drawn : public Image {
    public:
        Drawn(int i) : Image(i);
        int get_Type() {return 0;}
        string get_Info();

};

//type 1
class Generated : public Image {
    public:
        Generated(int i) : Image(i);
        int get_Type() {return 1;}
        string get_Info();
};*/

void FileImage(int width, int height, int type, string id, string Title, string Creator, Pixel** MyImage, string prompt = "");

#endif