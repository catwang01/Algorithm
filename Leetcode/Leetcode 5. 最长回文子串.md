
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
上面两个条件可以简化为

```
dp[i][j] = s[i] == s[j-1] and dp[i+1][j-1]
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
        # dp[i][j] 表示 s[i:j] 是回文串
        n = len(s)
        if n <= 1: return s
        dp = [[0] * (n+1) for _ in range(n+1)]
        maxlen = 1
        ret = s[0]
        for i in range(n): # 长度为0的子串是回文串
            dp[i][i] = True
        for i in range(n): # 长度为 1 的子串是回文串
            dp[i][i+1] = True
        for k in range(2, n+1):
            for i in range(0, n - k + 1): # [i:i+k] i + k <= n -->i <= n - k
                dp[i][i+k] = s[i] == s[i+k-1] and dp[i+1][i+k-1]
                if dp[i][i+k]:
                    if k > maxlen:
                        maxlen = k
                        ret = s[i:i+k]
        return ret
```

### 解法三：中心拓展法

时间复杂度： $O(n^2)$
空间复杂度： $O(1)$

#### 解法3: 实现1：左闭右开区间

##### 解法3: 实现1: python

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

#### 解法3: 实现2: 闭区间

```
class Solution:
    def longestPalindrome(self, s: str) -> str:
        n = len(s)
        ret = ""
        maxlen = 0
        for i in range(n):
            left = right = i
            while left - 1 >= 0 and right + 1 < n and s[left-1] == s[right + 1]:
                left -= 1
                right += 1
            # left - 1 < 0 or right + 1 == n or s[left-1] != s[right + 1]
            if right - left + 1 > maxlen:
                maxlen = right - left + 1
                ret = s[left:right+1]

            left, right = i, i + 1
            if i + 1 < n and s[left] == s[right]:
                while left - 1 >= 0 and right + 1 < n and s[left-1] == s[right + 1]:
                    left -= 1
                    right += 1
                # left - 1 < 0 or right + 1 == n or s[left-1] != s[right + 1]
                if right - left + 1 > maxlen:
                    maxlen = right - left + 1
                    ret = s[left:right+1]
        return ret
```

#### 解法3: 实现3: 添加虚拟元素化简情况

由于有两种情况。第一种情况比较直观。第二种情况可以添加一个虚拟元素转换为第一种情况。

添加一个虚拟元素的目的是可以简化问题。假设下标是在虚拟数组（就是原数组添加虚拟元素后的数组）上进行加减，只需要在取数的时候根据映射关系将虚拟数组上面的数映射到原数组上。

##### 解法3: 实现3:python

```
class Solution:
    def longestPalindrome(self, s: str) -> str:
        n = len(s)
        if n <= 1: return s

        max_length = 1
        ret = s[0]

        for i in range(n):
            left, right = i - 1, i + 1
            while left>=0 and right < n and s[left] == s[right]:
                left -= 1
                right += 1
            left += 1
            right -= 1

            if right - left + 1 > max_length:
                max_length = right - left + 1
                ret = s[left: right+1]

            # 假设多了一个元素
            left, right = i, i + 2
            # 因此 right < n + 1 而非 right < n
            # 在取数时，需要映射到原来的数组上
            while left >= 0 and right < n+1 and s[left]==s[right-1]:
                left -= 1
                right +=1
            left += 1
            right -= 1

            # 计算长度时要减 1，因为要减去虚拟元素
            if right - left > max_length:
                max_length = right - left
                ret = s[left: right]
        return ret
```

#### 解法3: 实现3： 中心拓展法 改进


将向两边拓展的逻辑抽象成一个 extend 函数

##### 解法3: 实现3: python

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
