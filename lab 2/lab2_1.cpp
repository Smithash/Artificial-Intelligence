#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

pair<int, int> getPoints(){
    string line;
    cin >> line;
    stringstream ss(line);

    pair<int, int> points;
    getline(ss, line, ',');
    points.first = stoi(line);

    getline(ss, line, ',');
    points.second = stoi(line);

    return points;
}

//Finding the dominat Row
vector<int> maxInRows(vector<vector<pair<int,int> > > &points, int n) {
    vector<int> result(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i] = max(points[i][j].first, result[i]);
        }
    }

    return result;
}

int main(){
    int n;
    cin >> n;

    //playoff matrix
    vector<vector<pair<int, int> > > matrix(n, vector<pair<int, int> > (n));
    //creating the playoff matrix
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            matrix[i][j] = getPoints();
        }
    }

    //Dominant row 
    vector<int> result = maxInRows(matrix, n);

    int rowIndex = 0;

    for (int i = 1; i < n; ++i) {
        if (result[i] > result[rowIndex]) {
            rowIndex = i;
        }
    }

    int colIndex = 0;
    //finding the dominant column from the dominant row
    for (int j = 1; j < n; ++j) {
        if (matrix[rowIndex][j].second > matrix[rowIndex][colIndex].second) {
            colIndex = j;
        }
    }

    printf("%d,%d\n", matrix[rowIndex][colIndex].first, matrix[rowIndex][colIndex].second);
   

   
    return 0;
}
