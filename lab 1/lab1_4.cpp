#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue> 
#include <fstream> 
using namespace std;

enum Actions{ Up =1, Down = 2, Left =3, Right =4};
const int SIZE = 4;
const string goalState = "ABCDEFGHIJKLMNO#";

void printBoard(vector<vector<char> > board) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

void fillBoard(vector<vector<char> > board, string input) { //puts the inout string into a 4x4 matrix to create the board
    int index = 0;
    for (int i = 0; i < SIZE; ++i) { //row
        for (int j = 0; j < SIZE; ++j) { //col
            board[i][j] = input[index++]; //sets pos i and j in the board to a char in the string
        }
    }
}

void print_tiles(const std::string& table) {
    for (size_t i = 0; i < table.length(); ++i) {
        printf("%c ", table[i]);
        if ((i + 1) % 4 == 0) {
            printf("\n");
        }
    }
    printf("\n");

}


pair<int,int> findBlank(vector<vector<char> > board){
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

vector<int> availableActions(string board){
    int pos = board.find('#');

    vector<int> action;
    

    if(!(pos == 0 || pos == 1 || pos == 2 || pos ==3)){
        action.push_back(Up);
    }
    
    if(!(pos == 12 || pos== 13 || pos ==14 || pos ==15)){
        action.push_back(Down);
    }
    if(!(pos == 0 || pos== 4 || pos ==8 || pos ==12)){
        action.push_back(Left);
    }
    if(!(pos == 3 || pos== 7 || pos ==11 || pos ==15)){
        action.push_back(Right);
    }
    
    return action;
}
string boardToString(vector<vector<char> > board) {
    string result;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            result += board[i][j];
        }
    }
    return result;
}




bool isElementInQueue(queue<pair<string, int> > q, pair<string, int> currentNode) {
    // Create a temporary queue to preserve the original queue's contents
    queue<pair<string, int> > temp = q;

    // Iterate through the temporary queue
    while (!temp.empty()) {
        // If the current element is equal to the target element, return true
        if (temp.front() == currentNode) {
            return true;
        }
        temp.pop(); // Remove the current element from the temporary queue
    }

    // Element not found in the queue
    return false;
}

    string updatedBoard(string input, int action){
        //find pos of #
        int pos = input.find('#');
        string updatedString = input;
        if(action == Right){
            updatedString[pos] = updatedString[pos+1];
            updatedString[pos + 1] ='#';
        }
        else if(action == Left){
            updatedString[pos] = updatedString[pos-1];
            updatedString[pos-1] ='#';
        }
        else if(action == Up){
            updatedString[pos] = updatedString[pos -4];
            updatedString[pos-4] = '#';
        }
        else{
            updatedString[pos] = updatedString[pos + 4];
            updatedString[pos+4] ='#';
        }
        return updatedString;
        
    }


bool findElement(vector<string> explored, string node){
    for(auto i: explored){
        if(node == i){
            return true;
        }
    }
    return false;
}  

int BFS(string input, int expandedNodes) {
    
    queue<pair<string,int> > q; //create Q
    if(input == goalState){
        return 0;
    }

    q.push(make_pair(input, 0)); //FIFO queue with node as only element
    set<string> explored; //an empty set
    
    // ofstream file;
    // file.open("output.txt");

    while(!q.empty()){
        string current = q.front().first;
        int depth = q.front().second;
        q.pop();
        cout<<q.size()<< endl;
        

        explored.insert(current); //adding the node to explored
        
        //get the actions 
        vector<int> actions = availableActions(current);

       
        // file << "Current state: " << current << ", Actions: ";
        // for (auto action : actions) {
        //     file << action << " ";
        // }
        // file <<"Depth "<<depth<< endl;

        
        for(auto& action: actions){
            string next = updatedBoard(current, action);
            
            pair<string, int> newNode = make_pair(next, depth+1);

            if(next == goalState){
               
                return depth + 1;
            }

            if(explored.find(next) == explored.end()){
                q.push(newNode);
                expandedNodes++;
            }
        }
        // string var;
        // cin >> var;
    }
    return 0;
}




int main(){
    string input;
    cin >> input;
    int expandedNodes = 0;
    int cost = BFS(input, expandedNodes);
    cout << cost <<"\n";
    return 0;
}