[toc]

# Leetcode 309. 最佳买卖股票时机含冷冻期 

[309. 最佳买卖股票时机含冷冻期 - 力扣（LeetCode）](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/)

## 问题描述

## 算法

### 解法一：动态规划

股票问题，最关键的是如何设置状态和进行转移。

根据题目，可以用一个二值变量状态来标记当前是否持有股票，0表示没有持有，1表示持有。还需要一个状态来标记当前是否在冻结期，0表示在冻结期，1表示不在冻结期。我们可以用一个二维数组来表示上面的两个状态，如 (1,0) 表示当前持有股票且不在冻结期。

由此可以得到下面的转移关系图

![](https://gitee.com/EdwardElric_1683260718/picture_bed/raw/master/img/20200710101009.png)


#### 解法一：实现

##### 解法1: c++

```
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // 0 不持有 1 持有
        // 0 不在冻结期 1 在冻结期
        int n = prices.size();
        if (n<=1) return 0;
        vector<vector<vector<int>>> dp(n, vector<vector<int>> (2, vector<int>(2)));
        dp[0][0][0] = 0, dp[0][0][1] = INT_MIN, dp[0][1][0] = -prices[0];
        for (int i=1; i<n; i++)
        {
            dp[i][0][0] = max(dp[i-1][0][0], dp[i-1][0][1]);
            dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][0][0]-prices[i]);
            dp[i][0][1] = dp[i-1][1][0] + prices[i];
            // dp[i][1][1] 不可能存在，不参与计算
        }
        return max(dp[n-1][0][0], dp[n-1][0][1]);
    }
};
```

### 解法1：空间优化

上面的解法中，我们用两个0-1标志位来分别表示是否持有股票和是否在冻结期，我们也看到了，(1,1) 这种状态是不可能出现的。也就是说，我们多表示了一个状态，实际上，我们只需要表示下面三种状态即可
1. 不持有股票、不在冻结期，即上面的 (0, 0)
2. 不持有股票、在冻结期，即上面的 (0,1)
3. 持有股票、不在冻结期，即上面的 (1,0)

因此，我们可以不使用两个 0-1 标志位，而是使用 0，1，2 三个数来分别表示这三位。

其中
1. 0 表示 不持有股票、不在冻结期，即上面的 (0, 0)
2. 1 表示持有股票、不在冻结期，即上面的 (1,0)
3. 2 表示 不持有股票、在冻结期，即上面的 (0,1)

由此，我们的代码可以修改为

```
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n<=1) return 0;
        vector<vector<int>> dp(n, vector<int>(3));
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        dp[0][2] = INT_MIN;
        for (int i=1; i<n; i++) {
            dp[i][0] = max(dp[i-1][0], dp[i-1][2]);
            dp[i][1] = max(dp[i-1][0]-prices[i], dp[i-1][1]);
            dp[i][2] = dp[i-1][1] + prices[i];
        }
        return max(dp[i][0], dp[i][2])
    }
};
```

### 解法一：空间优化2

可以看到，dp[i][k] k=0,1,2 的计算只需要 dp[i-1][k] 的值，因此可以使用三个变量 dp0, dp1, dp2 来代替dp数组；

三个变量之间的依赖关系如下图

![](https://gitee.com/EdwardElric_1683260718/picture_bed/raw/master/img/20200710102447.png)


可以看到，三个变量互相依赖，因此一定需要借助一个中间临时变量来保存中间值；

1. 可以先更新 dp0，它依赖于自身和dp2；而 dp1 更新依赖于 dp0 的值，因此需要在更新 dp0 之前保存它的值，保存在 tmp中；
2. 再更新 dp2，因为 dp2 的更新依赖于 dp1，而如果先更新 dp1 的话就需要再保存 dp1 的值；因此先更新dp2
3. 之后再更新 dp1

上述更新的过程如下

```
tmp = dp0
dp0 = max(dp0, dp2) 
dp2 = dp1 + prices[i]
dp1 = max(tmp-prices[i], dp1)
```

#### 解法一空间优化c++

```
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n<=1) return 0;
        int dp0=0, dp1=-prices[0], dp2 = -9999;
        int tmp;
        for (int i=1; i<n; i++) {
            tmp = dp0;
            dp0 = max(dp0, dp2);
            dp2 = dp1 + prices[i];
            dp1 = max(tmp-prices[i], dp1);
        }
        return max(0, max(dp0, max(dp1, dp2)));
    }
};
```