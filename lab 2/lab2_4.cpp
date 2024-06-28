#include <iostream>
#include <vector>
#include <sstream>
#include <string>


using namespace std;

 
enum  GameState {Won_o, Won_x, Draw, Ongoing};
vector<vector<char> > createboard(string input){
    vector<vector<char> > board;

    for (int i = 0; i < 3; ++i) {
        vector<char> temp;
        temp.push_back(' ');
        temp.push_back(' ');
        temp.push_back(' ');
        board.push_back(temp);
    }

    
    for(int i=0; i< 9; i++){
        if(input[i] == '.'){
            input[i] = '_';
        }
    }

    for(int i=0; i< 3; i++){
        for(int j=0; j<3; j++){
            int index = i * 3 + j;
            board[i][j] = input[index];
        }
    }
    return board;
}

bool checkDiagonal(vector<vector<char> > board){
    bool win = false;
    if(board[0][0] == 'x' && board[1][1] =='x' && board[2][2] == 'x'){
        win = true;
    }

    if(board[0][0] == 'o' && board[1][1] =='o' && board[2][2] == 'o'){
        win = true;
    }
    return win;
}

bool checkWin(vector<vector<char> > board, char player){
    //vertical and horizontal
    for(int i=0; i< 3; i++){
        if(board[i][0] == player && board[i][1] == player && board[i][2]== player){
            return true;
        }
        if(board[0][i] == player && board[0][i]== player && board[2][i] == player){
            return true;
        }
    }

    //diagonal 
    if(board[0][0] == player && board[1][1] == player && board[2][2] == player){
        return true;
    }
    if(board[0][2] == player && board[1][1] == player && board[2][0] == player){
        return true;
    }

    return false;

}

//check if the board is full

bool isBoardFull(vector<vector<char> > board){
    for(const auto& row: board){
        for(char cell: row){
            if(cell =='_'){
                return false;
            }
        }
    }
    return true;
}

// Function to determine the status of the game
GameState determineGameState(vector<vector<char> >& board) {
    if (checkWin(board, 'o'))
        return Won_o;
    if (checkWin(board, 'x'))
        return Won_x;
    if (isBoardFull(board))
        return Draw;
    return Ongoing;
}

void printState(vector<vector<char> > board){
    GameState state = determineGameState(board);

    switch(state){
        case Won_o:
            printf("O wins\n");
            break;
        case Won_x:
            printf("X wins\n");
            break;
        case Draw:
            printf("Draw\n");
            break;
        case Ongoing:
            printf("In progress\n");
            break;
    }
}

int main(){
    string input;
    cin>> input;
    vector<vector<char> > board;

    board =createboard(input);
    printState(board);
    
    return 0;
}