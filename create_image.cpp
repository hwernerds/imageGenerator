#include <iostream>
#include <fstream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include"/usr/local/cs/cs251/show_mem.h"
using namespace std;

struct Pixel {
    unsigned char red; 
    unsigned char green; 
    unsigned char blue;
};



class Image {
    int width, height;
    Pixel** data;
    public:
        Image(int w, int h, int c, int r, Pixel trg) {
            srand((int) time(0));
            width = w;
            height = h;
            data = new Pixel* [height];

            for(int i = 0; i < height; i++) {
                data[i] = new Pixel[width];
            }

            for(int i = 0; i < height; i++) {
                for(int j = 0; j < width; j++) {
                    data[i][j].red = rand() % 255;
                    data[i][j].green = rand() % 255;
                    data[i][j].blue = rand() % 255;
                }
            }

            for(int i = 0; i < r; i++) {
                int loc = rand()%height;
                for(int j = 0; j < width; j++){
                    data[loc][j].red = trg.red;
                    data[loc][j].green = trg.green;
                    data[loc][j].blue = trg.blue;
                }
            }

            for(int i = 0; i < c; i++){
                int loc = rand()%width;
                for(int j = 0; j < height; j++){
                    data[j][loc].red = trg.red;
                    data[j][loc].green = trg.green;
                    data[j][loc].blue = trg.blue;
                }
            }



        }


        Image(char* filename) {
            std::ifstream f(filename);
            char name[3];
            f  >> name;
            f >> width >> height;
            data = new Pixel* [height];
            for(int i = 0; i < height; i++) {
                data[i] = new Pixel[width];
            }
            int depth;
            f >> depth;
            f.get();
            for(int i = 0; i < height; i++) {
                f.read(reinterpret_cast<char *>(data[i]), width * 3);
            }
        }

        ~Image() {
            for(int i = 0; i < height; i++) {
                delete [] data[i];
            }
            delete [] data;

        }

        int getWidth() {
            return width;
        }

        int getHeight() {
            return height;
        }

        void print() {
            _write_image("output.ppm", reinterpret_cast<char **>(data), width, height);
            system("convert output.ppm ImageTesting.png");
        }   
};

int main() {
    Pixel pix;
    pix.red = 255;
    pix.green = 153;
    pix.blue = 255; 
    Image a(100, 100, 20, 20, pix);
    a.print();
}
