[toc]

# Leetcode 503. 下一个更大元素 II 

## 问题描述

[503. 下一个更大元素 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/next-greater-element-ii/)

## 算法


### 解法1: 单调栈

首先，由于元素是可以重复的，因此需要往栈中压入 index，而不是值。

其次，需要一个循环数组。易知可以用过 mod 操作来实现。

这个题的一个关键是什么时候停止循环。如果不是循环数组，那么很自然得，数组遍历完就停止循环。

对于本题来说，可以只遍历数组两次，遍历完就停止。因为两次之后，所有可以填的数字都填上了。

#### 解法1:实现

##### 解法1: 实现1： c++


```
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ret(n, -1);
        stack<int> s; 
        for (int i=0; i<2 * n; i++) { // 遍历数组两次，相当于将一个相同长度的数组拼接起来，因此数组长度为2n
            while (!s.empty() && nums[s.top()] < nums[i % n]) {
                if (ret[s.top()] == -1) {
                    ret[s.top()] = nums[i % n];
                }
                s.pop();
            }
            s.push(i % n);
        }
        return ret;
    }
};
```

##### 解法2: 实现1：python

```
class Solution:
    def nextGreaterElements(self, nums: List[int]) -> List[int]:
        n = len(nums)
        ret = [-1] * n
        for i in range(n):
            for j in range(i+1, i + n + 1):
                if nums[j % n] > nums[i]:
                    ret[i] = nums[j % n]
                    break
        return ret
```

# References
1. [单调栈解决 Next Greater Number 一类问题 - 下一个更大元素 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/next-greater-element-ii/solution/dan-diao-zhan-jie-jue-next-greater-number-yi-lei-2/)

