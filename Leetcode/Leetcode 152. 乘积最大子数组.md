
[toc]

# Leetcode 152. 乘积最大子序列

## 问题描述

[152. 乘积最大子序列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/maximum-product-subarray/submissions/) 

给定一个整数数组 nums ，找出一个序列中乘积最大的连续子序列（该序列至少包含一个数）。

示例 1:

输入: [2,3,-2,4]
输出: 6
解释: 子数组 [2,3] 有最大乘积 6。

示例 2:
输入: [-2,0,-1]
输出: 0
解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。

## 算法

### 解法1: dp

#### 解法1:实现1: 

本身是想用两个数组，一个数组存最大的正数乘积，一个数组存最小的负数乘积。这样的话一个数组中的数是正的，另一个数组中的数是负的。但是考虑 nums[0] 如果小于 0 时。乘积为负的那个数组初始化为 nums[i] 乘积为正的数组却不知道如何初始化。

为了避免这个问题，干脆就一个数组存最大的乘积，一个数组存最小的乘积，不考虑正负了。

##### 解法1: c++

```
class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        n = len(nums)
        if n==1: 
            return nums[0]

        dpMax, dpMin = [0] * n, [0] * n
        dpMax[0] = dpMin[0] = ret = nums[0]
        for i in range(n):
            if nums[i] > 0:
                dpMax[i] = max(dpMax[i-1] * nums[i], nums[i])
                dpMin[i] = dpMin[i-1] * nums[i]
            else:
                dpMax[i] = dpMin[i-1] * nums[i]
                dpMin[i] = min(dpMax[i-1] * nums[i], nums[i])
            ret = max(ret, dpMax[i])
        return ret
```

#### 解法1:实现2

由于有负数，因此有可能将最小值变成最大值，因此需要保存最小值和最大值。

令 imax[i] 表示以 nums[i] 结尾的序列中的乘积最大值，imin[i]表示以 nums[i] 结尾的序列中的乘积最小值。则

$$
imax[i] = max(imax[i-1] * nums[i], imin[i-1] * nums[i], nums[i])
$$

$$
imin[i] = min(imax[i-1] * nums[i], imin[i-1] * nums[i], nums[i])
$$

最终输出的值值需要在 imax 中求最大值就可以了。

**这时不需要考虑正负号以及0。**

##### 解法1: 实现2: c++

```
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        vector<int> imax(n), imin(n);
        imax[0] = imin[0] = nums[0];
        int ret = nums[0];
        int tmp1, tmp2;
        for (int i=1; i<n; i++) {
            tmp1 = imax[i-1]* nums[i];
            tmp2 = imin[i-1]*nums[i];
            imax[i] = max(nums[i], max(tmp1, tmp2));
            imin[i] = min(nums[i], min(tmp1, tmp2));
            ret = max(ret, imax[i]);
        }
        return ret;
    }
};
```

### 解法1: 空间优化

注意到 $imax[i-1]$ 在计算完 $imax[i]$ 后就没有用了。因此只需要用一个变量就可以，不需要一个数组，$imin[i]$ 也一样

#### 解法1: 空间优化: 实现

##### 解法1: 实现: c++

```
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int imax = nums[0], imin = nums[0], ret=nums[0];
        int tmp1, tmp2;
        for (int i=1; i<n; i++) {
            tmp1 = imax * nums[i], tmp2 = imin*nums[i];
            imax = max(nums[i], max(tmp1, tmp2));
            imin = min(nums[i], min(tmp1, tmp2));
            ret = max(ret, imax);
        }
        return ret;
    }
};
```

