
[toc]

# Leetcode 96. 不同的二叉搜索树

## 问题描述

[96. 不同的二叉搜索树 - 力扣（LeetCode）](https://leetcode-cn.com/problems/unique-binary-search-trees/)

## 算法

### 解法一：递归

时间复杂度和空间复杂度不会计算，猜测是 $O(2^n)$ 和 $O(n)$


#### 解法一递归python

```
class Solution:
    def numTrees(self, n: int) -> int:
        if n<=1: return 1
        else:
            counter = 0
            for i in range(n):
                counter += self.numTrees(i) * self.numTrees(n-i-1)
        return counter
```

##### 解法1: c++

```cpp
class Solution {
public:
    unordered_map<int, int> memo;

    int numTrees(int n) {
        if (n<=1) return 1;
        if (memo.find(n) == memo.end())
        {
            for (int i=1; i<=n; i++)
            {
                memo[n] += numTrees(i-1) * numTrees(n-i);
            }
        }
        return memo[n];
    }
};
```

### 解法1: 记忆化

#### 解法1：记忆化：实现

##### 解法1: c++

```cpp
class Solution {
public:
    unordered_map<int, int> memo;

    int numTrees(int n) {
        if (n<=1) return 1;
        if (memo.find(n) == memo.end())
        {
            for (int i=1; i<=n; i++)
            {
                memo[n] += numTrees(i-1) * numTrees(n-i);
            }
        }
        return memo[n];
    }
};
```
### 解法二：dp

将上面的递归算法修改为dp算法

时间复杂度： $O(n^2)$
空间复杂度： $O(n)$

#### 解法2: 实现

##### 解法二: python

```
class Solution:
    def numTrees(self, n: int) -> int:
        if n==1: return n
        dp = [0] * (n+1)
        dp[0] = dp[1] = 1
        for i in range(2,n+1):
            for j in range(i):
                dp[i] += dp[j] * dp[i-j-1]
        return dp[n]
```

##### 解法2: c++


```cpp
class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n+1, 0);
        dp[0] = dp[1] = 1;
        for (int i=2; i<=n; i++)
        {
            for (int j=1; j<=i; j++)
            {
                dp[i] += dp[j-1] * dp[i-j];
            }
        }
        return dp[n];
    }
};
```
