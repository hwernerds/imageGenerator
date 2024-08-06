#include <iostream>
#include"/usr/local/cs/cs251/show_mem.h"
#include <fstream>
#include <random>
#include<set>
using namespace std;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 255);

struct Pixel {
    unsigned char red, green, blue;
};

class Image{

    int width, height, depth = 255;
    Pixel** data;

    public:

        Image(int w, int h){
            // Dynamically allocate memory for the image
            width = w;
            height = h;
            data = new Pixel*[height]; 
            for(int i = 0; i < height; i++){
                data[i] = new Pixel[width];
            }

            // Generate a random color for the top left pixel
            int red1 = dis(gen);
            int green1 = dis(gen);
            int blue1 = dis(gen);

            // Generate a random color for the bottom right pixel
            int red2 = dis(gen);
            int green2 = dis(gen);
            int blue2 = dis(gen);

            // Calculate the minimum and maximum values for the red, green, and blue channels
            int minRed = min(red1, red2);
            int maxRed = max(red1, red2);
            int minGreen = min(green1, green2);
            int maxGreen = max(green1, green2);
            int minBlue = min(blue1, blue2);
            int maxBlue = max(blue1, blue2);

            // Calculate the range of values for the red, green, and blue channels
            int redRange = maxRed - minRed;
            int greenRange = maxGreen - minGreen;
            int blueRange = maxBlue - minBlue;

            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    // Calculate the value of the red, green, and blue channels for this pixel
                    // using a linear interpolation between the minimum and maximum values
                    int red = minRed + (redRange * j) / width;
                    int green = minGreen + (greenRange * j) / width;
                    int blue = minBlue + (blueRange * j) / width;

                    // Set the red, green, and blue channels of this pixel to the calculated values
                    data[i][j].red = red;
                    data[i][j].green = green;
                    data[i][j].blue = blue;
                }
            }
            
        }

        /*Image(const char filename[]){
            ifstream file(filename);
            char name[3];
            file >> name;
            file >> width >> height;
            data = new Pixel*[height]; 
            for(int i = 0; i < height; i++){
                data[i] = new Pixel[width];
            }
            file >> depth;
            file.get();
            for(int i=0; i<height; i++){
                file.read(reinterpret_cast<char *>(data[i]), width*3);
            }
            file.close();
        }*/

        ~Image(){
            for (int a = 0; a < height; a++){
                delete [] data[a];
            }
            delete [] data;
        }

        int getWidth(){
            return width;
        }

        int getHeight(){
             return height;
        }

        void replaceRows(int numRows, unsigned char red, unsigned char green, unsigned char blue){
            // Generate numRows random numbers between 0 and height - 1
            std::uniform_int_distribution<> dis(0, height - 1);
            std::set<int> rows;
            while(rows.size() < numRows){
                rows.insert(dis(gen));
            }

            // Replace the specified rows with the specified color
            for(int row : rows){
                for(int j = 0; j < width; j++){
                    data[row][j].red = red;
                    data[row][j].green = green;
                    data[row][j].blue = blue;
                }
            }
        }

        void replaceColumns(int numColumns, unsigned char red, unsigned char green, unsigned char blue){
            // Generate numColumns random numbers between 0 and width - 1
            std::uniform_int_distribution<> dis(0, width - 1);
            std::set<int> columns;
            while(columns.size() < numColumns){
                columns.insert(dis(gen));
            }

            // Replace the specified columns with the specified color
            for(int row = 0; row < height; row++){
                for(int col : columns){
                    data[row][col].red = red;
                    data[row][col].green = green;
                    data[row][col].blue = blue;
                }
            }
        }

        void createRandomPath(int numPixels, unsigned char red, unsigned char green, unsigned char blue){
            // Generate the starting x and y coordinates for the path
            int x1 = 0;
            int y1 = 0;

            // Generate a random number to determine which corner the path should start in
            std::uniform_int_distribution<> dis(0, 3);
            int corner = dis(gen);

            if(corner == 1){
                x1 = 0;
                y1 = height - 1;
            }
            else if(corner == 2){
                x1 = width - 1;
                y1 = 0;
            }
            else if(corner == 3){
                x1 = width - 1;
                y1 = height - 1;
            }

            // Generate the ending x and y coordinates for the path
            std::uniform_int_distribution<> xDis(0, width - 1);
            std::uniform_int_distribution<> yDis(0, height - 1);
            int x2 = xDis(gen);
            int y2 = yDis(gen);

            // Calculate the differences in x and y coordinates between the starting and ending points
            int dx = x2 - x1;
            int dy = y2 - y1;

            // Generate numPixels steps for the path, evenly spaced between the starting and ending points
            for(int i = 0; i < numPixels; i++){
                int x = x1 + i * dx / numPixels;
                int y = y1 + i * dy / numPixels;

                // If the path has gone out of bounds, wrap it around to the other side
                if(x < 0){
                    x = width - 1;
                }
                if(x >= width){
                    x = 0;
                }
                if(y < 0){
                    y = height - 1;
                }
                if(y >= height){
                    y = 0;
                }

                // Set the color of the pixel at the current position of the path
                data[y][x].red = red;
                data[y][x].green = green;
                data[y][x].blue = blue;
            }
        }

        void print(){
            ofstream file("output.ppm");
            file << "P6" << endl;
            file << getWidth() << ' ' << getHeight() << endl;
            file << 255 << endl;
            for(int i = 0; i < height; i++){
                file.write(reinterpret_cast<char *>(data[i]), width*3);
            }
        }

};
int main() {
    Image myimg(50, 50);
    //myimg.greyScale();
    //myimg.replaceRows(10,255,255,255);
    //myimg.replaceColumns(10,255,255,255);
    myimg.createRandomPath(5000,255,255,255);
    myimg.createRandomPath(5000,255,255,255);
    myimg.createRandomPath(5000,255,255,255);
    myimg.createRandomPath(5000,255,255,255);
    myimg.createRandomPath(5000,255,255,255);
    myimg.print();
}
