// faster segment tree LeetCode
// https://leetcode.com/problems/range-sum-query-mutable/discuss/1218358/C%2B%2B-or-Segment-Tree-or-Explained

#include <vector>
#include <iostream>
using namespace std;

class Solution{
    public:
        vector<int>tree;

        void update(int l, int r, int arr_idx, int idx, int diff){
            if(l == r and l == arr_idx){
                tree[idx] += diff;
            }else if(arr_idx > r or arr_idx < l){
                return;
            }else{
                tree[idx] += diff;
                int mid = l + (r-l)/2;
                update(l, mid, arr_idx, 2*idx+1, diff);
                update(mid+1, r, arr_idx, 2*idx+2, diff);
            }
        }

        int query(int l, int r, int a, int b, int idx){
            if(l>=a and r<=b){
                return tree[idx];
            }else if(l>b or r<a){
                return 0;
            }else{
                int mid = l + (r-l)/2;
                return query(l, mid, a, b, 2*idx+1) + query(mid+1, r, a, b, 2*idx+2);
            }
        }

        int build(int l, int r, int idx, vector<int> &arr){
            if(l == r){
                tree[idx] = arr[l];
                return arr[l];
            }else{
                int mid = l + (r-l)/2;
                tree[idx] = build(l, mid, 2*idx+1, arr) + build(mid+1, r, 2*idx+2, arr);
                return tree[idx];
            }
        }

        void init(vector<int> &arr){
            tree = vector<int>(4*arr.size(), -1);
            build(0, arr.size()-1, 0, arr);

            cout<<"Tree built: ";
            for(int &i : tree){
                cout<<i<<" ";
            }
            cout<<endl;
        }
};

int main(){
    Solution ob;
    int a[] = {1,3,5,7,9,11};
    vector<int>arr(a, a+sizeof(a)/sizeof(a[0]));
    ob.init(arr);
    cout<<"query result: "<<ob.query(0, arr.size()-1, 0, 2, 0)<<endl;
    ob.update(0, arr.size()-1, 1, 0, 2);
    cout<<"query result: "<<ob.query(0, arr.size()-1, 0, 2, 0)<<endl;
    cout<<"query result: "<<ob.query(0, arr.size()-1, 3, 5, 0)<<endl;
    cout<<"query result: "<<ob.query(0, arr.size()-1, 4, 5, 0)<<endl;
    cout<<"query result: "<<ob.query(0, arr.size()-1, 0, 5, 0)<<endl;
}
