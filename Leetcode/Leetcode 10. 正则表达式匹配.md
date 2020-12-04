[toc]

# Leetcode 10. 正则表达式匹配 

## 问题描述

[10. 正则表达式匹配 - 力扣（LeetCode）](https://leetcode-cn.com/problems/regular-expression-matching/)

## 算法

### 解法1: dp

#### 解法1: 实现

##### 解法1: 实现： python

```
class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        ns, np = len(s), len(p)
        dp = [[False for j in range(np+1)] for i in range(ns+1)]
        
        dp[0][0] = True 
        # i = 0 时仍然有可能匹配
        for j in range(2, np+1, 2):
            dp[0][j] = dp[0][j-2] and p[j-1] == '*'
        # j == 0 and i != 0 ==> false

        def match(i, j):
            return s[i] == p[j] or p[j] == '.'
    
        for i in range(1, ns+1):
            for j in range(1, np+1):
                if match(i-1, j-1):
                    dp[i][j] = dp[i-1][j-1]
                elif p[j-1] == '*':
                    if match(i-1, j-2):
                        dp[i][j] = dp[i][j-2] or dp[i-1][j] or dp[i-1][j-2]
                    else:
                        dp[i][j] = dp[i][j-2]
                else:
                    dp[i][j] = False
        return dp[ns][np]
```
