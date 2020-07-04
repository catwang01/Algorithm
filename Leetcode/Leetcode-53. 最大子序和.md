
[toc]

# Leetcode 53. 最大子序和

## 问题描述

- [53. 最大子序和 - 力扣（LeetCode）](https://leetcode-cn.com/problems/maximum-subarray/)

给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

示例:
输入: [-2,1,-3,4,-1,2,1,-5,4],
输出: 6
解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。

## 算法

### 法一：动态规划

动态规划的状态定义： dp[i] = 数组nums[0,1,2,...,i]中，**以nums[i]为结尾的区间的最大子序和**

在i时，有两种选择：
1. 将nums[i] 添加到 i-1 时的最大子序和数组中
2. 不将nums[i] 添加到 i-1 时的最大子序和数组中，此时是以 [nums[i]] 为i时的最大子序和数组

因此，有转移方程
$$
\begin{aligned}
dp[i] & = max(dp[i-1] + nums[i], nums[i]) \\
    & = max(dp[i-1], 0) + nums[i]
\end{aligned}
$$


#### 法一c++实现

```
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if (n==0) return 0;
        int dp[n] = {nums[0]}, maxSum=INT_MIN;
        for (int i=1; i<n; i++) {
            dp[i] = max(dp[i-1], 0) + nums[i];
            maxSum = max(maxSum, dp[i]);
        }
        return maxSum;
    }
};
```

#### 解法1: python 实现

```
class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        n = len(nums)
        dp = [0] * n
        dp[0] = nums[0]
        ret = dp[0]
        for i in range(1, n):
            dp[i] = nums[i] if dp[i-1] <= 0 else nums[i] + dp[i-1]
            ret = max(ret, dp[i])
        return ret
```

### 解法一空间压缩


注意到计算 dp[i] 时只需要用到 dp[i-1]，因此dp不需要用个一数组，直接用一个数就可以！

此时转移方程为（只需要将上面的转移方程中的dp的下标删除即可）

$$
\begin{aligned}
dp & = max(dp + nums[i], nums[i]) \\
    & = max(dp, 0) + nums[i]
\end{aligned}
$$

#### 解法一空间压缩c++实现

```
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        if (n==0) return 0;
        int dp = nums[0], maxSum=nums[0];
        for (int i=1; i<n; i++) {
            if (dp > 0) {
                dp += nums[i];
            } else {
                dp = nums[i];
            }
            maxSum = max(maxSum, dp);
        }
        return maxSum;
    }
};
```

#### 解法一空间压缩python实现

```
class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        n = len(nums)
        dp = nums[0]
        ret = dp
        for i in range(1, n):
            dp = nums[i] if dp <= 0 else nums[i] + dp
            ret = max(ret, dp)
        return ret
```


### 法二：分治法

从数组中间对半，将数组分成左右两个部分。则使子序列和最大子列有三种可能：
1. 在左边的数组中
2. 在右边的数组中
3. 横跨左右两个数组

这相当于将原问题分成三个子问题。其中，前两个问题可以递归求解，第三个子问题不能递归求解。
对于横跨左右数组的情况，中间的元素必定在使子序列和最大的子列中。因此可以从中间的元素向两边逐渐扩散，遍历两边所有的元素，记录下最大值并返回即可

时间复杂度： 设时间复杂度为 $T(n)$，则前两个子问题是递归求解的，只是问题规模减小了，因此是 $ 2 T(\frac{n}{2}$，第三个子问题中中间向两侧合起来实现了一次遍历，因此是 $O(n)$，分和并的操作格需要常数时间复杂度，即$O(1)$，因此有
$$T(n) = 2 T(\frac{n}{2}) + O(n) + O(1) = 2T(\frac{n}{2}) + O(n)$$
由master定理，$T(n) = O(nlogn)$

空间复杂度：$O(logn)$，因为递归使用了栈，栈的深度为 $O(logn)$（相当于有n个子节点的满二叉树的高度）

#### 法二c++实现

```
class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        n = len(nums)
        if n==0: return 0
        if n==1: return nums[0]
        return self.divide_and_conquer(nums, 0, n-1)
        
    def cross_sum(self, nums, low, mid, high):
        if low == high:
            return nums[low]
        else:
            s = 0
            s_max = -float("inf")
            for i in range(mid, low-1, -1):
                s += nums[i]
                s_max = max(s, s_max)

            s = s_max
            for i in range(mid+1, high+1):
                s += nums[i]
                s_max = max(s, s_max)
            return s_max
            
    def divide_and_conquer(self, nums, low, high):
        if low == high:
            return nums[low]
        if high-low == 1:
            return max(nums[low], nums[high], nums[low]+nums[high])
        else:
            mid = (low + high) // 2
            # 合并三个子问题的解
            return max(
                self.divide_and_conquer(nums, low, mid-1),
                self.divide_and_conquer(nums, mid+1, high),
                self.cross_sum(nums, low, mid, high)
            )
```
