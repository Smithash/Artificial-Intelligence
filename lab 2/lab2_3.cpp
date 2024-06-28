#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

//IMPLEMENTING MOVES 

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
            //cout<<board[i][j]<<" ";
        }
        //cout<<endl;
    }
    return board;
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

void printBoard(vector<vector<char> >& board){

    for(int i=0; i< 3; i++){
        for(int j=0; j<3; j++){
            cout<<board[i][j]<< " ";
        }
    cout<< endl;
    }
}



int main(){
    string input, action;
    cin >> input;
    int A; //player
    int B; //row index
    int C; //col index

    cin>> A >> B >> C;
    //cout << A << " " << B << " " << C << endl;
    

    vector<vector<char> > board = createboard(input);

    vector<vector<char> > updatedBoard = updateBoard(board, A,B,C);
    printBoard(updatedBoard);

    return 0;
}