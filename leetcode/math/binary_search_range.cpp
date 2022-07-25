// Leetcode 
// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/discuss/14699/Clean-iterative-solution-with-two-binary-searches-(with-explanation)

// Method 1: first smaller and first bigger
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int>res(2,-1);
        
        if(nums.size() == 0){
            return res;
        }
        
        int l = 0, r = nums.size()-1, m = 0;
        int a = -1;
        int b = nums.size();
        while(l <= r){
            m = l + (r - l)/2;
            if(nums[m] < target){
                a = m;
                l = m + 1;
            }else r = m - 1;
        }
        
        l = 0;
        r = nums.size()-1;
        while(l <= r){
            m = l + (r-l)/2;
            if(nums[m] > target){
                b = m;
                r = m - 1;
            }
            else l = m + 1;
        }
        
        if(a >= (int)nums.size()-1 || b <= 0 || b-a == 1){
            return res;
        }
        
        res[0] = a + 1;
        res[1] = b - 1;
        return res;
    }
};


// Method 2: beginning index and ending index (biased left and right)

vector<int> searchRange(int A[], int n, int target) {
    int i = 0, j = n - 1;
    vector<int> ret(2, -1);
    // Search for the left one
    while (i < j)
    {
        int mid = (i + j) /2;
        if (A[mid] < target) i = mid + 1;
        else j = mid;
    }
    if (A[i]!=target) return ret;
    else ret[0] = i;
    
    // Search for the right one
    j = n-1;  // We don't have to set i to 0 the second time.
    while (i < j)
    {
        int mid = (i + j) /2 + 1;	// Make mid biased to the right
        if (A[mid] > target) j = mid - 1;  
        else i = mid;				// So that this won't make the search range stuck.
    }
    ret[1] = j;
    return ret; 
}



// classic binary search
int search(vector<int>& nums, int target) {
	int l = 0;
	int r = nums.size()-1;
	int m;
	while(l <= r){
		m = l + (r-l)/2;
		if(nums[m] == target){
			return m;
		}
		if(nums[m] < target){
			l = m + 1;
		}else{
			r = m - 1;
		}
	}
	return -1;
}
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
