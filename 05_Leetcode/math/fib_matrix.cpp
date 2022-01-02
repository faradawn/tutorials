#include <iostream>

using namespace std;

void printArr(int *arr){
    for(int i=0;i<3;i++){
        cout<<arr[i]<<" ";

    }
    cout <<endl;
}

void matmul(int (*matrix)[3], int v[], int res[]){
    for(int i=0;i<3;i++){
        int sum=0;
        for(int j=0;j<3;j++){
            sum+=matrix[i][j]*v[j];
        }
        res[i]=sum;
    }
    for(int i=0; i<3; i++){
        v[i]=res[i];
    }
}

int fib(int n){
    if(n==0){return 0;}
    if(n<=2){return 1;}
    int res[]={0,0,0};
    int v[]={1,1,0};
    int matrix[][3]={{1,1,1},{1,0,0},{0,1,0}};

    while(n>=3){
        matmul(matrix, v, res);
        n--;
    }
    return res[0];
}

int main(){
    cout<<fib(4);
    
}