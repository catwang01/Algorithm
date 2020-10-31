
[toc]


# Leetcode 674. 最长连续递增序列 

## 问题描述

[674. 最长连续递增序列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/longest-continuous-increasing-subsequence/)
## 算法

### 解法1: dp

#### 解法1: c++

```cpp
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int n = nums.size();
        if (n<=1) return n;
        vector<int> dp(n, 1);
        int ret = 1;
        for (int i=1; i<n; i++) {
            if (nums[i] > nums[i-1]) {
                dp[i] = dp[i-1] + 1;
                ret = max(ret, dp[i]);
            }
        }
        return ret;
    }
};
```

### 解法1: dp 空间优化

#### 解法1: dp空间优化 c++

```cpp
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int n = nums.size();
        if (n<=1) return n;
        int dp = 1;
        int ret = 1;
        for (int i=1; i<n; i++) {
            dp = nums[i] > nums[i-1] ? dp + 1: 1;
            ret = max(ret, dp);
        }
        return ret;
    }
};
```