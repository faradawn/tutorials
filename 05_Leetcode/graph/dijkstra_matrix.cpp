#include <iostream>

using namespace std;

#define numV 6

void printDist(int dist[]){
    for(int i=0; i<numV; i++){
        cout<<dist[i]<<endl;
    }
}

int smallest(int dist[], int visited[]){
    int min=INT_MAX;
    int v=-1;
    for(int i=0; i<numV; i++){
        if(dist[i]<min && !visited[i]){
            min=dist[i];
            v=i;
        }
    }
    return v;
}

int dijkstra(int G[numV][numV], int s){
    int dist[numV];
    int visited[numV]={0};
    for(int i=0; i<numV; i++){
        dist[i]=INT_MAX;
    }
    dist[s]=0;

    for(int i=0; i<numV; i++){
        int v=smallest(dist, visited);
        visited[v]=1;

        int* adj = G[v];
        for(int j=0; j<numV; j++){
            if(adj[j] && !visited[j]){
                if(dist[v]+adj[j]<dist[j]){ // need to include dist[v]!=INT_MAX?
                    dist[j]=dist[v]+adj[j];
                }
            }
        }
        
    }
    printDist(dist);
    return 0;
}

int main(){
    int G[numV][numV] = {
		{0, 10, 20, 0, 0, 0},
		{10, 0, 0, 50, 10, 0},
		{20, 0, 0, 20, 33, 0},
		{0, 50, 20, 0, 20, 2},
		{0, 10, 33, 20, 0, 1},
		{0, 0, 0, 2, 1, 0}};
    int s = 0;
    dijkstra(G, s);
}