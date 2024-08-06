#include <iostream>
#include <fstream>
#include <limits>
#include <typeinfo>
#include <vector>
#include <sstream>
#include <string>
#include"File.h"
using namespace std;

File::File(string fn) {
    FileName = fn;
    currentLine = 0;
    f.open(fn + ".txt");
    if (f.good()) {
        //cout << "good" << endl;
    } else {
        cout << "No File Found for " << fn << ". Make one? (y or n)" << endl;
        char testing;
        cin >> testing;
        if (testing == 'y') {
            //cout << "Making one" << endl;
            ofstream temp(fn+".txt");
            f.open(fn+".txt");
            temp.close();
        } else {
            //cout << "Not Making one" << endl;
        }
    }
}

void File::AddToFile(string s, int l) {
    //cout << "Hello!" << endl;
    if (l != -2) {
        GoToLine(l);
        //cout << "Going to line" << endl;
    } else {
        GoToLine(0);
    }
    //cout << "Adding: " << s << "   To File: " << FileName << "   At line: " << currentLine <<  endl;
    f << s << endl;
    //f << "|-- hi hi --|" << endl;
    currentLine++;
}

string File::ReadFromFile(int l) {
    if (l != -2) {;
        GoToLine(l);
    }
    if (f.eof()) {
        return "End";
    }
    string temp;
    //string holder;
    getline(f, temp);
    /*while((holder.compare("--|") != 0) && !f.eof()) {
        f >> holder;
        temp += " ";
        temp += holder;
    }*/
    currentLine++;
    return temp;
}

string File::SearchForAccount(string user, string password) {
    string temp;
    f.close();
    f.open(FileName + ".txt");
    temp = "sadsad";
    while ((user != temp)&&!(f.eof())) {
        f >> temp;
        if (temp != "|--") {
            //cout << "function failed" << endl;
            return "Account Not Found";
        }
        f >> temp;
        if (temp == user) {
            f >> temp;
            if (temp == password) {
                break;
            } else {
                return "Wrong Password";
            }
        }
        getline(f, temp);
        currentLine++;
    }
    if (f.eof()) {
        return "Account Not Found";
    } else {
        return "Logged in";
    }
}

int File::GetCurrentLine() {
    return currentLine;
}

void File::GoToLine(int l) {
    string temp = "funny";
    //cout << "Current Line: " << currentLine << "  L: " << l << endl;
    if (l == -1) {
        //cout << "Going to the end" << endl;
        int counter;
        while (!f.eof()) {
            getline(f, temp);
            currentLine++;
        }
        counter = currentLine;
        f.close();
        f.open(FileName+".txt");
        //cout << "Going to end" << endl;
        currentLine = 0;
        for(int i = 0; i < counter-1; i++) {
            getline(f, temp);
            currentLine++;
            //cout << currentLine << endl;;
        }
        //f << "hi" << endl;
    } else {
        if (l < currentLine) {
            f.close();
            f.open(FileName + ".txt");
            currentLine = 0;
        }
        for(currentLine; currentLine < l; currentLine++) {
            //cout << "Moving to: " << currentLine << endl;
            getline(f, temp);
            if (f.eof()) {
                break;
            }
        }
    }
}

int File::moveUpColumn(int** image, int x, int y) {
    int holder = 1;
    if (x > 0) {
        if (image[x][y] == image[x-1][y]) {
            holder += moveUpColumn(image, x-1, y);
            //cout << "Holder: " << holder << "  X: " << x << "  Y: " << y << endl;
            return holder;
        }
    }
    //cout << "Holder: " << holder << "  X: " << x << "  Y: " << y << endl;
    return holder;
}

int File::moveAcrossRow(int** image, int x, int y) {
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


void File::FindColumns(int** image, int width, int height) {
    //int height = sizeof(image)/sizeof(image[0]);
    //int width = sizeof(image[0])/sizeof(image[0][0]);
    //cout << "Finding Columns : )" << endl;
    vector<string> holder;
    //cout << "height: " << height << "   width: " << width << endl;
    int bottom[width];
    for(int i = 0; i < width; i++) {
        bottom[i] = height-1;
    }
    //cout << bottom[1] << endl;
    int lengthOfColumn = 0;
    int counter = 0;
    for(int i = height-1; i > 0; i--) {
       // cout << "testing 2" << endl;
        lengthOfColumn = 1;
        //cout << "testingi " << i << "   Bottom " << bottom[0] << endl;
        for(int j = 0; j < width && i == bottom[j]; j++) {
            lengthOfColumn = moveUpColumn(image, i, j);
            //cout << "testingj " << j << " " << lengthOfColumn << endl;
            if (lengthOfColumn > 1) {
                //cout << "Pushing Back" << endl;
                counter++;
                holder.push_back("|-- Column Value: " + to_string(image[i][j]) + "  X: " + to_string(j) + "  Y: "+ to_string(i-lengthOfColumn+1) + "  Length: " + to_string(lengthOfColumn) + " --|");
            }
            bottom[j] -= lengthOfColumn;
            if (j == 3) {
                //cout << "I: " << i << "   J: " << j << " Success?" << endl;
            }
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

/*void determineLocation(vector<int>) {

}

void File::FindBoxes(int** image, int x, int y) {
    int bottom[width];
    int rowCheck[width];
    for(int i = 0; i < width; i++) {
        bottom[i] = height-1;
        rowCheck[i] = -1;
    }
    vector<int> holder;
    int temp;
    for(int i = height-1; i >=0; i--) {
        for(int j = 0; j < width; j++) {
            temp = moveUpColumn(image, i, j);
            if (temp > 1) {
                rowCheck[i] = temp;
            }
        }
        for(int i = 0; i < width; i++) {
            rowCheck[i] = -1;
        }
    }
}*/

void File::FindRows(int** image, int width, int height) {
    cout << "Height: " << height << "   Width: " << width << endl;
    for(int i = 0; i < height; i++) {
        cout << "[";
            for(int j = 0; j < width; j++) {
                cout << " " << image[i][j];
            }
        cout << "]" << endl;
    }
    vector<string> holder;
    int right[width];
    for(int i = 0; i < width; i++) {
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

string File::findSavedImages(){
    int counter = 0;
    string line = ReadFromFile(counter);
    int height, width;
    string tmp;
    //cout << "Line: " << line << endl;
    string tempstr = "";
    char temp;
    cout << "testing2" << endl;
    f.close();
    f.open(FileName+".txt");
    bool skip = false;
    while(!f.eof()){
        if (line[0] != '|' || !skip) {
            line = ReadFromFile();
            skip = true;
            //cout << "Continuing" << endl;
            continue;
        }
        stringstream ss(line);
        ss >> temp;
        ss >> temp;
        width = (int)(temp-'0');
        cout << "Width: " << width << endl;;
        ss >> temp;
        height = (int)(temp-'0');
        cout << "Height: " << height << endl;;
        for(int i = 0; i < height; i++) {
            tempstr += "\t\t[";
            for(int j = 0; j < width; j++) {
                ss >> temp;
                tempstr = tempstr + " " + temp;
            }
            tempstr += "]\n";
        }
        tempstr += "\n\n";
        line = ReadFromFile();
    }
    return tempstr;
}