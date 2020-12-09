[toc]

# Leetcode 150. 逆波兰表达式求值

## 问题描述

[150. 逆波兰表达式求值 - 力扣（LeetCode）](https://leetcode-cn.com/problems/evaluate-reverse-polish-notation/)

## 算法

### 解法1

#### 解法1: 实现：

##### 解法1: 实现：python

```
class Solution:
    def evalRPN(self, tokens: List[str]) -> int:
        st = []
        for token in tokens:
            if token in {"+", "-", "*", "/"}:
                y = st.pop()
                x = st.pop()
                st.append(self.getOp(token)(x, y))
            else:
                st.append(int(token))
        return st[-1]

    def getOp(self, op):
        return {"+": lambda x,y: x + y,
                "-": lambda x,y: x - y,
                "*": lambda x,y: x * y,
                "/": lambda x,y: int(x / y)}.get(op) # 注意题目的除法定义和 python 的整除不同。因此不能用 //
```