[toc]

# Leetcode 1671. 得到山形数组的最少删除次数

## 问题描述

[1671. 得到山形数组的最少删除次数 - 力扣（LeetCode）](https://leetcode-cn.com/problems/minimum-number-of-removals-to-make-mountain-array/)


我们定义 `arr` 是 **山形数组** 当且仅当它满足：

*   `arr.length >= 3`
*   存在某个下标 `i` （**从 0 开始**） 满足 `0 < i < arr.length - 1` 且：
    *   `arr[0] < arr[1] < ... < arr[i - 1] < arr[i]`
    *   `arr[i] > arr[i + 1] > ... > arr[arr.length - 1]`

给你整数数组 `nums`​ ，请你返回将 `nums` 变成 **山形状数组** 的​ **最少** 删除次数。

**示例 1：**

**输入：**nums = \[1,3,1\]
**输出：**0
**解释：**数组本身就是山形数组，所以我们不需要删除任何元素。

**示例 2：**

**输入：**nums = \[2,1,1,5,6,2,3,1\]
**输出：**3
**解释：**一种方法是将下标为 0，1 和 5 的元素删除，剩余元素为 \[1,5,6,3,1\] ，是山形数组。

**示例 3：**

**输入：**nums = \[4,3,2,1,1,2,3,1\]
**输出：**4

**提示：**

**输入：**nums = \[1,2,3,4,4,3,2,1\]
**输出：**1

**提示：**

*   `3 <= nums.length <= 1000`
*   `1 <= nums[i] <= 109`
*   题目保证 `nums` 删除一些元素后一定能得到山形数组。


## 算法

### 解法1 LIS

问题转化：题目要求的是得到山形数组的最少删除数。换个角度，是在求最长山形子序列。

这个和最长上升子序列(LIS)有点相似，但是又不同。LIS 有单调性，因此可以用 dp。但是最长山形子序列没有这种性质。

如果我们固定 nums[i] 作为山的顶点，那么问题实际上变成了求左侧求以 nums[i] 为结尾的最长上升子序列，右侧求以 nums[i] 为开头的最长下降子序列(这个实际上只是反方向的 LIS 问题)

注意到，我们的左侧的最长上升子序列的长度不能小于2，右侧的最长下降子序列的长度也不能小于2。

#### 解法1: 

##### 解法1： 实现：python


```
class Solution:
    def minimumMountainRemovals(self, nums: List[int]) -> int:
        n = len(nums)
        dp_up = [1] * n
        for i in range(n):
            for k in range(i):
                if nums[i] > nums[k]:
                    dp_up[i] = max(dp_up[i], dp_up[k] + 1)
                
        dp_down = [1] * n
        for i in range(n-1, -1, -1):
            for k in range(n-1, i, -1):
                if nums[i] > nums[k]:
                    dp_down[i] = max(dp_down[i], dp_down[k] + 1)
        
        print(dp_up, dp_down)
        ret = 0
        for i in range(n):
            if dp_up[i] >= 2 and dp_down[i] >= 2:
                ret = max(ret, dp_up[i] + dp_down[i] - 1)
        return n - ret
```