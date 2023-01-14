#include <iostream>
#include <vector>

using namespace std;

void round(vector<int> &arr){
    double sum=0;
    for(int i:arr){
        sum+=i;
    }
    double mean=sum/arr.size();
    double loss=0;
    for(int i:arr){
        double diff=i-mean;
        if(diff<0){
            diff=-diff;
        }
        loss+=diff;
    }
    cout<<(int)loss/2<<endl;
}

int main(){
    vector<int> arr={0,3};
    round(arr);

}