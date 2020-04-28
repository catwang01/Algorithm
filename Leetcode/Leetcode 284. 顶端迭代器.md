[toc]

# Leetcode 284. 顶端迭代器

## 问题描述

[284. 顶端迭代器 - 力扣（LeetCode）](https://leetcode-cn.com/problems/peeking-iterator/)

## 算法

### 解法1: 

#### 解法1:实现

##### 解法1: c++

```
class PeekingIterator:
    def __init__(self, iterator):
        self._next = None
        self.iterator = iterator

    def peek(self):
        if self._next is None:
            if self.iterator.hasNext():
                self._next = self.iterator.next()
        return self._next

    def next(self):
        if self._next is not None:
            ret = self._next
            self._next = None
            return ret
        if self.iterator.hasNext():
            return self.iterator.next()
        else:
            return None

    def hasNext(self):
        if self._next is not None:
            return True
        return self.iterator.hasNext()
```

