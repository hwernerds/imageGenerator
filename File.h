#ifndef __FILE_H__
#define __FILE_H__

#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
using namespace std;

struct Pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

class File {
        fstream f;
        string FileName;
        int currentLine;
    public:
        File(string fn);
        void AddToFile(string s, int l = -2);
        string ReadFromFile(int l = -2);
        string SearchForAccount(string user, string password);
        void GoToLine(int l);
        int GetCurrentLine();
        int moveUpColumn(int** image, int x, int y);
        void FindColumns(int** image, int width, int height);
        int moveAcrossRow(int** image, int x, int y);
        void FindRows(int** image, int width, int height);
        void saveImage(int** img, int h, int w);
        string findSavedImages();
};

void FileImage(int width, int height, int type, string id, string Title, string Creator, Pixel** MyImage, string prompt);
string GetImageInfo(int id);
string GetImagePath(int id);
string ConvertImage(string id, string name);
#endif