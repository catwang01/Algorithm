[toc]

# Leetcode 15. 三数之和

## 问题描述

[15. 三数之和 - 力扣（LeetCode）](https://leetcode-cn.com/problems/3sum/)

给定一个包含 n 个整数的数组 `nums`，判断 `nums` 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？找出所有满足条件且不重复的三元组。
注意：答案中不可以包含重复的三元组。
示例：
给定数组 nums = [-1, 0, 1, 2, -1, -4]，
满足要求的三元组集合为：

```
[
  [-1, 0, 1],
  [-1, -1, 2]
]
```

## 算法

### 解法一：双指针

#### 解法一python

```
class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        n = len(nums)
        if n <= 2: return []
        ret = []
        nums.sort()
        i = 0
        while i < n - 2:
            j = i + 1
            k = n - 1
            while j < k:
                s = nums[i] + nums[j] + nums[k]
                if s <= 0:
                    if s == 0:
                        ret.append([nums[i], nums[j], nums[k]])
                    while j+1 < k and nums[j] == nums[j+1]:
                        j += 1
                    j += 1
                else:
                    while j < k-1 and nums[k] == nums[k-1]:
                        k -= 1
                    k -= 1

            # i 在更新的时候要选择下一个不同的值
            while i + 1 < n and nums[i] == nums[i+1]:
                i += 1
            # 此时 i + 1 == n or nums[i] != nums[i+1]
            i += 1
            
        return ret
```
