#include <iostream>

using namespace std;

int main(){
    int n;
    int min=-1;
    int idx=0;
    cin >> n;

    
        if(i==0){
            min=x;
            continue;
        }
        if(x<min){
            min=x;
            idx=i;
        }
    }

    cout<<idx;

    return 0;
}