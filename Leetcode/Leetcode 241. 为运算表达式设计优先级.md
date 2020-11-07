
[toc]

# Leetcode 241. 为运算表达式设计优先级

## 问题描述

[241. 为运算表达式设计优先级 - 力扣（LeetCode）](https://leetcode-cn.com/problems/different-ways-to-add-parentheses/)


注：这个问题貌似不需要考虑 `-2-1-1` 这种输入。

## 算法

### 解法1: 递归


#### 解法1:

```
class Solution:
    def diffWaysToCompute(self, s: str) -> List[int]:
        ret = []
        isdight = True
        for i in range(len(s)):
            if s[i] in {"+", "*", "-"}:
                isdight = False
                left = self.diffWaysToCompute(s[:i])
                right = self.diffWaysToCompute(s[i+1:])
                for x in left:
                    for y in right:
                        ret.append(self.operator(s[i])(x, y))
        if isdight:  # 这个可以用python的内置函数 str.isdigit 代替
            return [int(s)]
        return ret
    
    def operator(self, op):
        return {
            "+": lambda x,y: x + y,
            "-": lambda x, y: x - y,
            "*": lambda x, y: x * y
        }.get(op)
```

# References
1. [Python/Golang 分治算法 - 为运算表达式设计优先级 - 力扣（LeetCode）](https://leetcode-cn.com/problems/different-ways-to-add-parentheses/solution/pythongolang-fen-zhi-suan-fa-by-jalan/)