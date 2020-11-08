[toc]


# Leetcode 32. 最长有效括号

## 问题描述

[32. 最长有效括号 - 力扣（LeetCode）](https://leetcode-cn.com/problems/longest-valid-parentheses/)

## 算法

一个序列，要满足有效的括号序列，需要满足两个条件：
1. 序列的长度为偶数
2. 对于每个 `)` 来说，它左边的 `(` 的个数小于等于它左边的 `)` 的个数（包含它本身）

### 解法1: 栈

加入有如下的序列 
```
(, ..., ), ...
        ^
        |
        |
        i
```

其中 i 位置上的 `)` 它左边的 `(` 个数多于 `)`。那么，在计算之后的序列时，可以从 i+1, i+2, ... 开始计算，而不用考虑 [0, ..., i] 的部分，因为 i+1, ..., 之后的元素不可能和 [0, ..., i] 的元素构成有效括号。

我们可以用一个栈来存储 `(`。遇到右括号时，我们就 pop

##### 解法1: 实现： python

```
class Solution:
    def longestValidParentheses(self, s: str) -> int:
        n = len(s)
        maxlen = 0
        st = [-1] # 上一次没有配对的
        for i in range(n):
            if s[i] == '(':
                st.append(i)
            else:
                st.pop()
                if st:
                    maxlen = max(maxlen, i - st[-1])
                else: # 栈空，说明上一次没有配对的 `)` 被弹了出来，栈中已经没有了可以和 `)`
                    # 说明 s[i] 弹出的元素是 `)` 而不是 `(`，因此没有 `(` 和 s[i] 配对
                    st.append(i)
        return maxlen              
```

### 解法2: 动态规划

时间复杂度：$O(n)$

##### 解法2: 实现：python

```
class Solution:
    def longestValidParentheses(self, s: str) -> int:
        n = len(s)
        s = ')' + s # 添加一个元素
        dp = [0] * (n+1)
        maxlen = 0
        for i in range(1, n+1):
            if s[i] == ')':
                if s[i-1] == '(':
                    dp[i] = dp[i-2] + 2
                else: # s[i-1] = ')'
                    if s[i - 1 - dp[i-1]] == '(':
                        dp[i] = 2 + dp[i-1] + dp[i - 1 - dp[i-1]-1]
                    else:
                        dp[i] = 0
            maxlen = max(maxlen, dp[i])
        return maxlen
```

### 解法3: 

两次遍历即可，参考 [ 1 ]。但是这个比较难想到。

第一次遍历可以理解。但是第二次遍历就不是很能理解了。

##### 解法3: 实现： python

```
class Solution:
    def longestValidParentheses(self, s: str) -> int:
        n = len(s)
        maxlen = 0
        left = right = 0
        for i in range(n):
            if s[i] == '(': 
                left += 1
            else:
                right += 1
            if right > left:
                left = right = 0
            if right == left:
                maxlen = max(maxlen, left+right)
        
        left = right = 0
        for i in range(n-1, -1, -1):
            if s[i] == '(': 
                left += 1
            else:
                right += 1
            if right < left:
                left = right = 0
            if right == left:
                maxlen = max(maxlen, left+right)

        return maxlen
```

# References
1. [最长有效括号 - 最长有效括号 - 力扣（LeetCode）](https://leetcode-cn.com/problems/longest-valid-parentheses/solution/zui-chang-you-xiao-gua-hao-by-leetcode-solution/)