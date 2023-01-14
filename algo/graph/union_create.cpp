#include <iostream>
#include <list>
#include <vector>
#include <numeric>
#include <unordered_map>


using namespace std;

typedef vector<int> Arr;
int numV = 6;
Arr *adj=new Arr[numV];

typedef struct Graph{
    int V;
    vector<int> *adj;
}Graph;

typedef struct EdgeGraph{
    int left;
    int right;
}EdgeGraph;

void create_list(int s, vector<int> &arr){
    for(auto &i : arr){
        adj[s].push_back(i);
    }
}

vector<EdgeGraph> create_edge_graph(const vector<int> &adjList){
    vector<EdgeGraph> edgeList;
    return edgeList;
}

int findParent(int x, vector<int> &parents){
    if(x == parents[x]){
        return x;
    }else{
        return findParent(parents[x], parents);
    }
}

void joinTwo(int x, int y, vector<int> &parents){
    parents[findParent(x, parents)]=findParent(y, parents);
}

Arr createUnion(Arr *adjList){
    unordered_map<int, int> visited;
    Arr parents(numV);
    iota(begin(parents), end(parents), 0);
    for(int i=0; i<numV; i++){
        for(auto &j : adjList[i]){
            if(!visited[j]){
                joinTwo(j, i, parents);
                visited[j]=1;
            }
        }
    }

    return parents;
}

int main(){
    Arr arr0={3,1};
    Arr arr1={0};
    Arr arr3={0,4};
    Arr arr4={3};
    Arr arr5={2};
    Arr arr2={5};
    create_list(0, arr0);
    create_list(1, arr1);
    create_list(2, arr2);
    create_list(3, arr3);
    create_list(4, arr4);
    create_list(5, arr5);

    Arr unionList = createUnion(adj);
    for(auto &i : unionList){
        cout<<i<<" ";
    }
}