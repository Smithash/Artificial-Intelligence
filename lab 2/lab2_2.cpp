#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

//IMPLEMENTING THE BOARD FOR MINIMAX

vector<vector<char> > board(string input){
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
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }

    //print board

    return board;
}



int main(){
    string input;

    cin >> input;

    board(input);
    return 0;
}