// raw search
vector<int> searchRange(vector<int>& nums, int target) {
        int l=0;
        int r=nums.size()-1;
        int l2, r1, m, m1, m2;
        l2=r1=-1;
        while(l<=r){
            m=(l+r)/2;
            if(nums[m]<target){
                l=m+1;
            }else if(nums[m]>target){
                r=m-1;
            }else{
                l2=m-1;
                r1=m+1;

                while(l<=l2){
                    m1=(l+l2)/2;
                    if(nums[m1]<target){
                        l=m1+1;
                    }else{
                        l2=m1-1;
                    }
                }
                l2=l2+1;

                while(r>=r1){
                    m2=(r1+r)/2;
                    if(nums[m2]>target){
                        r=m2-1;
                    }else{
                        r1=m2+1;
                    }
                }
                r1=r1-1;

                break;

            }
        }
        vector<int> res(2);
        res[0]=l2;
        res[1]=r1;
        return res;
    }


// offical method

vector<int> searchRange(vector<int>& nums, int target) {
    int l=0;
    int r=nums.size()-1;
    int m;
    int l_res=-1;
    int r_res=-1;

    // search left index
    while(l<=r){
        m=(l+r)/2;
        if(nums[m]>=target){
            if(nums[m]==target){
                l_res=m;
            }
            r=m-1;
        }else{
            l=m+1;
        }
    }

    // search right index
    l=0; r=nums.size()-1;
    while(l<=r){
        m=(l+r)/2;
        if(nums[m]<=target){
            if(nums[m]==target){
                r_res=m;
            }
            l=m+1;
        }else{
            r=m-1;
        }
    }

    return vector<int>{l_res, r_res};
}