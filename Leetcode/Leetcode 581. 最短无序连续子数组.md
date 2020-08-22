
[toc]

# Leetcode 581. 最短无序连续子数组

## 问题描述

[581. 最短无序连续子数组 - 力扣（LeetCode）](https://leetcode-cn.com/problems/shortest-unsorted-continuous-subarray/)

给定一个整数数组，你需要寻找一个连续的子数组，如果对这个子数组进行升序排序，那么整个数组都会变为升序排序。

你找到的子数组应是最短的，请输出它的长度。

示例 1:

输入: [2, 6, 4, 8, 10, 9, 15]
输出: 5
解释: 你只需要对 [6, 4, 8, 10, 9] 进行升序排序，那么整个表都会变为升序排序。
说明 :

输入的数组长度范围在 [1, 10,000]。
输入的数组可能包含重复元素 ，所以升序的意思是<=。

##  算法

### 解法1：


```
class Solution:
    def findUnsortedSubarray(self, nums: List[int]) -> int:
        n = len(nums)
        st = [-1]
        
        # (l, r) 无序数组
        i, l = 0, n
        while i < n:
            while (st[-1]!=-1 and nums[st[-1]] > nums[i]):
                st.pop()
                l = min(l, st[-1])
            st.append(i)
            i += 1

        j, r = n-1, -1
        st = [n]
        while j >= 0:
            while st[-1] != n and nums[st[-1]] < nums[j]:
                st.pop()
                r = max(r, st[-1])  
            st.append(j)
            j -= 1
        if l >= r:
            return 0
        else:
            return r - l - 1
```

### 解法2：单调栈

#### 解法2: 实现

##### 解法2: 实现：python

```
class Solution:
    def findUnsortedSubarray(self, nums: List[int]) -> int:
        n = len(nums)
        st = [-1]
        
        # (l, r) 无序数组
        i, l = 0, n
        while i < n:
            while (st[-1]!=-1 and nums[st[-1]] > nums[i]):
                st.pop()
                l = min(l, st[-1])
            st.append(i)
            i += 1

        j, r = n-1, -1
        st = [n]
        while j >= 0:
            while st[-1] != n and nums[st[-1]] < nums[j]:
                st.pop()
                r = max(r, st[-1])  
            st.append(j)
            j -= 1
        if l >= r:
            return 0
        else:
            return r - l - 1
```

# References
1. [581. 最短无序连续子数组 - 力扣（LeetCode）](https://leetcode-cn.com/problems/shortest-unsorted-continuous-subarray/)