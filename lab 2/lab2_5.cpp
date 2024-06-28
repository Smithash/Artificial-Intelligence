#include <iostream>
#include <vector>
#include <sstream>
#include <string>




using namespace std;

const int MAX = 1e6;
const int MIN = -1e6;
enum  GameState {Won_o, Won_x, Draw, Ongoing};

vector<vector<char> > createboard(string input){
    vector<vector<char> > board(3, vector<char>(3, '_'));

    // for (int i = 0; i < 3; ++i) {
    //     vector<char> temp;
    //     temp.push_back(' ');
    //     temp.push_back(' ');
    //     temp.push_back(' ');
    //     board.push_back(temp);
    // }

    
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

vector<vector<char> > updateBoard(vector<vector<char> > board, int A, int B, int C){
    vector<vector<char> > updatedBoard;
    updatedBoard = board;

    if(A == 0){
        updatedBoard[B][C] = 'x';
    }
    if(A == 1){
        updatedBoard[B][C] = 'o';
    }

    return updatedBoard;

}

int getCurrentPlayer(const vector<vector<char> >& board) {
    int xCount = 0, oCount = 0;
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == 'x')
                xCount++;
            else if (cell == 'o')
                oCount++;
        }
    }
    return (xCount == oCount) ? 0 : 1;
}

int minimax(vector<vector<char> > &board,bool isMax, int alpha, int beta, int player){
    GameState state = determineGameState(board);

    //Checking if game is won/draw, return the score
    if(state == Won_o){
        return -1;
    }
    else if(state == Won_x){
        return 1;
    }
    else if(state == Draw){
        return 0;
    }

    //Recursive case: try all possible moves and recursively call evaluate
    if(isMax){
        int maxScore = MIN;
        for(int i=0; i< 3; i++){
            for(int j=0; j<3; j++){
                if(board[i][j] == '_'){
                    board[i][j] = (player ==0) ? 'x': 'o';
                    int score = minimax(board,false, alpha, beta, (player +1)%2);
                    board[i][j] ='_';
                    maxScore = max(maxScore, score);
                    alpha = max(alpha, score);

                    if(beta <= alpha){
                        break;
                    }
                }
            }
        }
        return maxScore;
    }
    else{
        int minScore = MAX;
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if(board[i][j] == '_ '){
                    board[i][j] = (player ==0) ? 'x': 'o';
                    int score = minimax(board,true, alpha, beta, (player + 1)%2);
                    board[i][j] = '_';
                    minScore = min(minScore, score);
                    beta = min(beta, score);

                    if(beta <=alpha){
                        break;
                    }
                }
            }
        }
        return minScore;
    }
}

int determineWinner(vector<vector<char> >& board) {
    int player = getCurrentPlayer(board);
    int bestScore = MIN;
    int bestMove;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                board[i][j] = (player == 0) ? 'x' : 'o';
                int score = minimax(board, false, MIN, MAX, (player + 1) % 2);
                if (score == 1 || score == -1) {
                    bestMove = (player == 0) ? 'x' : 'o';
                    return score;
                }
                board[i][j] = '_';
            }
        }
    }
    return 0; // No winner found
}


int main(){
    string input;
    cin >> input;

    vector<vector< char> > board;
    board =createboard(input);
    int winner = determineWinner(board);
    
    if(winner == 1){
        printf("X wins\n");
    }
    else if(winner == -1){
        printf("O wins\n");
    }
    else{
        printf("Draw\n");
    }
    return 0;
}