[toc]

# Leetcode 60. 第 k 个排列

## 算法

### 解法1: 回溯法

问题可以归结为找递归树中的第 k 棵。参考 [ 1 ]

#### 解法1: c++

```cpp
class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> nums(n);
        for(int i=0; i<n; i++) nums[i] = i+1;
        vector<int> seen(n ,0);
        string ret;
        dfs(n, ret, k, 0, seen, nums);
        return ret;
    }

    // frac with memo
    unordered_map<int, int> memo;
    int frac(int x) {
        if (!memo[x]) {
            if (x<=1)
                memo[x] = 1;  // 注意 frac(0) = 1
            else
                memo[x] = frac(x-1) * x;
        }
        return memo[x];
    }

    void dfs(int n, string& ret, int k, int prev, vector<int>& seen, const vector<int>& nums) {
        // prev 表示当前树之前的树有 prev 棵
        if (n==0) return;
        int n_subtree = frac(n-1);
        for (int i=0; i<nums.size(); i++) {
            if (!seen[i]) {
                if (k <= prev + n_subtree) {
                    ret += to_string(nums[i]);
                    seen[i] = 1;
                    dfs(n-1, ret, k, prev, seen, nums);
                    break;
                } else {
                    prev += n_subtree;
                }
            }
        }
    }
};
```

# References
1. [60. 第k个排列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/permutation-sequence/)