[toc]

# Leetcode 剑指 Offer 03. 数组中重复的数字

## 问题描述

[剑指 Offer 03. 数组中重复的数字 - 力扣（LeetCode）](https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/comments/)

找出数组中重复的数字。

在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。数组中某些数字是重复的，
但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个
重复的数字。

示例 1：
输入：
[2, 3, 1, 0, 2, 5, 3]
输出：2 或 3 

限制：
2 <= n <= 100000

## 算法

### 解法一：使用hash表（dict or set）

时间复杂度：$O(n)$
空间复杂度： $O(n)$

#### 解法一python

```
class Solution:
    def findRepeatNumber(self, nums: List[int]) -> int:
        s = set()
        for x in nums:
            if x not in s:
                s.add(x)
            else:
                return x
```

### 解法二：使用数组

可以直接建立一个大小为 n 的数组 A，其中第 i 个元素 A[i] 对应数字 i 目前为止的出现次数

时间复杂度： $O(n)$
空间复杂度： $O(n)$

#### 解法二C++

```
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        int n = nums.size();
        vector<int> A(n, 0);
        for (int i=0; i<n; i++) {
            if (A[nums[i]] == 1) {
                return nums[i];
            } else {
                A[nums[i]] += 1;
            }
        }
        return -1;
    }
};
```

### 解法三：桶的思想

考虑到数字的范围为 0~n-1，数组的下标为 0~n-1，因此可以用数组的下标 i 对应于数字 i

对于nums数组中的第i个元素 nums[i] 有两个位置
1. i 表示 nums[i] 目前的位置
2. nums[i] 表示 nums[i] 应该处于的位置

时间复杂度： $O(n)$
空间复杂度： $O(1)$ 没有用到额外的空间

2020-08-14: 补充
其实这个还是一个 hash 的思想。将下标 i 和数值 i 对应起来。当发生 hash collision 时就返回。

#### 解法三：实现

##### 解法三：实现：c++

```
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        int i = 0;
        while (i < nums.size()) {
            if (nums[i] != i) 
            { // i位置和 i 位置上的值 nums[i] 不匹配
                // 检查 nums[i] 想去的位置上有没有正确的值
                if (nums[nums[i]] == nums[i])
                    return nums[i]; 
                else
                    swap(nums[i], nums[nums[i]]);
            }
            else
                i++;
        }
        return -1;
    }
};
```