[toc]


# Leetcode 91. 解码方法

## 问题描述

[91. 解码方法 - 力扣（LeetCode）](https://leetcode-cn.com/problems/decode-ways/)

## 算法

### 解法1

#### 解法1:

```
class Solution:
    def numDecodings(self, s: str) -> int:
        n = len(s)
        if n == 0: return 0
        dp = [0] * n
        if s[0] != '0': dp[0] = 1

        for i in range(1, n):
            if s[i] != '0':
                dp[i] += dp[i-1]
            if 10 <= int(s[i-1: i+1]) <= 26: # 这种写法排除了 s[i-1] = '0' 的可能性
                                            # 如果 s[i-1] == '0' 那么 0 <= int(s[i-1:i+1]) <= 9
                if i - 2 >= 0:
                    dp[i] += dp[i-2] 
                else:
                    dp[i] += 1
        return dp[n-1]
```