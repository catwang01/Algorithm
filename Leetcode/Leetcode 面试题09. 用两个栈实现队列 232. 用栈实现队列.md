
[toc]

# Leetcode 面试题09. 用两个栈实现队列

[面试题09. 用两个栈实现队列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof/)

相同题目 [232. 用栈实现队列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/implement-queue-using-stacks/)

## 算法

### 解法一：一个栈存储数据一个栈辅助

#### 解法一：复杂度分析

- appendTail

时间复杂度： $O(n)$ 因为之前的元素都要先出栈，后进栈，因此为 $O(2n)=O(n)$
空间复杂度： $O(n)$

- deleteHead
时间复杂度： $O(1)$
空间复杂度： $O(1)$

#### 解法一：实现

##### 解法一：python

```
class CQueue:

    def __init__(self):
        self.s1 = [] 
        self.s2 = []

    def appendTail(self, value: int) -> None:
            while self.s1: # s1 != []
                self.s2.append(self.s1.pop())
            self.s1.append(value)
            while self.s2: # s2 != []
                self.s1.append(self.s2.pop())

    def deleteHead(self) -> int:
        return self.s1.pop() if self.s1 else -1
```

# References
[面试题09. 用两个栈实现队列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof/)
