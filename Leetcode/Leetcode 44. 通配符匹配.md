[toc]

# Leetcode 44. 通配符匹配

## 问题描述

[44. 通配符匹配 - 力扣（LeetCode）](https://leetcode-cn.com/problems/wildcard-matching/)

## 算法

### 解法零：使用正则

#### 解法零：实现

##### 解法零：python

![2375808b502b592dd3bd685886261ab9.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p10736)

```
import re
class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        # 多个*替换为一个.*，可以提高效率
        # ? 替换为 .
        p = re.sub(r'\*{1,}', '.*', p.replace('?', '.'))
        res = re.search(p, s)
        if res is not None and res.group()==s:
            return True
        else:
            return False
```

### 解法一：递归

#### 解法一：实现

##### 解法一：python

![5c958fba7ec15ec0d898550fd772181c.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p10734)

```
class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        if s=='': 
            return set(p)==set(['*']) or p==''
        else:
            if p=='': 
                return False
            else:
                if p[0] == '?':
                    return self.isMatch(s[1:], p[1:])
                elif p[0] == '*':
                    return self.isMatch(s[1:], p[1:]) or \
                            self.isMatch(s, p[1:]) or \
                            self.isMatch(s[1:], p)
                else:
                    return self.isMatch(s[1:], p[1:]) if s[0]==p[0] else False
```

### 解法二：递归 + 下标做参数

#### 解法二：实现

##### 解法二：python

![37074ef3f45f09d743f7b11943b9cef2.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p10737)

```
class Solution:
    def isMatch(self, s: str, p: str) -> bool:

        def aux(i, j):
            if i == len(s): 
                if j==len(p):
                    return True
                else:
                    for k in range(j, len(p)):
                        if p[k] != '*': 
                            return False
                    return True
            else:
                if j == len(p): 
                    return False
                else:
                    if p[j] == '?':
                        return aux(i+1, j+1)
                    elif p[j] == '*':
                        return aux(i+1, j+1) or \
                                aux(i, j+1) or \
                                aux(i+1, j)
                    else:
                        return aux(i+1, j+1) if s[i]==p[j] else False
        return aux(0, 0)
```

### 解法四：递归 + 记忆化

基于解法四，添加记忆化，并将函数名由 aux 修改为 dp

#### 解法四：实现

##### 解法四：python

```
class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        memo = {}
        def dp(i, j):
            if (i,j) not in memo:
                if i == len(s): 
                    if j==len(p):
                        memo[i,j] = True
                    else:
                        for k in range(j, len(p)):
                            if p[k] != '*': 
                                memo[i,j] = False
                                return memo[i,j]
                        memo[i,j] = True
                else:
                    if j == len(p): 
                        memo[i,j] = False
                    else:
                        if p[j] == '?':
                            memo[i,j] = dp(i+1, j+1)
                        elif p[j] == '*':
                            memo[i,j] = dp(i+1, j+1) or \
                                    dp(i, j+1) or \
                                    dp(i+1, j)
                        else:
                            memo[i,j] = dp(i+1, j+1) if s[i]==p[j] else False
            return memo[i,j]
        return dp(0, 0)
```

### 解法五：dp

将解法四的递归 + 记忆化修改为dp

#### 解法五：实现

##### 解法五：python

```
class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        
        n, m = len(s), len(p)
        dp = [[True] * (m+1) for _ in range(n+1)]
        
        # 初始化 n-th 行
        j = m-1
        while j >= 0 and p[j]=='*':
            j -= 1
        while j>=0:
            dp[n][j] = False
            j -= 1

        # 初始化 m-th 列
        for i in range(n):
            dp[i][m] = False

        # 填表
        for i in range(n-1, -1, -1):
            for j in range(m-1, -1, -1):
                if p[j] == '?':
                    dp[i][j] = dp[i+1][j+1]
                elif p[j] == '*':
                    dp[i][j] = dp[i+1][j+1] or dp[i][j+1] or dp[i+1][j]
                else:
                    dp[i][j] = dp[i+1][j+1] if s[i]==p[j] else False
        return dp[0][0]
```

#### 解法5: 实现2: 

用 `dp[i][j]` 表示 `s[:i]` 和 `p[:j]` 是否匹配。则转移方程为

```
         = dp[i-1][j-1]                     p[j-1]=='?' or p[j-1]==s[i-1]
dp[i][j] = dp[i][j-1] or dp[i][j-1]          p[j-1] == '*'
        = false                           otherwise
```

其中，当 `p[j-1]=='*'` 时有两种情况：

1. `*` 被消耗掉，此时 `dp[i][j] = dp[i][j-1]`
2. `*` 消耗掉 `s[i-1]`，`dp[i][j] = dp[i-1][j]`

##### 解法5: 实现2: python

```
class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        ns, np = len(s), len(p)
        dp = [[False] * (np+1) for i in range(ns+1)]
        dp[0][0] = True
        # 模式串为空
        for i in range(1, ns+1): dp[i][0] = False
        # 目标串 s 为空
        for j in range(1, np+1): # 如果 p[:j] 全是 "*"，那么dp[0][j] 为 True
            dp[0][j] = p[j-1] == '*' and dp[0][j-1]
        for i in range(1, ns+1):
            for j in range(1, np+1):
                if p[j-1] == "?" or p[j-1] == s[i-1]:
                    dp[i][j] = dp[i-1][j-1]
                elif p[j-1] == '*':
                    dp[i][j] = dp[i][j-1] or dp[i-1][j]
                # 其他情况为 false
        return dp[ns][np]
```
