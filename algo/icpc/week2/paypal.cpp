#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <cstdio>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);


/*
 * Complete the 'playlist' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts INTEGER_ARRAY songs as parameter.
 * Input0004 -> 2215
 */

long playlistnew(vector<int>& songs){
    vector<int> modsongs(songs.size());
    long long cnt = 0;
    long long target = 60;
    map<int, int> mp;

    for(int i = 0; i < songs.size(); i++){
        mp[songs[i] % 60] ++;
    }
    
    long acc = 0;

    if(mp.count(30) > 0){
        int cnt = mp[30];
        acc += cnt * (cnt-1) / 2;
    }

    for(auto &it : mp){
        int cur = it.first; 
        if(cur >= 30) break;
        if(mp.count(60-cur) > 0){
            acc += mp[cur] * mp[60-cur];
        }
    }
    return acc;
}

long playlist(vector<int> songs) {
    vector<int> modsongs(songs.size());
    long cnt = 0;
    long long target = 60;

    for(int i = 0; i < songs.size(); i++){
        modsongs[i] = songs[i] % 60;
    }
    sort(modsongs.begin(), modsongs.end());
    
    int l = 0;
    int r = modsongs.size()-1;
    while(l < modsongs.size() and modsongs[l] == 0){
        l ++;
    }
    
    cnt = (l-1) * l / 2;
    
    while(l < r){
        int left = modsongs[l];
        int right = modsongs[r];
        int sum = left + right;
        if(sum < target){
            l ++;
        }else if(sum > target){
            r --;
        }else{
            if(r - l == 1){
                cnt ++;
                break;
            }
            int acc_right = 0;
            int acc_left = 0;
            while(r > l and modsongs[r] == right){
                r --;
                acc_right ++;
            }
            while(r > l and modsongs[l] == left){
                l ++;
                acc_left ++;
                
            }
            cnt += acc_left * acc_right;
        }
    }
    return cnt;
}
int main()
{
    int n;
    cin >> n;
    vector<int> input1(n);
    for(int i = 0; i < n; i++){
        cin >> input1[i];
    }
    cout << "res " << playlistnew(input1) << endl;
}
