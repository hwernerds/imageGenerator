#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
#include <ctime>
#include "File.h"
//#include "Image.h"
#include "/usr/local/cs/cs251/show_mem.h"
using namespace std;

/*string Generated::get_Info() {

}*/

void FileImage(int width, int height, int type, string id, string Title, string Creator, Pixel** MyImage, string prompt) {
    string temp;
    cout << "working" << endl;
    temp = "mkdir Images/" + id;
    system(temp.c_str());
    ofstream of;
    temp = "Images/" + id + "ImageInfo.txt";
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
    if (type == 1) {
        temp = temp + " " + prompt;
    }
    cout << "Temp is:" << temp << endl;
    of << temp;
    temp = "Image/" + id + "/ImageData.ppm";
    _write_image(temp.c_str(), reinterpret_cast<char **>(MyImage), width, height);

    File myFile("Accounts/"+Creator);
    myFile.AddToFile(id, -1);
}