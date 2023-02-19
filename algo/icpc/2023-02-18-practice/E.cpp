#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    
    cout << 2 << endl;
    cout << n-1 << " " << n << endl;

    while(n - 2 > 0){
        cout << n - 2 << " " << n << endl;
        n --;
    }

    return 0;
}