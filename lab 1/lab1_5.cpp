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

bool isElementInPriorityQueue(priority_queue<pair<string, int>, vector<pair<string, int> >, greater<pair<string, int> > > pq, pair<string, int> currentNode) {
    // Create a temporary priority queue to preserve the original priority queue's contents
    priority_queue<pair<string, int>, vector<pair<string, int> >, greater<pair<string, int> > > temp = pq;

    // Iterate through the temporary priority queue
    while (!temp.empty()) {
        // If the current element is equal to the target element, return true
        if (temp.top() == currentNode) {
            return true;
        }
        temp.pop(); // Remove the current element from the temporary priority queue
    }

    // Element not found in the priority queue
    return false;
}




int h1(string input){ 
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

int AStar(string input){ 
    //implement USC 
    //h = number of tiles in the current configuration that are in the wrong location according to the goal
    //use a priority queue
    
    // ofstream File("output.txt");
    //frontier thats ordered by heuristic
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

        // File << "Current state: " << current << ", Actions: ";
        // for (auto action : actions) {
        //     File << action << " ";
        // }
        // File << endl;

        
        for(auto& action: actions){

            string next = updatedBoard(current, action);
            
            
            int newCost = costSoFar + 1;
            
            
            if(next == goalState){
                return newCost;
            }
            if(explored.find(next) == explored.end()){
                int priority = newCost + h1(next);
                q.push(make_pair(priority, make_pair(next, newCost)));
                
            }
            
        }


    }
    
    return 0;
}

int main(){
    string input;
    cin >> input;
    
    int cost = AStar(input);
    cout << cost <<"\n";
    return 0;
}