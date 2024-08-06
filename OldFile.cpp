#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
using namespace std;

class File {
    fstream f;
    string FileName;
    int currentLine;
    public:
        File(string fn) {
            FileName = fn;
            currentLine = 0;
            f.open(fn + ".txt");
            if (f.good()) {
                //cout << "good" << endl;
            } else {
                cout << "No File Found for " << fn << ". Make one? (Y or N)" << endl;;
                char testing;
                cin >> testing;
                if (testing == 'Y') {
                    cout << "Making one" << endl;
                    ofstream temp(fn+".txt");
                    f.open(fn+".txt");
                    temp.close();
                } else {
                    cout << "Not Making one" << endl;
                }
            }
        }
        void AddToFile(string s, bool x = false) {
            //cout << "Hello!" << endl;
            if (x) {
                GoToLine(-1);
            }
            f << s << endl;
        }
        string ReadFromFile() {
            string temp = "";
            string holder;
            while((holder.compare("--|") != 0) && !f.eof()) {
                f >> holder;
                temp += " ";
                temp += holder;
            }
            currentLine++;
            return temp;
        }
        void GoToLine(int l) {
            string temp = "funny";
            if (l == -1) {
                while (!f.eof()) {
                    f >> temp;
                }
            } else {
                if (l > currentLine) {
                    f.close();
                    f.open(FileName + ".txt");
                    currentLine = 0;
                }
                for(int i = currentLine; i < l; i++) {
                    while((temp.compare("--|") != 0) && !f.eof()) {
                        f >> temp;
                    }
                    currentLine = i;
                    if (f.eof()) {
                        break;
                    }
                }
            }
        }

        int moveUpColumn(int** image, int x, int y) {
            int holder = 1;
            if (x > 0) {
                if (image[x][y] == image[x-1][y]) {
                    holder += moveUpColumn(image, x-1, y);
                    // cout << "Holder: " << holder << "  X: " << x << "  Y: " << y << endl;
                    return holder;
                }
            }
            //cout << "Holder: " << holder << "  X: " << x << "  Y: " << y << endl;
            return holder;
        }

        void FindColumns(int** image) {
            for(int i = 0; i < 3; i++) {
                /*cout << "[";
                for(int j = 0; j < 3; j++) {
                    cout << " " << image[i][j];
                }
                cout << "]" << endl;*/
            }
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
                        holder.push_back("|-- Column Value: " + to_string(image[i][j]) + "  X: " + to_string(j) + "  Y: "+ to_string(i-lengthOfColumn+1) + "  Length: " + to_string(lengthOfColumn) + " --|");
                    }
                    bottom[j] -= lengthOfColumn;
                }
            }
            //cout << holder[0] << " anothertest" << endl;
            while(counter > 0) {
                //cout << "testing 4" << endl;
                AddToFile(holder[holder.size()-1]);
                holder.pop_back();
                counter--;
            }
        }

        int moveAcrossRow(int** image, int x, int y) {
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

        void FindRows(int** image) {
            for(int i = 0; i < 3; i++) {
                cout << "[";
                for(int j = 0; j < 3; j++) {
                    cout << " " << image[i][j];
                }
                cout << "]" << endl;
            }
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
                        holder.push_back("|-- Row Value: " + to_string(image[i][j]) + "  X: " + to_string(j-lengthOfRow+1) + "  Y: "+ to_string(i) + "  Length: " + to_string(lengthOfRow) + " --|");
                    }
                    right[i] -= lengthOfRow;
                }
            }
            //cout << holder[0] << " anothertest" << endl;
            while(counter > 0) {
                //cout << "testing 4" << endl;
                AddToFile(holder[holder.size()-1]);
                holder.pop_back();
                counter--;
            }
        }
};

int main() {
    int ImageHolder[3][3] = {{0,0,0},{0,0,1},{0,0,1}};
    int** myImage;
    /*int height = 0;
    cout << "finished 0" << endl;
    while (ImageHolder[height++]) {}
    cout << "finished 1" << endl;
    int width = 0;
    while (ImageHolder[0][width++]) {}*/
    myImage = new int*[3];
    for(int i = 0; i < 3; i++) {
        myImage[i] = new int[3];
        for(int j = 0; j < 3; j++) {
            myImage[i][j] = ImageHolder[i][j];
            //cout << "testing 1" << endl;
        }
    }
    File myFile("ColumnTesting");
    //cout << "hi" << endl;
    /*for(int i = 0; i < 3; i++) {
        cout << "[";
        for(int j = 0; j < 3; j++) {
            cout << " " << myImage[i][j];
        }
        cout << "]" << endl;
    }*/
    myFile.FindColumns(myImage);
    File OtherFile("RowTesting");
    //cout << OtherFile.moveAcrossRow(myImage, 1, 1) << endl;
    OtherFile.FindRows(myImage);
    //myFile.ReadFromFile();
    //myFile.ReadFromFile();
}