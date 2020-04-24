
[toc]

# Leetcode 343. 整数拆分

## 问题描述

[343. 整数拆分 - 力扣（LeetCode）](https://leetcode-cn.com/problems/integer-break/) 

[面试题14- II. 剪绳子 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/jian-sheng-zi-ii-lcof/)

还有一种贪心的算法，个人觉得比较难想到。因此就不看了。

给定一个正整数 n，将其拆分为至少两个正整数的和，并使这些整数的乘积最大化。 返回你可以获得的最大乘积。

示例 1:

输入: 2
输出: 1
解释: 2 = 1 + 1, 1 × 1 = 1。
示例 2:

输入: 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36。
说明: 你可以假设 n 不小于 2 且不大于 58。

## 算法

### 解法1.1：递归

首先使用递归是自然的。这个问题明显可以用递归解决。

注意：n > 1。说明如果要求一根长度为 n 的绳子的最大乘积，则必须对绳子进行切分。

设 cuttingRote(n) 的表示对一根长度为 n 的绳子，进行切分得到的最大乘积，则在转移时，需要注意，剪去 i 之后，剩下的 n - i 的绳子可以不进行切分。而 cuttingRote(n-i) 返回的是进行切分的最大乘积。因此这部分要特殊考虑，否则会出错。

#### 解法1.1: 实现

##### 解法1.1: c++

```
class Solution {
public:
    int integerBreak(int n) {
        if (n==1) return 1;
        vector<int> dp(n+1);
        dp[1] = 1;
        for (int i=2; i<=n; i++) {
            for (int j=1; j<=i-1; j++) {
                dp[i] = max(dp[i], j*max(dp[i-j], i-j));
            }
        }
        return dp[n];
    }
};
```

### 解法1.2：动态规划

设 dp[i] 表示 i 拆分后可以得到的最大乘积。则有下面几种情况

对于 i >= 2，可以有下面的拆分方式：$i = (i-j) + (j) \quad 1 \le j \le i-1$；

**需要注意的是，如果对 i-j 拆分，则其可当作因数 dp[i-j]，如果对 i-j 不拆分，则其可当作因数 i-j； 
如 i-j = 2 时，如果拆分，dp[2] = 1，而如果不对 i-j 以拆分，则可将 i-j =2 整个作为因子**

1. i-j 不拆分，j拆分，有 (i-j) * dp[j]
2. i-j 拆分，j 不拆分 dp[i-j] * j
3. i-j 不拆分，j 不拆分 (i-j) * j
4. i-j 拆分， j 拆分 dp[i-j] * dp[j]

小优化：
由于上面的计算是对称的，i-j 和 i 处于相同的位置，因此j可以取值为 [1, i//2+1]

时间复杂度： $O(n^2)$
空间复杂度： $O(n)$

#### 解法1.2:实现

##### 解法1.2: python

这个用 c++ 会溢出。即使用 long long 也会溢出。所以用 python 比较好

```
class Solution:
    def integerBreak(self, n: int) -> int:
        dp = [0] * (n+1)
        dp[1] = 1
        for i in range(2, n+1):
            for j in range(1, i//2+2):
                dp[i] = max(dp[i], dp[i-j] * dp[j], dp[i-j] * j, (i-j) * dp[j], (i-j) * j)
        return dp[n]
```

### 解法2: 另一种转移方程

对于长度为i的绳子，可以将绳子的前k个单位长度做为一段，再对剩下i-k的进行分割。因此可得到转移方程

```
dp[i] = min(k*dp[i-k]) 1<=k<=i-1
```

上面的方程有bug，不能得到正确的答案。因此剩下的 i-k 长度的绳子还有可能不分割，此时得到的乘积为 k * (i-k)，所以最终的转移方程为 

```
dp[i] = min(k*dp[i-k], k*(i-k)) 1 <= k <= i-1
```

#### 解法2:实现

##### 解法2: python

```
class Solution:
    def cuttingRope(self, n: int) -> int:
        dp = [0] * (n+1)
        dp[1] = 1
        for i in range(2, n+1): # i = [2,...,n]
            for k in range(1, i):
                dp[i] = max(dp[i], dp[i-k] * k, (i-k)*k)
        return dp[n]
```

