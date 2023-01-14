#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int cnt = n-1;
    int num = 0;
    while(n --){
        char c;
        cin >> c;
        if(c == 'O'){
            num += 1 << cnt;
        }
        cnt --;
    }

    cout << num;
}