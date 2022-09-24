// Word Search Program
// Anusha Bajracharya
// 2/11/22
// CS 1337.010
// Note:
//  This program tries to find specific words according to a text file
//  within a matrix of letters from the same text files and reports
//  where the word has been found or if the word was not found
// Changelog:
// 2/11- created the readWordSearch function; initially if statement
//       to ignore the comment lines, empty lines, and lines starting
//       with digits
// 2/12- changed to using peek function instead of if statement and
//       altered the logic of how to retrieve the word search
// 2/13- tried to add function to store each word as a char array but changed
//       to using string :: npos and line.find
// 2-15- added toupper in findWords function to make sure all letters being
//       searched are capitalized
// 2-16- included wordDirection function and created vector to add all words
//       that were not found


#include <iostream>
#include <fstream>  // ifstream
#include <string>   // getline
#include <vector>   // vector and push_back

using namespace std;

// For searching in all 8 directions
int x[] = { -1, -1, -1, 0, 0, 1, 1, 1 }; // Controls up and down 
int y[] = { -1, 0, 1, -1, 1, -1, 0, 1 }; // Controls left and right

// Rows and columns of the word search grid
const int R = 18;
const int C = 18;

// Stores the matrix of letters from the text file
char wordSearchGrid[R][C];

// Stores the words that weren't found
vector<string>(unfoundWords);

// The findWords function searches the words starting at (row, coln) in 
// the word search grid based on all 8 directions
int findWords(char grid[R][C], int row, int col, string word) {

    // If first character of word doesn't match with
    // given starting point in grid.
    if (grid[row][col] != toupper(word[0]))
        return -1;

    int len = word.length();

    // Search word in all 8 directions starting from (row,col)
    for (int dir = 0; dir < 8; dir++) {
        // Initialize starting point for current direction
        int k, rd = row + x[dir], cd = col + y[dir];


        // First character is already checked, match remaining
        // characters
        for (k = 1; k < len; k++) {

            // If out of bound break
            if (rd >= R || rd < 0 || cd >= C || cd < 0)
                break;

            // Removes the empty spaces in the movie titles
            if (word[k] == ' ')
                continue;

            // If not matched, break
            if (grid[rd][cd] != toupper(word[k]))
                break;

            // Moving in particular direction
            rd += x[dir], cd += y[dir];
        }
        /*if (k == len) {
            if (x[dir] == -1 && y[dir] == -1) {
                direction = "NW"; //SW
            }
            else if (x[dir] == -1 && y[dir] == 0) {
                direction = "N"; //W
            }
            else if (x[dir] == -1 && y[dir] == 1) {
                direction = "NE"; //NW
            }
            else if (x[dir] == 0 && y[dir] == -1) {
                direction = "W"; //S
            }
            else if (x[dir] == 0 && y[dir] == 1) {
                direction = "E"; // N
            }
            else if (x[dir] == 1 && y[dir] == -1) {
                direction = "SW"; //SE
            }
            else if (x[dir] == 1 && y[dir] == 0) {
                direction = "S"; //E
            }
            else if (x[dir] == 1 && y[dir] == 1) {
                direction = "SE"; //NE
            }

            return true;

        }

    }
    return false;*/
        // If all character matched, then value of must
        // be equal to length of word
        if (k == len)
            return dir;
    }
   return -1;
} // findWords

// wordDirection function gives cardinal direction based on the x-y directions
string wordDirection(short int x, short int y) {
    string direction = "";
    if (x == -1 && y == -1) {
        direction = "NW";
    }
    else if (x == -1 && y == 0) {
        direction = "N";
    }
    else if (x == -1 && y == 1) {
        direction = "NE";
    }
    else if (x == 0 && y == -1) {
        direction = "W";
    }
    else if (x == 0 && y == 1) {
        direction = "E";
    }
    else if (x == 1 && y == -1) {
        direction = "SW";
    }
    else if (x == 1 && y == 0) {
        direction = "S";
    }
    else if (x == 1 && y == 1) {
        direction = "SE";
    }
    return direction;

} // wordDirection

