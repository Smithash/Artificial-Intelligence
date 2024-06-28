#include <iostream>
#include <string>
using namespace std;

const int SIZE = 4;
//Implementing Moves 

// Input -> 2 lines 
    // 1 -> string of characters and hash symbol
    // 2 -> action taken: UP, DOWN, LEFT, RIGHT

// Output -> resulting config of 4x4 matrix , each value separated by space
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

pair<int,int> findBlank(char board[SIZE][SIZE]){
    int indexRow;
    int indexCol;

    for(int i=0; i< SIZE; i++){
        for(int j=0; j<SIZE; j++){
            if(board[i][j] == '#'){
                indexRow = i;
                indexCol = j;
            }
        }
    }
    return make_pair(indexRow, indexCol);
}

void updateBoard(char board[SIZE][SIZE], string action){
    //Index of the #
    pair<int,int> blankIndex = findBlank(board);
    int rowIndex = blankIndex.first;
    int colIndex = blankIndex.second;

    //Checking if Right, Left, Down or Up
    if(action == "RIGHT"){
        // j becomes j+1
        board[rowIndex][colIndex] = board[rowIndex][colIndex+1];
        board[rowIndex][colIndex+1] = '#';
    }
    else if(action == "LEFT"){
        // j becomes j-1
        board[rowIndex][colIndex] = board[rowIndex][colIndex-1];
        board[rowIndex][colIndex-1] = '#';
    }
    else if(action == "UP"){
        // i becomes i-1
        board[rowIndex][colIndex] = board[rowIndex-1][colIndex];
        board[rowIndex-1][colIndex] = '#';
    }
    else{
        // i becomes i+1
        board[rowIndex][colIndex] = board[rowIndex+1][colIndex];
        board[rowIndex+1][colIndex] = '#';
    }

}

int main(){
    char board[SIZE][SIZE];
    string line1, line2;

    getline(cin, line1);

    fillBoard(board, line1);
    
    
    getline(cin, line2);
    updateBoard(board, line2);

    printBoard(board);

    return 0;
    
}
