#include <iostream>
#include <vector>

using namespace std;

void printArr(vector<int> arr){
    for(int &i : arr){
        cout<<i<<" ";
    }
    cout<<endl;
}
void swap(int *a, int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

void heapify(vector<int> &arr, int i, int len){
    int l=2*i+1;
    int r=2*i+2;
    int largest=i;
    if(l<len && arr[l]>arr[largest]){
        largest=l;
    }
    if(r<len && arr[r]>arr[largest]){
        largest=r;
    }
    if(largest!=i){
        swap(&arr[largest], &arr[i]);
        heapify(arr, largest, len);
    }
}

void heapSort(vector<int> &arr){
    for(int n=arr.size()-1; n>0; n--){
        swap(&arr[0], &arr[n]);
        heapify(arr, 0, n);
    }

}

int main(){
    vector<int>arr={1, 12, 9, 5, 6, 10, 5};
    // build heap
    int p=arr.size()/2-1;
    for(int i=p; i>=0; i--){
        heapify(arr, i, arr.size());
    }
    printArr(arr);
    // sort heap
    heapSort(arr);
    printArr(arr);

    

}