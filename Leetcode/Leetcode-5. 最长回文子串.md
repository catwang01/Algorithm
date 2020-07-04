
[toc]

# Leetcode 5. 最长回文子串

## 问题描述

[5. 最长回文子串 - 力扣（LeetCode）](https://leetcode-cn.com/problems/longest-palindromic-substring/submissions/)

给定一个字符串 `s`，找到 `s` 中最长的回文子串。你可以假设 `s` 的最大长度为 1000。

**示例 1：**
**输入:** "babad"
**输出:** "bab"
**注意:** "aba" 也是一个有效答案。

**示例 2：**
**输入:** "cbbd"
**输出:** "bb"

## 算法

### 解法一：bruteforce

时间复杂度：计算 $i$，$j$ 的组合一共有 $\frac{n(n-1)}{2}$组 即$O(n^2)$，求逆验证的时间为 $O(n)$，故总的时间复杂度为 $O(n^3)$

空间复杂度：$O(1)$ 除了返回的字符串之外没有使用额外的空间

#### 解法一python实现 超时

![52dda8ef924f8f501d8517d109b6145c.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p10586)

```
class Solution:
    def longestPalindrome(self, s: str) -> str:
        # 检查字符串 s[i:j] 是否是回文串
        def check(i,j):
            # 从两边不断向内检查是否相等
            while i < j and s[i]==s[j-1]:
                i += 1
                j -= 1
            return i >= j
                
        n = len(s)
        if n <= 1: return s
        maxLen = 1
        result = s[0]
        for i in range(n):      # i=[0,..,n-1]
            for j in range(i+1, n+1):   # j=[1,...,n]
                if check(i,j) and maxLen < j - i:
                    maxLen = j-i
                    result = s[i:j]
        return result
```

### 解法一：修改为递归并添加缓存

上面的 check 函数每次都要挨个检查字符串是否是回文串，注意到：

对于字符串 `s[i:j]`，若 `s[i] == s[j-1]` 则 s[i:j] 是否是回文串取决于 `s[i+1:j-1]` 是否是回文串。因此可以使用递归，并且使用记忆化来减少重复计算。

#### 解法一：修改为递归并添加缓存python

```
class Solution:
    def longestPalindrome(self, s: str) -> str:

        memo = {}
        def dp(i,j): # s[i:j]是否回文
            if (i,j) not in memo:
                # 空串和单字符是回文
                if j-i<= 1: 
                    memo[(i,j)] = True
                else:
                    memo[(i,j)] = dp(i+1, j-1) if s[i]==s[j-1] else False
            return memo[(i,j)]

        n = len(s)
        if n <= 1: return s
        maxLen = 1
        result = s[0]
        for i in range(n):      # i=[0,..,n-1]
            for j in range(i+1, n+1):   # j=[1,...,n]
                if dp(i,j) and maxLen < j - i:
                    maxLen = j - i 
                    result = s[i:j]
        return result
```

### 解法二：动态规划法

将上面的记忆化递归修改为dp

dp[i][j] 定义为 bool值，表示 `s[i:j]` 是否为回文串，则有两种情况

1. s[i:j] 的两端字母相同，则 dp[i][j] 是否为回文取决于删除两端字母后剩下的字符串是否为回文，即

```
dp[i][j] = dp[i+1][j-1] if s[i]==s[j-1]
```

2. s[i:j] 两端的字母不同，则 dp[i][j] 不可能是回文即

```
dp[i][j] = False    if s[i]!=s[j-1]
```

边界条件如下：

```
dp[i][i] = True # 空串为回文
dp[i][i+1] = True # 单字符为回文
```

这产生了一个直观的动态规划解法，我们首先初始化一字母和二字母的回文，然后找到所有三字母回文，并依此类推；

时间复杂度：$O(n^2)$
空间复杂度：$O(n^2)$，dp表所占用的空间

注意填表的时候要按照对角线填。

![a80c93e78d82a891e3cee4f94b7bb30e.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p10585)

#### 解法二python实现

```
class Solution:
    def longestPalindrome(self, s: str) -> str:
        n = len(s)
        if n <= 1: return s

        # dp[i][j]表示s[i:j]是否是回文
        dp = [[None]*(n+1) for _ in range(n)]
        for i in range(n-1, -1, -1): # 从下往上填 [n-1,...,0]
            for j in range(i, n+1):
                if j-i<=1: # 空串和单字符是回文
                    dp[i][j] = True
                else:
                    dp[i][j] = dp[i+1][j-1] if s[i]==s[j-1] else False
        maxLen = 1
        result = s[0]
        for i in range(n):                     # i=[0,..,n-1]
            for j in range(i+maxLen, n+1):      # j=[i+m,...,n]
                if dp[i][j] and maxLen < j-i:
                    maxLen = j - i 
                    result = s[i:j]
        return result
```

### 解法三：中心拓展法

时间复杂度： $O(n^2)$
空间复杂度： $O(1)$

#### 解法3: 实现

##### 解法3: python

```
class Solution:
    def longestPalindrome(self, s: str) -> str:
        n = len(s)
        if n<=1: return s
        ret = ""
        for i in range(n):
            # [i, i+1)
            left, right = i, i + 1 # 注意这里的 left 是闭区间 right 是开区间
            while left - 1 >= 0 and right + 1 <= n and  s[left-1] == s[right]:
                left -= 1
                right += 1
            if len(ret) < right - left:
                ret = s[left:right]
            left, right = i, i
            while left - 1 >=0 and right + 1<= n and s[left-1] == s[right]:
                left -= 1
                right += 1
            if len(ret) < right - left:
                ret = s[left: right]
        return ret
```

##### 解法3: 中心拓展法 改进

将向两边拓展的逻辑抽象成一个 extend 函数，有

```
class Solution:
    def longestPalindrome(self, s: str) -> str:
        n = len(s)
        if n<=1: return s

        ret = ""

        def extend(left, right):
            nonlocal ret
            while left - 1 >= 0 and right + 1 <= n and  s[left-1] == s[right]:
                left -= 1
                right += 1
            if len(ret) < right - left:
                ret = s[left:right]

        for i in range(n):
            extend(i, i+1)
            extend(i, i)
        return ret
```
