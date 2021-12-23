#include <iostream>

using namespace std;

int brute_force(int* W, int* V, int len, int maxW){
    int maxVal=0;
    for(int k=1; k<=len; k++){
        for(int j=0; j<len-k+1; j++){
            int vSum=0;
            int wSum=0;
            for(int i=j; i<j+k; i++){
                if(wSum+W[i]<=maxW){
                    vSum+=V[i];
                    wSum+=W[i];
                    if(k==5){
                        cout<<V[i] << ": " <<vSum<<" "<< wSum <<endl;
                    }
                }
            }
            if(vSum>maxVal){
                maxVal=vSum;
            }
        }
    }
    return maxVal;
}

int main(){
    int W[]={6,4,2,10,7};
    int V[]={8,3,1,14,9};
    int maxW=15;
    int len = sizeof(W)/sizeof(W[0]);
    cout<< "res "<<brute_force(W, V, len, maxW)<<endl;
}