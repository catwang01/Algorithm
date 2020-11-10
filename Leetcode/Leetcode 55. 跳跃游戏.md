[toc]


# Leetcode 55. 跳跃游戏

## 问题描述

[55. 跳跃游戏 - 力扣（LeetCode）](https://leetcode-cn.com/problems/jump-game/)

给定一个非负整数数组，你最初位于数组的第一个位置。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个位置。

**示例 1:**
**输入:** [2,3,1,1,4]
**输出:** true
**解释:** 我们可以先跳 1 步，从位置 0 到达 位置 1, 然后再从位置 1 跳 3 步到达最后一个位置。

**示例 2:**
**输入:** [3,2,1,0,4]
**输出:** false
**解释:** 无论怎样，你总会到达索引为 3 的位置。但该位置的最大跳跃长度是 0 ， 所以你永远不可能到达最后一个位置。


## 算法

### 解法1.1: 递归

注意如果遇到0的话不能直接返回false。需要判断一下是否是最后一个 index。 如果是的话，返回 true。否则返回 false;

#### 解法1.1:实现

##### 解法1.1： c++ 超时

```
class Solution {
public:
    bool canJump(vector<int>& nums) {
        if (nums.size()<=1) return true;
        return dp(0, nums);
    }

    bool dp(int i, const vector<int>& nums) {
        if (i>=nums.size()) return true;
        if (nums[i]==0) {
            return (i==nums.size()-1);
        }
        for (int k=1; k<=nums[i]; k++) {
            if (dp(i+k, nums)) return true;
        } 
        return false;
    }
};
```

### 解法1.2: dp

用dp数组来记录某个位置是否可达；
dp[i] = True 表示 i 位置可达，若 dp[i] = True，则 dp[i+1], ..., dp[i+nums[i]] 都可达，即这些值均为 True

时间复杂度：$O(n^2)$ 二重循环，内循环至多运行 $O(n)$ 次
空间复杂度： $O(n)$

上面的递归修改为 dp

#### 解法1.2: 实现

##### 解法1.2: c++ 超时

```
class Solution {
public:
    bool canJump(vector<int>& nums) {
        if (nums.size()<=1) return true;
        int n = nums.size();
        vector<bool> dp(n, false);
        int i = n-1;
        dp[n-1] = true;
        bool flag;
        while (i--) {
            for (int k=1; k<=nums[i]; k++) {
                if (dp[i+k]) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[0];
    }
};
```


##### 解法1.2: python 超时

```
class Solution:
    def canJump(self, nums: List[int]) -> bool:
        n = len(nums)
        if n==0: return False
        if n==1: return True

        dp = [False] * n
        dp[n-1] = True
        for i in range(n-2, -1, -1):
            for k in range(1, nums[i]+1):
                dp[i] = dp[i+k]
                if dp[i]: break
        return dp[0]
```

### 解法2：贪心

时间复杂度： $O(n)$
空间复杂度： $O(n)$

用 maxIndex 表示可达的最大下标，遍历所有可达的下标，并不断更新 maxIndex，若 maxIndex < n-1，说明最后一个位置不可达；反之，说明最后一个位置可达。

贪 maxIdx。可以这样做的原因是，只要可以到达 maxIdx，那么比 maxIdx 小的位置都可以到达。

#### 解法2: 实现

##### 解法2： python


```
class Solution:
    def canJump(self, nums: List[int]) -> bool:
        n = len(nums)
        if n == 1: return True
        maxIndex = nums[0]
        i = 1
        while i <= maxIndex:
            maxIndex = max(maxIndex, nums[i] + i)
            if maxIndex >= n-1:
                return True
            i += 1;
        return False
```


##### 解法2: c++


```
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int maxIndex = 0;
        for (int i=0; i<nums.size(); i++) {
            if (maxIndex < i) return false; // 如果不能到达，就return
            maxIndex = max(maxIndex, nums[i] + i);
        }
        return true;
    }
};
```
