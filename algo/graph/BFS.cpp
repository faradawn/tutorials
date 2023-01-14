#include <iostream>
#include <list>

using namespace std;

typedef struct Graph{
    int largest;
    list<int> *adj;
}Graph;

void BFS(Graph G, int s){
    list<int>queue;
    int *visited = new int[G.largest+1];
    queue.push_back(s);
    visited[s] = 1;

    while(!queue.empty()){
        int a = queue.front();        
        queue.pop_front();
        cout<<a<<endl;

        for(auto &i : G.adj[a]){
            if(!visited[i]){
                queue.push_back(i);
                visited[i] = 1;
            }
        }
    }
    delete[] visited;
}

int main(){
    Graph G;
    G.largest=11;
    list<int> *adj = new list<int>[12];
    adj[0].push_back(9);
    adj[0].push_back(11);
    adj[0].push_back(7);
    adj[9].push_back(8);
    adj[9].push_back(10);
    adj[7].push_back(3);
    adj[7].push_back(6);
    adj[7].push_back(11);
    adj[11].push_back(0);
    adj[11].push_back(7);
    G.adj=adj;

    BFS(G, 0);
}
