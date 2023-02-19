#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> visited;
long long tot_dist;

void dfs(vector<pair<int,int>> &coord, int x, int y){

}

int main(){
    int scene;
    cin >> scene;

    while(scene -- > 0){
        int width, height;
        cin >> width >> height;
        int sx, sy;
        cin >> sx >> sy;

        int num_beepers;
        cin >> num_beepers;

        vector<pair<int,int>> coord(num_beepers);
        for(int i = 0; i < num_beepers; i++){
            cin >> coord[i].first >> coord[i].second;
        }

        visited.resize()

        

    }

}