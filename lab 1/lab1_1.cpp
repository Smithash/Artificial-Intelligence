#include <iostream>
#include <string>
using namespace std;

const int SIZE = 4;

void printBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

void fillBoard(char board[SIZE][SIZE], string input) { //puts the inout string into a 4x4 matrix to create the board
    int index = 0;
    for (int i = 0; i < SIZE; ++i) { //row
        for (int j = 0; j < SIZE; ++j) { //col
            board[i][j] = input[index++]; //sets pos i and j in the board to a char in the string
        }
    }
}

int main() {
    char board[SIZE][SIZE];
    string input;

    cin >> input;

    fillBoard(board, input);
    printBoard(board);

    return 0;
}