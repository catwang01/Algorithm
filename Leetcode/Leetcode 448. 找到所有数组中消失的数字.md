[toc]

# Leetcode 448. 找到所有数组中消失的数字

## 问题描述

[448. 找到所有数组中消失的数字 - 力扣（LeetCode）](https://leetcode-cn.com/problems/find-all-numbers-disappeared-in-an-array/)

给定一个范围在  1 ≤ a[i] ≤ n ( n = 数组大小 ) 的 整型数组，数组中的元素一些出现了两次，另一些只出现一次。

找到所有在 [1, n] 范围之间没有出现在数组中的数字。

您能在不使用额外空间且时间复杂度为O(n)的情况下完成这个任务吗? 你可以假定返回的数组不算在额外空间内。

示例:
输入:
[4,3,2,7,8,2,3,1]
输出:
[5,6]

## 算法

### 解法1：原地 hash

思路和 [442. 数组中重复的数据 - 力扣（LeetCode）](https://leetcode-cn.com/problems/find-all-duplicates-in-an-array/) 相同。

##### 解法1：实现：c++

```
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> result;
        for (int i=0; i<nums.size(); i++) {
            while (nums[i] != nums[nums[i]-1]) {
                swap(nums[i], nums[nums[i]-1]);
            }
        }
        for (int i=0; i<nums.size(); i++) {
            if (i != nums[i]-1) {
                result.push_back(i+1);
            }
        }
        return result;
    }
};
```

##### 解法1：实现：python

```
class Solution:
    def findDisappearedNumbers(self, nums: List[int]) -> List[int]:

        def swap(i, j):
            nums[i], nums[j] = nums[j], nums[i]

        def isCorrectSettled(idx): # idx 位置是否被正确放置
            return nums[idx] == idx + 1
        n = len(nums)

        for i in range(n):
            while not isCorrectSettled(nums[i]-1):
                swap(i, nums[i]-1)

        ret = []
        for i in range(n):
            if nums[i] != i + 1:
                ret.append(i + 1)
        return ret
```
