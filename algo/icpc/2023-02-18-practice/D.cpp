#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n;
    int k;
    cin >> n >> k;
    long long minn = 0;
    long long maxx = 0;
    vector<long long> b(n, 0);

    for(int i = 0; i < n; i ++){
        cin >> b[i];
    }

    sort(b.begin(), b.end());
    maxx = b[b.size()-1];

    for(int i = b.size()-2; i >= 0; i--){
        maxx += b[i];
        minn = 0;
        k --;
        if(k == 0){
            break;
        }
    }

    cout << maxx - minn << endl;

    return 0;
}