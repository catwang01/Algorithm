[toc]

# Leetcode 115. 不同的子序列 

## 问题描述

[115. 不同的子序列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/distinct-subsequences/)

## 算法

### 解法1：暴力递归（超时）

超时运行。

设 num=0，遍历 $s(1,\cdots, n)$，
如果 $s[j]$ 和 $t[0]$ 相同，则计算 $s(j+1,j+2, \cdots, n)$ 中子序列 $t(2,\cdots, m)$ 的个数（子问题），累计到 num 上 ，最终返回答案。

边界条件是当 $len(t)==1$时，t在s中的子序列的数量就是t在s中出现的次数。

#### 解法1：实现：python

```
class Solution:
    def numDistinct(self, s: str, t: str) -> int:
        if len(t)==1:
            return s.count(t)
        num = 0
        for i in range(len(s)):
            if s[i] == t[0]:
                num += self.numDistinct(s[i+1:], t[1:])
        return num
```

### 解法2: 回溯（超时）

#### 解法2: 实现：python

```
class Solution:
    def numDistinct(self, s: str, t: str) -> int:

        ret = 0
        def dfs(i, j): # dfs 表示 s[:i], t[:j] 完成匹配，接下要匹配 s[i:], t[j:]
            nonlocal ret, t, s
            if j == len(t):
                ret += 1
                return 
            if len(s) - i < len(t) - j: # s[i:] 长度小于 t[j:] 长度
                return
            # 选择 i
            if s[i] == t[j]: dfs(i+1, j+1)
            # 不选择 i
            dfs(i+1, j)
        
        dfs(0, 0)
    return ret
```

### 解法3: dp

定义：`dp[i][j]` 表示 s 中以 s[i-1] 结尾的子序列有多少个 t[:j]（注意 t[:j] 表示 (t[0], ..., t[j-1]) 不包含 t[j]）

那么，有下面两种情况

1. s[i-1] == t[j-1]

此时我们要求 s[:i-1] 中有多少 t[:j-1]。这个要如何用 dp 来表示呢？由于我们的 dp[i][j] 定义中，将子序列的末尾固定为 s[i-1] 了。因此，我们在计算 s[:i-1] 中有多少 t[:j-1] 时，需要遍历所有可能的末尾元素。
即 

```
dp[i][j] = sum(dp[k][j-1] for k in range(i))
```

2. 如果 s[i-1] != t[j-1]

按照定义，以 s[i-1] 结尾的序列不可能等于 t[:j]，因此 dp[i][j] = 0

由此我们得到了转移方程

```
dp[i][j] = sum(dp[k][j-1] for k in range(i)) if s[i-1] == t[j-1]
         = 0                                    s[i-1] != t[j-1]
```

这里初始化容易出错。

当 `i = 0` 时，`dp[0][j]` 表示以 `s[:0] = ""` 结尾的字序列中等于 `t[:j]` 的个数，因此当 `j=0` 时 `dp[i][j] = dp[0][0] = 1`，其他情况 `dp[i][j] = dp[0][j]` 不为 0 

#### 复杂度分析

时间复杂度的一个上界是 $O(n^3)$，但是由于许多 s[i-1] != t[j-1]，计算这部分的时间复杂度为 $O(1)$，因此实际运行起来不会太慢。

空间复杂度： $O(n^2)$

##### 解法3: 实现：python

```
class Solution:
    def numDistinct(self, s: str, t: str) -> int:
        ns, nt = len(s), len(t)
        if nt == 0: return 1 # t 为空，此时可以将 s 都删除得到一个空序列，算一个
        if ns == 0: return 0 # s 为空，且 t 不为空，t 不可能是 s 的子序列
        dp = [[0 for j in range(nt+1)]for i in range(ns+1)]
        # 除 i=j=0 外，i=0 || j=0 时为 0
        dp[0][0] = 1

        for i in range(1, ns+1):
            for j in range(1, nt+1):
                if s[i-1] == t[j-1]:
                    for k in range(i):
                        dp[i][j] += dp[k][j-1] # s[:k] 和 t[:j-1]
        ret = 0
        for i in range(ns+1):
            ret += dp[i][nt]
        return ret
```

### 解法4: 另一种转移方程


我们定义 `dp[i][j]` 为 `s[:i]` 中含有 `t[:j]` 的个数。这次，我们没有添加子序列必须以 `s[i-1]` 结尾的约束。

那么，也有两种情况

1. `s[i-1] == t[j-1]` 时，子序列可能以 s[i-1] 结尾，也可能不以 s[i-1] 结尾。
如果子序列以 `s[i-1]` 结尾，相当于 `s[i-1]` 消耗了 `t[j-1]`，这样的子序列有 `dp[i-1][j-1]`；如果子序列不以 `s[i-1]` 结尾，那么这样的子序列有 `dp[i-1][j]` 个

因此

```
dp[i][j] = dp[i-1][j-1] + dp[i-1][j]
```

2. 如果 `s[i-1] != t[j-1]` ，那么只可能在 `s[:j-1]` 中找有没有子序列等于 `t[:j]`，即

```
dp[i][j] = dp[i-1][j-1]
```

因此，有

```
dp[i][j] = dp[i-1][j-1] + dp[i-1][j]    if s[i-1] == t[j-1]
         = dp[i-1][j]                   if s[i-1] == t[j-1]
```

注意，根据 `dp[i][j]` 的定义，当 `j = 0` 时，`s[:i]` 中总包含 `t[:j] = t[:0] = ""`，因此 `dp[i][0] = 1`

#### 复杂度分析

时间复杂度：$O(n^2)$
空间复杂度： $O(n^2)$

##### 解法4：实现3：python

```
class Solution:
    def numDistinct(self, s: str, t: str) -> int:
        ns, nt = len(s), len(t)
        if nt == 0: return 1
        if ns == 0: return 0
        dp = [[0 for j in range(nt+1)]for i in range(ns+1)]
        # dp[i][j] 表示 s[:i] 中有多少 t[:j]
        # i=0 时为 0
        # j=0 时为 1
        for i in range(ns+1):
            dp[i][0] = 1

        for i in range(1, ns+1):
            for j in range(1, nt+1):
                if s[i-1] == t[j-1]:
                    dp[i][j] = dp[i-1][j-1] + dp[i-1][j]
                else:
                    dp[i][j] = dp[i-1][j]
        return dp[ns][nt]
```