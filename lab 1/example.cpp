#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <fstream>
#include <c++/v1/queue>
using namespace std;

enum Actions { Up = 1, Down = 2, Left = 3, Right = 4 };
const int SIZE = 4;



void printBoard(vector<vector<int> > board) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

void fillBoard(vector<vector<int> >& board, vector<int> input) {
    int index = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = input[index++]; // No need to convert from char to int
        }
    }
}

string boardToString(vector<vector<int> > board) {
    string result;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            result += to_string(board[i][j]); // Convert int to string
        }
    }
    return result;
}

pair<int, int> findBlank(vector<vector<int> > board) {
    int indexRow;
    int indexCol;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == -1) { // Change '#' to -1 for representing blank
                indexRow = i;
                indexCol = j;
            }
        }
    }
    return make_pair(indexRow, indexCol);
}

vector<int> availableActions(vector<vector<int> > board) {
    pair<int, int> blankPos = findBlank(board);
    int row = blankPos.first;
    int col = blankPos.second;
    vector<int> actions;

    if (row > 0) actions.push_back(Up);
    if (row < SIZE - 1) actions.push_back(Down);
    if (col > 0) actions.push_back(Left);
    if (col < SIZE - 1) actions.push_back(Right);

    return actions;
}

vector<vector<int> > updatedBoard(vector<vector<int> > board, int action) {
    pair<int, int> blankPos = findBlank(board);
    int row = blankPos.first;
    int col = blankPos.second;

    if (action == Right) {
        swap(board[row][col], board[row][col + 1]);
    } else if (action == Left) {
        swap(board[row][col], board[row][col - 1]);
    } else if (action == Up) {
        swap(board[row][col], board[row - 1][col]);
    } else {
        swap(board[row][col], board[row + 1][col]);
    }
    return board;
}

bool isElementInQueue(queue<pair<vector<vector<int> >, int> > q, pair<vector<vector<int> >, int> currentNode) {
    queue<pair<vector<vector<int> >, int> > temp = q;
    while (!temp.empty()) {
        if (temp.front() == currentNode) {
            return true;
        }
        temp.pop();
    }
    return false;
}
bool findElement(set<vector<vector<int> > > explored, vector<vector<int> > node) {
    return explored.find(node) != explored.end();
}

bool vectorsEqual(const vector<vector<int> >& a, const vector<int>& b) {
    if (a.size() != 1) return false; // Ensure a is a vector of size 1
    return a[0] == b;
}


int BFS(vector<vector<int> > input, int expandedNodes, vector<int> goalState) {
    queue<pair<vector<vector<int> >, int> > q;
    if (vectorsEqual(input, goalState)) {
        return 0;
    }
    q.push(make_pair(input, 0));
    set<vector<vector<int> > > explored;

    while (!q.empty()) {
        vector<vector<int> > current = q.front().first;
        int depth = q.front().second;
        q.pop();

        explored.insert(current);

        vector<int> actions = availableActions(current);
        for (auto& action : actions) {
            vector<vector<int> > next = updatedBoard(current, action);
            
            pair<vector<vector<int> >, int> newNode = make_pair(next, depth + 1);

            if (vectorsEqual(next, goalState)) {
                return depth + 1;
            }
            
            if (!findElement(explored, next)) {
                q.push(newNode);
                expandedNodes++;
            }
        }
    }
    return 0;
}


int main() {

    vector<int> goalState;
    for (int i = 1; i <= 15; ++i) {
        goalState.push_back(i);
    }
    goalState.push_back(-1);


    vector<vector<int> > input(SIZE, vector<int>(SIZE));
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cin >> input[i][j];
        }
    }

    int expandedNodes = 0;
    int cost = BFS(input, expandedNodes, goalState);
    cout << cost << "\n";
    return 0;
}
