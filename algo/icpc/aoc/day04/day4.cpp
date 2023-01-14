#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <cstdio>
#include <queue>

using namespace std;

int main(){
    std::ifstream myfile ("day4/input2.txt");
    std::string myline;

    long long tot = 0;

    while(myfile){
        std::getline (myfile, myline);
        if(myline.length() == 0) break;
        int idx1 = myline.find('-'); 
        int idx2 = myline.find('-', idx1 + 1);
        int mid = myline.find(',');

        int a = stoi(myline.substr(0, idx1));
        int b = stoi(myline.substr(idx1+1, mid - (idx1+1)));
        int c = stoi(myline.substr(mid+1, idx2 - (mid+1)));
        int d = stoi(myline.substr(idx2+1, myline.length() - (idx2+1)));

        // cout << idx1 << " " << mid << " " << idx2 << endl;
        // cout << a << " " << b  << " " <<  c << " " << d << endl;
        
        if((c >= a && d <= b) || (a >= c && b <= d) || (c <= b && c >= a) || (d >= a && d <= b)){
            cout << a << " " << b << " " << c << " " << d << endl;
            tot ++;
        }

        // if(a <= d && c <= b){
        //     cout << a << " " << b << " " << c << " " << d << endl;
        //     tot ++;
        // }

    }

    
    cout << "total " << tot << endl;
}