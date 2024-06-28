#include <iostream>
#include <string>
#include <vector>
#include <queue> 
#include <fstream> 
#include <set>
#include <tuple>
#include <iomanip>
using namespace std;

enum Actions{ Up =1, Down = 2, Left =3, Right =4};
const int SIZE = 4;
const string goalState = "ABCDEFGHIJKLMNO#";


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

int BFS(string input) {
    int nodes =0;
    queue<pair<string,int> > q; //create Q
    if(input == goalState){
        return 0;
    }

    q.push(make_pair(input, 0)); //FIFO queue with node as only element
    set<string> explored; //an empty set

    while(!q.empty()){
        string current = q.front().first;
        int depth = q.front().second;
        q.pop();
        
        

        explored.insert(current); //adding the node to explored
        
        //get the actions 
        vector<int> actions = availableActions(current);

        for(auto& action: actions){
            string next = updatedBoard(current, action);
            
            pair<string, int> newNode = make_pair(next, depth+1);

            if(next == goalState){
                
                return depth + 1, nodes;
            }

            if(explored.find(next) == explored.end()){
                q.push(newNode);
                nodes++;
            }
        }
    }
    return 0;
}

int h1(string input){ //this is incorrect
    //Need to calculate h 
    int h =0;

    for(int i=0; i < input.size(); i++){
        if(input[i] != goalState[i] && input[i]!='#'){
            h++;
        }
    }
    //then add the depth to h
    return h;
}

int h2(const string& state) {
    int h = 0;
    for (int i = 0; i < state.size(); ++i) {
        if (state[i] != '#') {
            int currentRow = i / 4;
            int currentCol = i % 4;
            int goalIndex = goalState.find(state[i]);
            int goalRow = goalIndex / 4;
            int goalCol = goalIndex % 4;
            h += abs(currentRow - goalRow) + abs(currentCol - goalCol);
        }
    }
    return h;
}


int AStar1(string input){
    int expandedNodes =0;
    priority_queue<pair<int, pair<string, int> >, vector<pair<int, pair<string, int> > >, greater<pair<int, pair<string, int> > > > q;


    if(input == goalState){
        return 0;
    }
    q.push(make_pair(h1(input), make_pair(input, 0)));
    set<string> explored;
    while(!q.empty()){
        string current = q.top().second.first;
        int costSoFar = q.top().second.second; //essentially the depth

        q.pop();
        explored.insert(current);
        //Get the action 
        vector<int> actions = availableActions(current);

        for(auto& action: actions){
            string next = updatedBoard(current, action);
            
            int newCost = costSoFar + 1;
            //pair<string, int> newNode = make_pair(next, cost);
            if(next == goalState){

                return newCost, expandedNodes;
            }
            if(explored.find(next) == explored.end()){
                int priority = newCost + h1(next);
                q.push(make_pair(priority, make_pair(next, newCost)));
                expandedNodes++;
            }
        }
    }
    return 0;
}

int AStar2(string input){
    int nodes =0;
    priority_queue<pair<int, pair<string, int> >, vector<pair<int, pair<string, int> > >, greater<pair<int, pair<string, int> > > > q;


    if(input == goalState){
        return 0;
    }
    q.push(make_pair(h2(input), make_pair(input, 0)));
    set<string> explored;
    while(!q.empty()){
        string current = q.top().second.first;
        int costSoFar = q.top().second.second; //essentially the depth

        q.pop();
        explored.insert(current);
        //Get the action 
        vector<int> actions = availableActions(current);

        for(auto& action: actions){
            string next = updatedBoard(current, action);
            
            int newCost = costSoFar + 1;
            //pair<string, int> newNode = make_pair(next, cost);
            if(next == goalState){
                
                return newCost, nodes;
            }
            if(explored.find(next) == explored.end()){
                int priority = newCost + h2(next);
                q.push(make_pair(priority, make_pair(next, newCost)));
                nodes++;
            }
        }
    }
    return 0;
}



int main(){
    string puzzle;
    fstream input;
    input.open("../puzzles.txt");
    //ofstream results("result.txt");

    if (!input.is_open()) {
        cerr << "Error: " << strerror(errno)<<endl;
        cerr << "Failed to open files." << endl;
        return 1;
    }

    while(getline(input, puzzle)){
        cout<<puzzle<<"\n";
        //results<<"Puzzle \t\t"<<"Solution \t"<<"BFS \t"<< "A*-h1 \t"<<"A*h2"<<"\n\n";
    }
    return 0;
}
    