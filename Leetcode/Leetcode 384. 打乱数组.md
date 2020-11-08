
[toc]

# Leetcode 384. 打乱数组

## 问题描述

[384. 打乱数组 - 力扣（LeetCode）](https://leetcode-cn.com/problems/shuffle-an-array/)

## 算法

### 解法1: RANDOM_IN_PLACE 算法

```
class Solution:

    def __init__(self, nums: List[int]):
        self.nums = nums


    def reset(self) -> List[int]:
        """
        Resets the array to its original configuration and return it.
        """
        return self.nums


    def shuffle(self) -> List[int]:
        """
        Returns a random shuffling of the array.
        """
        nums = self.nums[:]
        for i in range(len(nums)):
            idx = random.randint(i, len(nums)-1)
            nums[i], nums[idx] = nums[idx], nums[i]
        return nums
```