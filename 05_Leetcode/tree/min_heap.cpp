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

void heapifyDown(vector<int> &arr){
    int i=0;
    int l=2*i+1;
    int r=2*i+2;
    while(l<arr.size()){
        if(l==arr.size()-1){
            if(arr[l]<arr[i]){
                swap(arr[l], arr[i]);
                return;
            }
        }else{
            if(arr[l]<arr[r] && arr[l]<arr[i]){
                swap(arr[l], arr[i]);
                i=l;
                l=2*i+1;
                r=2*1+2;
            }else if(arr[r]<arr[l] && arr[i]<arr[r]){
                swap(arr[r], arr[i]);
                i=r;
                l=2*i+1;
                r=2*i+2;
            }
        }
    }
}

int main(){
    vector<int> arr={25,15,20,17};
    heapifyDown(arr);
    printArr(arr);
}