// patternSearch function searches for the movie title on the word search grid
void patternSearch(char grid[R][C], string word)
{
    // Consider every point as starting point and search
    // given word
    bool found = false;
    int dir = -1;
    for (int row = 0; row < R; row++) {
        for (int col = 0; col < C; col++) {

            // Stores which of 8 directions
            dir = findWords(grid, row, col, word);
            if (dir != -1) {
                found = true;
                cout << word << " found at " << (row + 1) << ", "
                    << (col + 1) << " (direction: " << wordDirection(x[dir], y[dir]) << ")" << endl;
            }
        }
    }
    // All unfound movies added to vector
    if (!found) {
        unfoundWords.push_back(word);
    }

} // patternSearch



// readWordSearch function reads in the word search from the file into a char array
void readWordSearch(ifstream& infile) {

    string line; // Stores each line from the file
    int row = 0; // Counter of the while loop and for the row of the word search
    while (true) { // Retrieves every line from the file
        char ch;
        ch = infile.peek();
        while (ch == '#' || ch == '\n' || isdigit(ch)) { // Sees if the line is a comment, a new line, or begins with a digit
            getline(infile, line); // Ignore that line
            ch = infile.peek(); // Peek at first character of next line
        }
        getline(infile, line);

        // assigning each character of the line into the word matrix
        if (row <= 18) {
            for (int coln = 0; coln < C; coln++) {
                wordSearchGrid[row][coln] = line[coln];
            }
        }
        // increments the row up to 18
        row++;

        // break when the matrix reached 18 rows
        if (row == 18) {
            break;
        }

    }
    cout << endl;
    cout << "Nbr Rows: 18; Nbr Cols: 18 " << endl;

    // Using a nested for loop to print out all the contents of the matrix
    for (int row = 0; row < R; row++) {
        for (int coln = 0; coln < C; coln++) {
            cout << wordSearchGrid[row][coln];
        }
        cout << endl; // Starting a new line after every row
    }
    cout << endl;
} //readWordSearch


// Driver function
int main() {

    string wordSearchFile;
    ifstream infile;

    // Prompts user to input the file name
    cout << "Enter the name of a file to use: ";
    cin >> wordSearchFile;

    // Opens file
    infile.open(wordSearchFile);

    // While input file is invalid, prompt user to input file name
    // until it is valid or user enters "exit" to quit 
    while (!infile) {
        cout << "Oops, can't open the specified input file: No such file or directory" << endl;
        cout << "The file name used was: " << wordSearchFile << endl;
        cout << "Enter another file name to use (or press \"exit\" to quit)";
        cin >> wordSearchFile;
        if (wordSearchFile == "exit") {
            return 0;
        }
        else {
            infile.open(wordSearchFile);
        }
    }

    // Calls the readWordSearch Function
    readWordSearch(infile);

    string line; // each line of the text file
    bool found = false;

    while (getline(infile, line))
    {

        // searches for the line that matches "#Movie Titles to Search For"
        size_t pos = line.find("#Movie Titles to Search For");

        // The following if statement search for string "#Movie Titles to Search For"
        // for each line and if it has already been found no need to search anymore
        if (pos == string::npos && !found)
        {
            continue;
        }
        else {
            found = true; // Set to true because the the string has already been found
        }

        // The following block of code will call the function patternSearch
        if (found == true) {

            char ch;
            ch = infile.peek(); // Using peek to find if it is a comment or new line
            while (ch == '#' || ch == '\n') { // Check for both comment lines and blank lines
                getline(infile, line); // Ignore this line - just toss it
                ch = infile.peek(); // Peek at first character of the current line
            }

            if (line[0] == '#' || line[0] == '\n') {

                continue;
            }
            patternSearch(wordSearchGrid, line);
        }

    }

    cout << endl;
    cout << "Couldn't find these movies: " << endl;

    for (int i = 0; i < unfoundWords.size(); i++) {
        cout << unfoundWords.at(i) << endl;
    }
    infile.close();

    return 0;
} // main



