[toc]

# Leetcode 155. 最小栈

## 问题描述

[155. 最小栈 - 力扣（LeetCode）](https://leetcode-cn.com/problems/min-stack/)

## 算法

### 解法1: 单调栈

用一个非严格递减的单调栈来保存最小值。

```
class MinStack:

    def __init__(self):
        """
        initialize your data structure here.
        """
        self.data = []
        self.mindata = []

    def push(self, x: int) -> None:
        self.data.append(x)
        if not self.mindata or self.mindata[-1] >= x:
            self.mindata.append(x)

    def pop(self) -> None:
        val = self.data.pop()
        if val == self.mindata[-1]:
            self.mindata.pop()

    def top(self) -> int:
        return self.data[-1]

    def getMin(self) -> int:
        return self.mindata[-1]


# Your MinStack object will be instantiated and called as such:
# obj = MinStack()
# obj.push(x)
# obj.pop()
# param_3 = obj.top() 
# param_4 = obj.getMin()
```
