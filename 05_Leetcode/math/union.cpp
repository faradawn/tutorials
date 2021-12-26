#include <iostream>
#include <unordered_map>

using namespace std;

int brute_force(int *arr, int len){ // exceeds run time
    int max=0;
    int head=NULL;
    int ter=NULL;
    unordered_map<int, int> myHash;
    for(int i=0; i<len; i++){
        myHash[arr[i]]=1;
    }

    for(int i=0; i<len; i++){
        if(ter && arr[i]<=ter && arr[i]>=head){
            continue;
        }
        int tempHead=arr[i];
        int sum=1;
        int v=arr[i];
        while(1){
            v++;
            if(myHash[v]){
                sum++;
            }else{
                if(sum>max){
                    head=tempHead;
                    ter=v-1;
                    max=sum;
                }
                break;
            }
        }
    }
    return max;
}

int main(){
    cout<<"wrokding?"<<endl;
    int arr[]={100,4,200,1,3,2};
    brute_force(arr, sizeof(arr)/sizeof(arr[0]));
}