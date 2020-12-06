[toc]

# Leetcode 518. 零钱兑换 II

## 问题描述

[518. 零钱兑换 II](https://leetcode-cn.com/problems/coin-change-2/)

给定不同面额的硬币和一个总金额。写出函数来计算可以凑成总金额的硬币组合数。假设每一种面额的硬币有无限个。 

示例 1:
输入: amount = 5, coins = [1, 2, 5]
输出: 4
解释: 有四种方式可以凑成总金额:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1

示例 2:
输入: amount = 3, coins = [2]
输出: 0
解释: 只用面额2的硬币不能凑成总金额3。

示例 3:
输入: amount = 10, coins = [10] 
输出: 1
 
注意:
你可以假设：
0 <= amount (总金额) <= 5000
1 <= coin (硬币面额) <= 5000
硬币种类不超过 500 种
结果符合 32 位符号整数


## 算法

这个就是所谓对完全背包问题。

### 解法一：动态规划一

记 $dp[i][j]$ 为使用前 i 个硬币凑成金额 j 的种类数。根据使用 $coins[i]$ 的个数来分类：

1. 使用0个 $coins[i]$ 的有 $dp[i-1][j]$个
2. 使用1个 $coins[i]$ 的有 $dp[i-1][j-coins[i]]$个
3. 使用2个 $coins[i]$ 的有 $dp[i-1][j-2*coins[i]]$个
4. ...

则转移方程为

$$
\begin{aligned}
dp[i][j] =& dp[i-1][j] + dp[i-1][j-coins[i]] \\
& + dp[i-1][j-2*coins[i]] \\
& + dp[i-1][j-3*coins[i]] \\ 
& + \cdots + dp[i-1][j-k*coins[i]]
\end{aligned}
$$

其中 k 是满足 $j - k*coins[i] \ge 0$ 最小的k

时间复杂度： $O(n*(amount+1)^2)$ 最坏情况下当面值为1时，k需要循环 amount+1 次
空间复杂度： $O(n * (amount+1))$

#### 解法一python

注意这里的边界情况 $dp[0][j]$ 设置为1，这样可以简化递推公式

超时。

```
class Solution:
    def change(self, amount: int, coins: List[int]) -> int:
        n = len(coins)
        if n ==0: return 1 if amount==0 else 0
        dp = [[0] * (amount+1) for _ in range(n)]
        # 边界情况设置为1 可以简化递推公式 
        for i in range(n):
            dp[i][0] = 1
        for j in range(1, amount+1):
            if j % coins[0] == 0:
                dp[0][j] = 1 
        for i in range(1, n):
            for j in range(1, amount+1):
                for k in range(j // coins[i] + 1):
                    dp[i][j] += dp[i-1][j - k*coins[i]]
        return dp[n-1][amount]
```

#### 解法一c++

```
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        // 特判
        if (n==0) {
            if (amount==0) 
                return 1;
            else 
                return 0;
        }
        vector<vector<int> > dp(n, vector<int>(amount+1, 0));
        for (int i=0; i<n; i++) {
            dp[i][0] = 1;
        }
        for (int j=1; j<amount+1; j++) {
            if (j % coins[0]==0) dp[0][j] = 1;
        }
        for (int i=1; i<n; i++) {
            for (int j=1; j<amount+1; j++) {
                for (int k=0; k <= j / coins[i]; k++) {
                    dp[i][j] += dp[i-1][j - k * coins[i]];
                }
            }
        }
        return dp[n-1][amount];
    }
};
```

### 解法2: 另一种转移方程

#### 解法2: 实现：递归

##### 解法2: 实现：python

```
class Solution:
    def change(self, amount: int, coins: List[int]) -> int:
        if amount == 0: return 1
        memo = {}
        def helper(s, i):
            if i < 0 or s < 0:
                return 0
            if s == 0:
                return 1
            if (s, i) not in memo:
                memo[(s,i)] = helper(s - coins[i], i) + helper(s, i-1)
            return memo[(s, i)]

        return helper(amount, len(coins)-1)
```

### 解法3: 解法2 修改为 dp

#### 解法3: 实现1

可以改变一种看法，得到新的转移方程。

可以考虑是否包含第 i 个硬币，

1. 不包含第 i 个硬币，有 dp[i-1][j] 种组合
2. 包含第 i 个硬币，有 dp[i][j-coins[i]] 种组合，因此转移方程为 

$$dp[i][j] = dp[i-1][j] + dp[i][j-coins[i]]$$

##### 解法3: 实现1: python

```
class Solution:
    def change(self, amount: int, coins: List[int]) -> int:
        n = len(coins)
        # 特判
        if n==0: return 1 if amount ==0 else 0
        dp = [[None] * (amount+1) for _ in range(n)]
        # 第一列全为1
        for i in range(n):
            dp[i][0] = 1
            
        # 第二列根据是否能够整除来判断
        for j in range(1, amount+1):
            dp[0][j] = 1 if j % coins[0] == 0 else 0

        for i in range(1, n):
            for j in range(1, amount+1):
                dp[i][j] = dp[i-1][j] + dp[i][j-coins[i]] if j>=coins[i] else dp[i-1][j]
        return dp[n-1][amount]
        
```

### 解法4: 解法3状态优化

#### 解法4: 实现

##### 解法4: 实现1: python

```
class Solution:
    def change(self, amount: int, coins: List[int]) -> int:
        n = len(coins)
        if n==0: return 1 if amount ==0 else 0
        dp = [0] * (amount+1)
        dp[0] = 1
        for i in range(n):
            for j in range(1, amount+1):
                if j>=coins[i]:
                    dp[j] += dp[j-coins[i]]
        return dp[amount]
```

# References
- [动态规划 - 零钱兑换 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/coin-change-2/solution/dong-tai-gui-hua-wan-quan-bei-bao-wen-ti-by-liweiw/)
