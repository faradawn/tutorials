#include <iostream>
#include <vector>

using namespace std;

long long goal;
long long n;
long long mult = 3 * 5 * 7;

long long three = 0;
long long five = 0;
long long seven = 0;

long long found = 0;
long long times = 0;

void dfs(long long cur){
    if(found == 1 or cur > goal){
        return;
    }
    if(cur == goal){
        found = 1;
        cout << three << " " << five << " " << seven << endl;
        return;
    }

    seven ++;
    dfs(cur + 7);
    seven --;

    five ++;
    dfs(cur + 5);
    five --;
    
    three ++;
    dfs(cur + 3);
    three --;
}

int main(){
    cin >> n;
    if(n < 3LL){
        cout << -1 << endl;
        return 0;
    }

    goal = n % (long long)mult;
    times = n / mult;
    seven += times * 15;

    dfs(0);

    if(found == 0){
        cout << -1 << endl;
    }

    return 0;
}