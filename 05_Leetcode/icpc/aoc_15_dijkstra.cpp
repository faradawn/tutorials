#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int dijkstra(vector<vector<int>> &matrix){
    
}

int main(){
    ifstream file {"aoc_15_input.txt"};
    if(!file.is_open()){
        cout<<"not open\n";
        return -1;
    }
    vector<vector<int>> matrix;
    string line;
    while(file>>line){
        vector<int>arr;
        for(char &c : line){
            arr.push_back(c-48);
        }
        matrix.push_back(arr);
    }

    cout<<matrix[0][0]<<" "<<matrix[1][3];


}