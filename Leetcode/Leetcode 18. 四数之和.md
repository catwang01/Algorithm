[toc]

# Leetcode 18. 四数之和

## 问题描述

[18. 四数之和 - 力扣（LeetCode）](https://leetcode-cn.com/problems/4sum/)

## 算法

### 解法1: 排序 + 双指针

实际上解法和 三数之和相同，只不过多了一层循环而已。

1. 先对数据进行排序。
2. 先固定最小的两个数 nums[i] 和 nums[j]，问题转化为在 nums[j+1:] 中寻找两数之和为 `target - nums[i] - nums[j]` 的数
3. 每个可能的解有四个数，从小到大依次排列。我们规定：每次下标在 +1 或 -1 时都寻找下一个和自己不等的数，这样可以保证相同的解不会出现。我们把这个逻辑抽象为 `get_next_bigger()` 和 `get_next_smaller()` 两个函数。

时间复杂度： $O(n^3)$

##### 解法1: 实现：python

```
class Solution:
    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:
        ret = []
        n = len(nums)
        if n < 4: return ret

        nums.sort()
        
        def get_next_bigger(i, right):
            while i + 1 < right and nums[i] == nums[i+1]:
                i += 1
            # nums[i] < nums[i+1] 
            i += 1
            return i
        
        def get_next_small(left, j):
            while left < j - 1 and nums[j] == nums[j-1]:
                j -= 1
            # nums[j-1] < nums[j] 
            j -= 1
            return j

        def twoSum(k, target): # find three sum equals targe in nums[k:]
            nonlocal n, nums
            left, right = k, n - 1
            while left < right:
                # print(left, right)
                if nums[left] + nums[right] == target:
                    ret.append([nums[i], nums[j], nums[left], nums[right]])
                    left = get_next_bigger(left, right)
                elif nums[left] + nums[right] > target:
                    right = get_next_small(left, right)
                else:
                    left = get_next_bigger(left, right)

        i = 0
        while i < n:
            j = i + 1
            while j < n:
                # print("i: {} j: {}".format(i, j))
                twoSum(j+1, target - nums[i] - nums[j])
                j = get_next_bigger(j, n)
            i = get_next_bigger(i, n)
            
        return ret
```

### 解法2: 回溯法

##### 解法2: 实现：python

```
class Solution:
    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:
        nums.sort()
        
        ret = []

        def dfs(i, path):
            # 如果剩下的元素都选上都凑不够 4 个 
            if len(nums) - i < 4 - len(path): 
                return
            if len(path) == 3:
                j = self.bisearch(nums, i, len(nums), target - nums[path[0]] - nums[path[1]] - nums[path[2]])
                if j != -1:
                    ret.append([nums[idx] for idx in path + [j]])
                return
            # 不选
            k = i
            while k < len(nums) and nums[k] == nums[i]:
                k += 1
            if len(nums) - k >= 4 - len(path): # 如果剩下的元素都选上都凑不够 4 个 
                dfs(k, path)

            # 选
            path.append(i)
            dfs(i+1, path)
            path.pop()

        dfs(0, [])
        return ret
    
    def bisearch(self, nums, low, high, target):
        if target > nums[high-1] or target < nums[low]: return -1
        while high - low > 2:
            mid = (low + high) // 2
            if nums[mid] == target:
                return mid
            elif nums[mid] > target:
                high = mid
            else:
                low = mid + 1
        if nums[high-1] == target:
            return high-1
        if nums[low] == target:
            return low
        return -1
```
