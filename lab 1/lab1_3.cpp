#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int SIZE = 4;
//Implementing available actions 

//INPUT -> string of characters and the hash symbol
//OUTPUT -> list of available actions, on their own line, ORDER: up, down, left, right
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

vector<string> availableActions( char board[SIZE][SIZE]){
    pair<int,int> blankIndex = findBlank(board);
    int size =4;
    int rowIndex = blankIndex.first;
    int colIndex = blankIndex.second;

    vector<string> action;
    action.push_back("UP");
    action.push_back("DOWN");
    action.push_back("LEFT");
    action.push_back("RIGHT");

    if(rowIndex ==0){
        action.erase(action.begin());
    }
    if(rowIndex ==3){
        action.erase(action.begin()+1);
    }
    if(colIndex == 0){
        action.erase(action.begin()+2);
    }
    if(colIndex == 4){
        action.pop_back();
    }
    return action;
}

int main(){
    char board[SIZE][SIZE];
    string line1, line2;

    getline(cin, line1);

    fillBoard(board, line1);
    
    vector<string> actions = availableActions(board);

    // Print the available actions
    
    for (int i=0; i<actions.size(); i++) {
        cout << actions[i] << endl;
    }
    return 0;
    
}
