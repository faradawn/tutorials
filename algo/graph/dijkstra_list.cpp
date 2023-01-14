#include <iostream>

using namespace std;

typedef struct Node{
    int v;
    int dist;
    int path[];
    Node(){v=0; dist=INT_MAX;}
    Node(int x){v=x; dist=INT_MAX;}
}Node;

typedef struct Graph{
    Node* adj[];
}Graph;

int dijkstra(Graph G, int s){
    return 0;
}

int main(){
    Graph G;
    int numNodes = 9;
    Node adj[numNodes];
    for(int i=0; i<numNodes; i++){
        adj[i]=Node(i);
    }
    cout << adj[5].v<<endl;
    
}