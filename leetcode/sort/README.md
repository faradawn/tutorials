# 自定义 Operator

## Custom Sort
```c++
// using lambda
auto cmp = [](vector<int>& v1, vector<int>& v2){
    return v1[2] > v2[2] or (v1[2] == v2[2] and v1[3] < v2[3]);
};

sort(bids.begin(), bids.end(), cmp);
sort(bids.begin(), bids.end(), Compare());
```

## Custom Map and Set
```c++
struct Compare_Bid{
    bool operator() (const vector<int>& v1, const vector<int>& v2) const {
        return v1[2] > v2[2] or (v1[2] == v2[2] and v1[3] < v2[3]);
    }
};

struct Greater_Int{
    bool operator() (int a, int b) const {
        return a > b;
    }
};

map<int, set<vector<int>, Compare_Bid>, Greater_Int >map_bids;

for(auto& vec : bids){
    map_bids[vec[2]].insert(vec);
}
```


## Custom Priority Queue (min-heap)
```c++
struct Greater{
    bool operator()(tuple<int,int,int> const &t1, tuple<int,int,int> const &t2){
        return get<0>(t1) > get<0>(t2);
    }
};

priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, Greater>q;

q.push({1,2,3});
```












