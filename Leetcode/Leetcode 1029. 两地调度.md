[toc]


# Leetcode 1029. 两地调度

## 问题描述

[1029. 两地调度 - 力扣（LeetCode）](https://leetcode-cn.com/problems/two-city-scheduling/)

## 算法

### 解法1: 贪心

假设先将所有人都安排到 A 地面试，然后调其中 n 个人让他们去 b 地面试，此时由于去 A、B 两地的花销不同，会导致花销增加 `costs[i][1] - costs[i][0]`（注意，虽然这里用的是“增加”这个表达，但是，`costs[i][1] - costs[i][0]` 可能是负数）

我们值需要选择 N 个使增加最少的人就可以了，相当于贪心算法贪 `costs[i][1] - costs[i][0]` ，只需要排序然后选择前 n 个数就可以。

[ 1 ] 给了贪心法的数学论证。

#### 解法1: 实现1:排序

时间复杂度：$O(nlogn)$
空间复杂度：$O(n)$

##### 解法1: 实现1: python

```
class Solution:
    def twoCitySchedCost(self, costs: List[List[int]]) -> int:
        n = len(costs) // 2
        totalCost = sum(cost_a for cost_a, _ in costs)
        diff = [cost_b - cost_a for cost_a, cost_b in costs]
        diff.sort()
        totalCost += sum(diff[:n])
        return totalCost
```

#### 解法1: 实现2: 快速选择

由于我们只需要知道最小的 n 个元素，不需要知道这 n 个元素的排序，因此可以使用快速选择。

时间复杂度： $O(n)$
空间复杂度：$O(n)$

##### 解法1: 实现1: python

```
class Solution:
    def twoCitySchedCost(self, costs: List[List[int]]) -> int:
        n = len(costs) // 2
        totalCost = sum(cost_a for cost_a, _ in costs)
        diff = [cost_b - cost_a for cost_a, cost_b in costs]
        self.quickSelect(diff, 0, n * 2, n)
        totalCost += sum(diff[:n])
        return totalCost

    def quickSelect(self, A, low, high, k):
        if high - low <= 1: 
            return
        i = j = low
        pivotIdx = random.randint(low, high-1)
        A[pivotIdx], A[high-1] = A[high-1], A[pivotIdx]
        pivot = A[high-1]
        # [low, i) --> 小于等于 pivot
        # [i, j) 大于 pivot
        # [j, high) 未处理
        while j < high:
            if A[j] <= pivot:
                A[i], A[j] = A[j], A[i]
                i += 1
            j += 1
        # A[i-1] 是 pivot，A[i-1] 左边有 i-1 元素
        if i - 1 == k - 1:   # 如果 A[i-1] 左边有 k - 1 个元素，说明 A[i-1] 是第 k 个元素
            return 
        elif i - 1 < k - 1: # 如果 A[i-1] 左边小于 k - 1 个元素，说明第 k 个元素在 A[i-1] 右边（[i, high)
            self.quickSelect(A, i, high, k)
        else: # 说明第 k 个元素在 A[i-1] 左边 [low, i-1)
            self.quickSelect(A, low, i-1, k)
```

# References
1. [两地调度之优化算法 - 两地调度 - 力扣（LeetCode）](https://leetcode-cn.com/problems/two-city-scheduling/solution/liang-di-diao-du-zhi-you-hua-suan-fa-by-yi-di-ji-m/)