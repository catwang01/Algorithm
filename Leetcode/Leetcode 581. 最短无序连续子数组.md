
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

### 解法1： 排序法

对 nums 进行排序，得到一个新的数组 nums_sorted，然后从左边依次比较 nums 和 nums_sorted 对应项是否相当，如果不相等，则得到了最短无序连续子数组的左边界。

同理从右边开始依次比较可以得到右边界。

时间复杂度：$O(nlogn)$
空间复杂度：$O(n)$

##### 解法1: 实现：python

```
class Solution:
    def findUnsortedSubarray(self, nums: List[int]) -> int:
        if len(nums) == 1: return 0
        
        nums_sorted = sorted(nums)
        for i in range(len(nums)):
            if nums[i] != nums_sorted[i]:
                break
        left = i

        for j in range(len(nums)-1, -1, -1):
            if nums[j] != nums_sorted[j]:
                break
        right = j
        return max(j - i + 1, 0)
```

### 解法2：

保存最大最小值。考虑有序数列的性质。如果 x1, ..., xn 是有序的，那么 x1 一定是 x1, x2, .., xn 中的最小值。同理，如果 x2,...,xn 是有序的，那么饿 x2 一定是 x2, ..., xn 中的最小值。

相当于，我们每次遍历 nums[i]，然后查看 nums[i] 是否是 nums[i:] 的最小值，如果不是，说明 i 是最短无序连续子数组的左边界。

因此可以得到下面的伪代码

```
for i in range(len(nums)):
    if nums[i] != min(nums[i:]):
        break
left = i
```

上面每次循环都有 min 操作，是 $O(n)$ 复杂度，因此这个循环是 $O(n^2)$ 复杂度。

我们可以通过提前计算好 min 来减少计算复杂度。

假设我们用来保存 min 的数组是 minNums，可以按照下面的方式计算。

```
minNums = [0] * n
minNums[0] = nums[0]
for i in range(1, len(nums)):
    minNums[i] = min(minNums[i-1], nums[i])
```

注意，我们的 minNums[i] 表示 nums[i:] 的最小值，因此需要按照从 n-1 到 0 的顺序倒着算。
 

```
class Solution:
    def findUnsortedSubarray(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 1: return 0
        minNums = [0] * n
        minNums[n-1] = nums[n-1]
        for i in range(n-2, -1, -1):
            minNums[i] = min(minNums[i+1], nums[i])
        for i in range(n):
            if nums[i] != minNums[i]:
                break
        left = i

        maxNums = [0] * n
        maxNums[0] = nums[0]
        for i in range(1, n):
            maxNums[i] = max(maxNums[i-1], nums[i])
        for i in range(n-1, -1, -1):
            if nums[i] != maxNums[i]:
                break
        right = i
        return max(right - left + 1, 0)
```

### 解法3：单调栈

实际上和解法2 有着类似的思路。解法2 是在说，

```
我们每次遍历 nums[i]，然后查看 nums[i] 是否是 nums[i:] 的最小值，如果不是，说明 i 是最短无序连续子数组的左边界。
```

这实际上是在说，如果 nums[i] 左边还存在比 nums[i] 小的数，那么 i 就可能是一个无序连续子数组的左边界。而如果我们要找最短的无序连续子数组的左边界，那么我们就需要找这样的最小的 i。

#### 解法3: 实现

##### 解法3: 实现：python

```
class Solution:
    def findUnsortedSubarray(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 1: return 0
        st = []
        left = n
        for i in range(n):
            while st and nums[st[-1]] > nums[i]: # 如果右边有小于他的数，就 pop
                left = min(left, st.pop())
            st.append(i)
        
        right = -1
        st = []
        for j in range(n-1, -1, -1):
            while st and nums[st[-1]] < nums[j]: # 如果左边有大于他的数，就 pop
                right = max(right, st.pop())
            st.append(j)
        # print(left, right)
        return max(right - left + 1, 0)
```