[toc]

# Leetcode 1312. 让字符串成为回文串的最少插入次数

## 问题描述

[1312. 让字符串成为回文串的最少插入次数 - 力扣（LeetCode）](https://leetcode-cn.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/)

## 算法

### 解法1: 递归

#### 解法1: 实现1: 

##### 解法1: 实现1: python

```
class Solution:
    def minInsertions(self, s: str) -> int:
        if len(s) <= 1:
            return 0
        if s[0] == s[len(s)-1]:
            return self.minInsertions(s[1:len(s)-1])
        else:
            return 1 + min(self.minInsertions(s[1:]), self.minInsertions(s[:len(s)-1]))
```

#### 解法1: 实现2:

##### 解法1: 实现2: python

```
class Solution:
    def minInsertions(self, s: str) -> int:

        def minInsertionsRange(i, j): # [i, j)
            if j - i <= 1:
                return 0
            if s[i] == s[j-1]:
                return minInsertionsRange(i+1, j-1)
            else:
                return 1 + min(minInsertionsRange(i+1, j), minInsertionsRange(i, j-1))

        return minInsertionsRange(0, len(s))
```

#### 解法1: 实现3: 记忆化

```
class Solution:
    def minInsertions(self, s: str) -> int:
        
        memo = {}
        def minInsertionsRange(i, j): # [i, j)
            if j - i <= 1:
                return 0
            if (i, j) not in memo:
                if s[i] == s[j-1]:
                    memo[(i, j)] = minInsertionsRange(i+1, j-1)
                else:
                    memo[(i, j)] = 1 + min(minInsertionsRange(i+1, j), minInsertionsRange(i, j-1))
            return memo[(i,j)]

        return minInsertionsRange(0, len(s))
```

### 解法2: dp

可以将上面的记忆化直接修改为 dp，注意需要沿着对角线方向更新参数

#### 解法2: 实现1


##### 解法2: 实现1: python

```
class Solution:
    def minInsertions(self, s: str) -> int:
        n = len(s)
        dp = [[0] * (n+1) for i in range(n+1)]
        for k in range(1, n+1):
            for i in range(n-k+1): # j = i + k && j <= n --> i + k <= n --> i <= n - k
                j = i + k
                if s[i] == s[j-1]:
                    dp[i][j] = dp[i+1][j-1]
                else:
                    dp[i][j] = 1 + min(dp[i+1][j], dp[i][j-1])
        return dp[0][n]
```

### 解法3: dp-2


参考 [ 1 ]

本题属于[516. 最长回文子序列](https://leetcode-cn.com/problems/longest-palindromic-subsequence/)的子题，求的就是**不为最长回文子序列的字符个数，所以我们只需要用字符串长度减去最长回文子序列的长度就是最少插入次数了**

# References
1. [C++：动态规划（新瓶装旧酒） - 让字符串成为回文串的最少插入次数 - 力扣（LeetCode）](https://leetcode-cn.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/solution/cdong-tai-gui-hua-xin-ping-zhuang-jiu-jiu-by-xiaon/)