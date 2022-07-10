#include <iostream>
#include <list>
#include <vector>
#include <numeric>
#include <unordered_map>

using namespace std;

typedef vector<int> Arr;
int numV = 6;
Arr *adj=new Arr[numV];

typedef struct EdgeGraph{
    int left;
    int right;
    EdgeGraph(int x, int y){left=x; right=y;}
}EdgeGraph;

void create_list(int s, vector<int> &arr){
    for(auto &i : arr){
        adj[s].push_back(i);
    }
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

vector<EdgeGraph> create_edge_graph(vector<int> *adjList){
    vector<EdgeGraph> edgeList;
    unordered_map<int, int> myHash;
    for(int i=0; i<numV; i++){
        for(auto &j : adjList[i]){
            if(myHash[j] != i){
                edgeList.push_back(EdgeGraph(i, j));
                myHash[i]=j;
                cout<<"["<<i<<" - "<<j<<"] ";
            }
        }
    }
    return edgeList;
}

int checkCycle(vector<EdgeGraph> &edgeList){
    vector<int> parents(numV);
    iota(begin(parents), end(parents), 0);
    for(auto &i : edgeList){
        int l = findParent(i.left, parents);
        int r = findParent(i.right, parents);
        if(l == r){
            for(auto &i : parents){
                cout<< i << " ";
            }
            cout<<endl;
            return 1;
        }else{
            joinTwo(l, r, parents);
        }
    }
    for(auto &i : parents){
        cout<< i << " ";
    }
    cout<<endl;
    return 0;
}


int main(){
    Arr arr0={3,1};
    Arr arr1={0,4};
    Arr arr3={0,4};
    Arr arr4={3,1};
    Arr arr5={2};
    Arr arr2={5};
    create_list(0, arr0);
    create_list(1, arr1);
    create_list(2, arr2);
    create_list(3, arr3);
    create_list(4, arr4);
    create_list(5, arr5);
    
    vector<EdgeGraph> edgeList = create_edge_graph(adj);
    cout<< "\nis cycle? " << checkCycle(edgeList)<<endl;
   
}