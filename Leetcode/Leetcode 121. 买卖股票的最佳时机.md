
[toc]

# Leetcode 121. 买卖股票的最佳时机

## 问题描述

[121. 买卖股票的最佳时机 - 力扣（LeetCode）](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/submissions/)

给定一个数组，它的第 *i* 个元素是一支给定股票第 *i* 天的价格。

如果你最多只允许完成一笔交易（即买入和卖出一支股票），设计一个算法来计算你所能获取的最大利润。

注意你不能在买入股票前卖出股票。

**示例 1:**

**输入:** [7,1,5,3,6,4]
**输出:** 5
**解释:** 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格。

**示例 2:**

**输入:** [7,6,4,3,1]
**输出:** 0
**解释:** 在这种情况下, 没有交易完成, 所以最大利润为 0。


## 算法

### 解法一：bruteforce

时间复杂度：$O(n^2)$
空间复杂度： $O(1)$

#### 解法一python

```
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)
        profit = 0
        for i in range(n-1):
            if max(prices[i+1:]) > prices[i]: # 注意这里max的时间复杂度为 O(n-i+1)
                profit = max(profit, max(prices[i+1:]) - prices[i])
        return profit
```

### 解法二：解法一优化

上面的解法一，其中重复运算的部分是在求最大值时，求 prices[i+1:] 的最大值 和 求 prices[i:] 的最大值有很大的重叠。

因此可以考虑先求 prices[i+1:] 的最大值，再求 prices[i:] 的最大值，只需要 prices[i] = max(prices[i], max(prices[i+1:]))，可以减少重复计算； 这实际是动态规则的思想

因此，需要一个变量 max_price 来维护最大值 

时间复杂度： $O(n)$
空间复杂度： $O(1)$

#### 解法二python

```
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)
        if n <= 1: return 0
        profit = 0
        max_price = prices[n-1]
        for i in range(n-2, -1, -1): #[n-2,...,0]
            profit = max(profit, max_price - prices[i])
            max_price = max(max_price, prices[i]) # 更新最大值
        return profit
```

这个实际上是动态规划的思想，写成更明显的dp的形式为

```
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)
        if n <= 1: return 0
        # dp[i] 表示 max(prices[i+1:])
        dp = [None] * n
        dp[-1] = prices[-1] 
        for i in range(n-2, -1, -1): # [n-2, 0]
            dp[i] = max(prices[i], dp[i+1])
        # 利用dp数组计算最大的profit，下面这个循环可以合并到上面的循环中
        profit = 0
        for i in range(n-1): # [0,...,n-2]
            profit = max(profit,dp[i]-prices[i])
        return profit
```

### 解法三：利用最大子序和（这个代码不通用）

计 

$$diff[i] = prices[i+1] - prices[i]$$

要计算的是 $max(prices[j] - prices[i])$，相当于求 

$$max(prices[j] - prices[i]) = max(diff[i] + ... + diff[j-1])$$


#### 解法三c++

```
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n<=1) return 0;
        int diff[n-1];
        for (int i=0; i<n-1; i++) {
            diff[i] = prices[i+1]-prices[i];
        }
        int dp = diff[0], profit = diff[0];
        for (int i=1; i<n-1; i++) {
            dp = max(diff[i]+dp, diff[i]);
            profit = max(profit, dp);
        }
        return max(profit, 0);
    }
};
```

### 解法四：三维dp


#### 为什么要用三维dp，二维dp不可吗？

决策过程可以使用下面的多段图表示

![df05e71bda544e41720c700359843ee5.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p10964)

因此，可以考虑使用 `dp[i][j]` 来表示状态。其中 

i = 0, 1，0表示当天手中不持有股票。1表示当天手中持有股票。
j 表示天数。

可是，这样有一个问题。 dp[0][j] 表示第 j 天不持有股票。有两种可能
1. 前 j-1 天里已经完成过一次交易，因此第j天只有一种选择：不买入股票。

2. 前 j-1 天里没有完成过交易，因此第 j 天有两种选择：买入股票或者不买入股票

因此可以看到，第 j 天可以做的选择，是和之前的状态有关系的。因此不具备无后效性！

为了消除无后效性，可以多添加一个状态，来区别上面的两种不同。添加一个状态 k 来表示剩余的交易次数。这道题目要求至多一次交易，因此 k = 0 or 1。

dp[i][j][k] 的意义如下：

![ce0ca69d2599c666872ff734e4f7aec5.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p10965)

#### 转移方程

![fe8721513917c5aafba06fbd6facdf7a.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p10966)

#### 返回值

这个问题有一个小坑，就是要返回 `max(dp[0][n][0], dp[0][n][1])`，不是 `dp[0][n][0]`。因为题目要求至多一次交易，当然可以不进行交易。 `dp[0][n][1]` 表示的就是不进行交易时的最大利润（当然是0）。

因为的确有例子，使得只要进行交易就会亏钱。

#### 复杂度分析

时间复杂度： $O(4n)=O(n)$
空间复杂度： $O(4n)=O(n)$

#### 解法4：实现

##### 解法4

```
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)
        if n <= 1: return 0
        dp = [[[0,0] for i in range(2)] for _ in range(n)]
        dp[0][0][0] = -float('inf')
        dp[0][0][1] = -prices[0]
        dp[0][1][0] = -float("inf")
        dp[0][1][1] = 0
        
        for i in range(1, n):
            dp[i][0][1] = max(dp[i-1][0][1], dp[i-1][1][1] - prices[i])
            dp[i][0][0] = max(dp[i-1][0][0], dp[i-1][0][1] + prices[i])
            # dp[i][1][0] 不可能，不算它了 
            dp[i][1][1] = dp[i-1][1][1]
        return max(dp[n-1][0][0], dp[n-1][1][1])
```

##### 解法4：c++


```
class Solution {
public:
    int inf=99999;
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int> > > dp(2, vector<vector<int>>(n+1, vector<int>(2, -inf)));
        dp[0][0][1] = 0;
        for (int j=1; j<n+1; j++) {
            // 里面逻辑上是对第1、2个下标循环，由于它们的维度都是2比较小，因此直接列举出来了
            dp[0][j][0] = max(dp[0][j-1][0], dp[1][j-1][0] + prices[j-1]);
            dp[0][j][1] = dp[0][j-1][1];
            dp[1][j][0] = max(dp[1][j-1][0], dp[0][j-1][1] - prices[j-1]);
        }
        return max(dp[0][n][0], dp[0][n][1]);
    }
};
```

### 解法四：三维dp空间优化

时间复杂度：$O(n)$
空间复杂度： $O(1)$

变量依赖图
![f5d1b18d129de1de2fc8af9ec1cd2097.png](evernotecid://7C71FA3B-B5E0-41C4-AF1B-AB35446A037A/appyinxiangcom/22483756/ENResource/p12006)

箭头 A -> B 表示 A 的更新依赖于 B 的值。从图中可以看出。更新顺序应该是 dp00，dp10，dp01。

不然，如果先更新 dp10的话，由于 dp00 的更新依赖于 dp10 的值，更准确的说，依赖于 dp10 的旧值。而先更新 dp10 会将 dp10 的旧值覆盖，因此会产生错误。


#### 解法四空间优化：实现

##### 解法四空间优化：c++

```
class Solution {
public:
    int inf=99999;
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int dp00=-inf, dp01 = 0, dp10=-inf;
        for (int j=1; j<n+1; j++) {
            dp00 = max(dp00, dp10 + prices[j-1]);
            dp10 = max(dp10, dp01 - prices[j-1]);
            // 去掉dp01 = dp01;
        }
        return max(dp00, dp01);
    }
};
```
