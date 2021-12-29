#include <iostream>
#include <vector>
#include "helper.h"

using namespace std;

void foo(int a){
    cout<<a<<"yaya!"<<endl;
}

void printArr(vector<int> &arr){
    for(int i : arr){ cout<<i<<" "; }
    cout<<endl;
}