// Function that recreates an array based on the analysis in .txt files
int** File::recreate(int width, int height) {

        // creating a new array that is populated with value -1
        int** new_img;
        new_img = new int*[height];
        for(int i = 0; i < height; i++) {
            new_img[i] = new int[width];
            for(int j = 0; j < width; j++) {
                new_img[i][j] = -1;
            }
        }
        
        // Opening the column testing file
        string line_column;
        ifstream colFile("ColumnTesting.txt");

        // Iterating through lines of the opened file and extracting stating x, y values, length and the value.
        while (getline(colFile, line_column)) {
            string tmp;
            int start_x, start_y, value, len;
            istringstream is1(line_column);
            is1 >> tmp >> tmp >> tmp >> value >> tmp >> start_x >> tmp >> start_y >> tmp >> len;
            
            // Changing the values of the new array to the ones corresponding to the column analysis
            for(int j = start_x; j < start_x + len; j++) {
                new_img[j][start_y] = value;
            }
        }
        
        // Opening the row testing file
        string line_row;
        ifstream rowFile("RowTesting.txt");
        
        // Iterating through lines of the opened file and extracting stating x, y values, length and the value.
        while (getline(rowFile, line_row)) {
            string tmp2;
            int start_x, start_y, value, len;
            istringstream is2(line_row);
            is2 >> tmp2 >> tmp2 >> tmp2 >> value >> tmp2 >> start_x >> tmp2 >> start_y >> tmp2 >> len;
            
            // Changing the values of the new array to the ones corresponding to the column analysis
            for(int j = start_y; j < start_y + len; j++) {
                new_img[start_x][j] = value;
            }

        }


        // Iteating through the new array and change the values that were not changed by row and column analysis to random numbers from range 0 to 5
        for(int i = 0; i < height; i++) {
            for(int j = 0; j < width; j++) {
                if(new_img[i][j] == -1) {
                    new_img[i][j] = rand() % 6;
                }
            }
        }
        return new_img;
}