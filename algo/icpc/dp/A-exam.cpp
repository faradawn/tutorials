#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print_max(vector<vector<int>> &mat){
    for(auto& vec : mat){
        for(auto i : vec){
            cout << i << " ";
        }
        cout << endl;
    }
}

int main(){
    string nn;
    getline(cin, nn);
    int n = stoi(nn);
    string line1;
    string line2;
    getline(cin, line1);
    getline(cin, line2);

    if(line1.length() == 0){
        cout << 0 << endl;
    }
    

    vector<vector<int>> dp(n + 1, vector<int>(line1.length() + 1, 0));

    for(int i = 1; i < dp[0].size(); i++){
        dp[0][i] = dp[0][i-1] + (line1[i-1] != line2[i-1]);
    }

    for(int i =1; i < dp.size(); i++){
        dp[i][i] = dp[i-1][i-1] + (line1[i-1] == line2[i-1]);
    }

    for(int i = 1; i < dp.size(); i ++ ){
        for(int j = i + 1; j < dp[0].size(); j++){
            // max(if friend is correct, if friend is not correct)
            dp[i][j] = max((line1[j-1]==line2[j-1]) + dp[i-1][j-1], (line1[j-1] != line2[j-1]) + dp[i][j-1]);
        }
    }

    // print_max(dp);

    cout << dp[dp.size()-1][dp[0].size()-1] << endl;

}