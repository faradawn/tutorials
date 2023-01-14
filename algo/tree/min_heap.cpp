#include <iostream>
#include <vector>
using namespace std;

void printArr(vector<int> &arr){
    for(int &i : arr){
        cout<<i<<" ";
    }
    cout<<endl;
}

void swap(int *i, int *j){
    int temp=*i;
    *i=*j;
    *j=temp;
}

void heapifyUp(int i, vector<int> &arr){
    int p=(i-1)/2;
    while(p>=0 && arr[i]<arr[p]){
        swap(&arr[i], &arr[p]);
        i=p;
        p=(i-1)/2;
    }
}

void heapifyDown(vector<int> &arr, int i){
    int l=2*i+1;
    int r=2*i+2;
    int smallest=i;
    while(l<arr.size()){        
        if(l<arr.size() && arr[l]<arr[i]){
            smallest=l;
        }
        if(r<arr.size() && arr[r]<arr[smallest]){
            smallest=r;
        }
        if(smallest!=i){
            swap(&arr[smallest], &arr[i]);
            i=smallest;
            l=2*i+1;
            r=2*i+2;
            smallest=i;
        }else{
            return;
        }
    }
}

 void heapDown(vector<int> &heap, int i){
        int l=(2*i)+1;
        int r=(2*i)+2;
            int smallest=i;
            if(l<heap.size() && heap[l]<heap[i]){
                smallest=l;
            }
            if(r<heap.size() && heap[r]<heap[smallest]){
                smallest=r;
            }
            if(smallest!=i){
                swap(&heap[smallest], &heap[i]);
                heapDown(smallest);
            }

    }

int main(){
    vector<int> arr={25,15,20,17};
    heapifyDown(arr, 0);
    printArr(arr);
}