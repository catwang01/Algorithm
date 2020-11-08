
[toc]

# Leetcode 198. 打家劫舍 

## 问题描述

[198. 打家劫舍 - 力扣（LeetCode）](https://leetcode-cn.com/problems/house-robber/submissions/)

### 解法一：dp1

dp[i] 定义为以 nums[i] 为结尾的偷盗序列中可以得到的最高金额，则

```
dp[i] = max(nums[i] + dp[j]) 对于 j <= i - 2
```

由于我们规定 dp[i] 只能以 nums[i] 结尾，那么 nums[i-1] 就不能偷，剩下的就在 dp[j], j <= i- 2 中选一个最大的就可以。

```
```

### 解法2: dp1 优化

上面的转移方程可以优化。注意到，dp 数组有一定的单调性
1. dp[i-2] 一定不小于 dp[i-4] 因为 dp[i-2] 可以取到 dp[i-4] + nums[i-2], 同理有 

```
dp[i-2] <= dp[i-4] <= dp[i-6] <= dp[i-8] <= ...，
```

2. 同样的，有

```
dp[i-3] <= dp[i-5] <= dp[i-7] <= dp[i-9] <= ...
```

因此，我们在计算 dp[i] 时不需要遍历 j <= i-2，只需考虑 j=i-2 和 j=i-3 的情况就好了

优化后的转移方程为（当然还要考虑越界的问题，这里为了简单省略掉了）

```
dp[i] = nums[i] + max(dp[i-2], dp[i-3])
```

这样可以将时间复杂度降低到 $O(n^2)$

##### 解法2: 实现：python

```
class Solution:
    def rob(self, nums: List[int]) -> int:
        # dp[i] 偷了以 i 结尾的得到的最高金额
        if len(nums) == 0: return 0
        dp = [0] * len(nums)
        ret = nums[0]
        for i in range(0, len(nums)):
            if i - 3 >= 0:
                dp[i] = nums[i] + max(dp[i-2], dp[i-3])
            elif i - 2 >= 0:
                dp[i] = nums[i] + dp[i-2]
            else:
                dp[i] = nums[i]
            ret = max(ret, dp[i])
        return ret
```

### 解法3：dp2 第二种dp数组定义

dp[i] 定义为第 i 天偷完之后得到的最高金额。（注意，这个定义和上一种方法中对 dp 的定义截然不同）

我们考虑 nums[i] 到底偷不偷

1. 偷，那么我们的金额增加 nums[i]，同时为了不触发警报，我们不能偷 nums[i-1]，因此，问题转化为在 nums[0], ..., nums[i-2] 中我们怎么偷才能得到最高金额的问题，即 dp[i-2]

2. 不偷，如果我们不偷，那么问题转化为 在 nums[0], ..., nums[i-1] 中我们怎么偷才能得到最高金额的问题，即 dp[i-1]

因此，我们可以得到下面的转移方程

```
dp[i] = max(dp[i-2] + nums[i], # 偷 nums[i]
            dp[i-1])    # 不偷 nums[i]
```

时间复杂度： $O(n)$
空间复杂度： $O(n)$

##### 解法3: 实现：python

```
class Solution:
    def rob(self, nums: List[int]) -> int:
        # dp[i] 偷了以 i 结尾的得到的最高金额
        if len(nums) == 0: return 0
        dp = [0] * len(nums)
        dp[0] = nums[0]
        for i in range(1, len(nums)):
            dp[i] = max(dp[i-1], dp[i-2] + nums[i])
        return dp[len(nums) - 1]
```

### 解法4： dp2空间优化

由于只用到了 dp[i-1] 和 dp[i-2]， 因此可以使用两个变量dp0 和 dp1 来保存这两个中间结果

时间复杂度：$O(n)$
空间复杂度：$O(1)$

##### 解法4: 实现：python

```
class Solution:
    def rob(self, nums: List[int]) -> int:
        n = len(nums)
        if n==0: return 0
        if n==1: return nums[0] 
        dp0, dp1 = nums[0], max(nums[0], nums[1])
        for i in range(2, n):
            dp0, dp1 = dp1,  max(nums[i]+dp0, dp1)
        return dp1
```
