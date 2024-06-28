#include <iostream>
#include <string>
#include <vector>
#include <queue> 
#include <fstream> 
#include <set>
using namespace std;

//estimation of the cost-to-go is the number of tiles in the current 
//configuration that are in the wrong location according to the goal

//Input -> initial state 
//Output -> cost of the optimal path
enum Actions{ Up =1, Down = 2, Left =3, Right =4};
const int SIZE = 4;
const string goalState = "ABCDEFGHIJKLMNO#";

void print_tiles(const std::string& table) {
    for (size_t i = 0; i < table.length(); ++i) {
        printf("%c ", table[i]);
        if ((i + 1) % 4 == 0) {
            printf("\n");
        }
    }
    printf("\n");

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

int AStar(string input){ //doesn't work at all. dont think im using priority queue correctly
    //implement USC 
    //h = number of tiles in the current configuration that are in the wrong location according to the goal
    //use a priority queue

    //ofstream File("output.txt");
    //frontier thats ordered by heuristic
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

        // File << "Current state: " << current << ", Actions: ";
        // for (auto action : actions) {
        //     File << action << " ";
        // }
        // File << endl;

       
        for(auto& action: actions){
            string next = updatedBoard(current, action);
            
            int newCost = costSoFar + 1;
            //pair<string, int> newNode = make_pair(next, cost);
            if(next == goalState){
                return newCost;
            }
            if(explored.find(next) == explored.end()){
                int priority = newCost + h2(next);
                q.push(make_pair(priority, make_pair(next, newCost)));
            }
            
        }


    }
    return 0;
}

int main(){
    string input;
    ifstream puzzles;
    puzzles.open("./puzzles.txt");
    
    while(getline(puzzles, input)){
        cout<<input<<endl;
    }
    
    // int cost = AStar(input);
    // cout << cost <<"\n";
    return 0;
}