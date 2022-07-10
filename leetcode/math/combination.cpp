#include <iostream>
#include <vector>

using namespace std;

void printArr(int *arr, int len){
    for(int i=0; i<len; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}


void combination(int *arr, int *arr1, int len, int len1, int n, int offset, int index){
    if(n==0){
        printArr(arr1, len1);
        return;
    }

    for(int i=offset; i<len-n+1; i++){
        arr1[index]=arr[i];
        combination(arr, arr1, len, len1, n-1, i+1, index+1);
    }

}

int main(){
    int arr[]={1,2,3,4,5};
    int n=3;

    int len=sizeof(arr)/sizeof(arr[0]);
    int *arr1=new int[n];
    int len1=n;
    int offset=0; int index=0;
    combination(arr, arr1, len, len1, n, offset, 0);
}
