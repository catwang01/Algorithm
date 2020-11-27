[toc]

# Leetcode 1458. 两个子序列的最大点积

## 问题描述

[1458. 两个子序列的最大点积 - 力扣（LeetCode）](https://leetcode-cn.com/problems/max-dot-product-of-two-subsequences/)

## 算法

### 解法1：dp

考虑使用 dp。

有两种 dp数组设计方式：

1. 
```
dp[i][j] 定义为以 nums1[i-1] 结尾 和以 nums2[j-1] 结尾的子序列的最大内积
```

2. 

```
dp[i][j] 定义为 nums1[:i] 和 nums2[:j] 的最大内积
```

我们使用第二种定义，因为这样写出的时间复杂度比较低。

对于 dp[i][j]，我们考虑 nums1[:i] 和 nums2[:j] 的末尾两个元素，有下面几种情况

1. 不选 nums1[:i]，那么结果为 dp[i-1][j]

2. 不选 nums2[:j] 那么结果为 dp[i][j-1]

3. 两个都不选，那么结果为 dp[i-1][j-1]

也就是说，我们的转移方程为

```
dp[i][j] = max(nums1[i-1] * nums2[j-1] + dp[i-1][j-1], 
                dp[i-1][j], 
                dp[i][j-1])
```

对于 `i==0 or j==0` 即 nums1[:j] or nums2[:j] 为空串的情况，我们设置

```
dp[i][j] = 0
```

由此我们得到了我们的第一版代码。

```
class Solution:
    def maxDotProduct(self, nums1: List[int], nums2: List[int]) -> int:
        n1, n2 = len(nums1), len(nums2)
        dp = [[0] * (n2+1) for i in range(n1+1)]
        for i in range(1, n1+1):
            for j in range(1, n2+1):
                dp[i][j] = max( nums1[i-1] * nums2[j-1] + dp[i-1][j-1], 
                                dp[i][j-1], 
                                dp[i-1][j])
        return dp[n1][n2]
```

这个代码是有 bug 的。因为它不能保证最优结果对应的子序列非空。看下面的示例

```
[1]
[-1]
```

这个示例上面的代码结果为 0。因为它计算了

```
dp[1][1] = max(nums1[0] * nums2[0] + dp[0][0], dp[0][1], dp[1][0]) = max(-1, 0, 0) = 0
```

这里可以看到，我们设计 `i==0 or j==0` 时返回值为0 是错误的。因为有可能最大的内积为负数时返回为0。

我们令 `i==0 or j==0` 是返回值0 `-inf`，表示不能取到空串。但是这样又回带来一个问题：边界值无法计算。

我们这里修改我们的转移方程为

```
dp[i][j] = max( nums[i-1] * nums2[j-1],
                nums1[i-1] * nums2[j-1] + dp[i-1][j-1], 
                dp[i-1][j], 
                dp[i][j-1])
```

这个问题的根本原因是递推是 nums1[:i] 或 nums2[:i] 不是一定可以取空串导致的。

## todo 这个没有说清楚


##### 解法1: 实现：python

```
class Solution:
def maxDotProduct(self, nums1: List[int], nums2: List[int]) -> int:
    n1, n2 = len(nums1), len(nums2)
    dp = [[-float("inf")] * (n2+1) for i in range(n1+1)]
    for i in range(1, n1+1):
        for j in range(1, n2+1):
            dp[i][j] = max( nums1[i-1] * nums2[j-1] + dp[i-1][j-1], 
                            nums1[i-1] * nums2[j-1],
                            dp[i][j-1], 
                            dp[i-1][j])
    return dp[n1][n2]
```

```
