#include <iostream>
#include <list>

using namespace std;

int hashFn(int data, int len){
    return data % len;
}

void insert(list<int> *h, int data, int len){
    int index = hashFn(data, len);
    h[index].push_back(data);
}

void remove(list<int> *h, int data, int len){
    int index = hashFn(data, len);
    list <int> :: iterator it;
    for(it = h[index].begin(); it != h[index].end(); it++){
        if(*it==data){
            if (it != h[index].end()){
                h[index].erase(it);
            }
            return;
        }
    }
}

void printHashList(list<int> *h, int len){
    for(int i=0; i<len; i++){
        for(int it : h[i]){
            cout<<it<<" - ";
        }
        cout<<endl;
    }
}

int main(){
    int arr[]={20, 34, 56, 54, 76, 87};
    int len = sizeof(arr)/sizeof(arr[0]);
    list<int> *hashList = new list<int>[len];

    for(int i=0; i<len; i++){
        insert(hashList, arr[i], len);
    }

    remove(hashList, 34, len);

    printHashList(hashList, len);
}

