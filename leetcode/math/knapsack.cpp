#include <iostream>

using namespace std;

int max(int a, int b){return a > b ? a : b;}

int maxVal(int* wt, int* vt, int W, int len){
    int *dp= new int[W+1]{0};
    for(int i=0; i<len; i++){
        int thisWeight = wt[i];
        int thisVal = vt[i];
        for(int j=W; j>=0; j--){    
            if(thisWeight<=j){
                if(thisVal+dp[j-thisWeight] > dp[j]){
                    dp[j]=thisVal + dp[j-thisWeight];
                }
            }
        }
    }
    return dp[W];
}

int main(){
    int wt[]={1,2,3};
    int vt[]={2,3,5};
    int W=5;
    int len=sizeof(wt)/sizeof(wt[0]);
    cout<<maxVal(wt, vt, W, len);

}