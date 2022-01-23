#include <iostream>
#include <vector>

using namespace std;

void printArr(vector<int> &vec){
    for(int i: vec){
        cout<<i<<" ";
    }
    cout<<endl;
}

int main(){
    int n; int q;
    cin>>n>>q;
    
    vector<int> vec(n);

    for(int i=0; i<n; i++){
        int c;
        cin>>c;
        cout<<c<<endl;
        vec[i]=c;
    }
    printArr(vec);

    for(int i=0; i<n; i++){

    }
}