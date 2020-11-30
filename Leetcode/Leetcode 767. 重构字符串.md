[toc]

# Leetcode 767. 重构字符串

## 问题描述

[767. 重构字符串 - 力扣（LeetCode）](https://leetcode-cn.com/problems/reorganize-string/)

## 解法

### 解法1：大根堆 + 贪心

参考 [ 1 ]

##### 解法1: 实现1：python

```
class BigRootHeap:
    def __init__(self):
        self.data = []
    
    def push(self, val):
        heapq.heappush(self.data, (-val[0], val[1]))
    
    def pop(self):
        ret = heapq.heappop(self.data)
        return (-ret[0], ret[1])
    
    def __len__(self):
        return len(self.data)

class Solution:
    def reorganizeString(self, S: str) -> str:
        heap = BigRootHeap()
        for k, v in Counter(S).items():
            heap.push((v, k))
        ret = ""
        while len(heap):
            v1, k1 = heap.pop()
            ret += k1
            v1 -= 1
            if len(heap) == 0:
                return "" if v1 else ret
            v2, k2 = heap.pop()
            ret += k2
            v2 -= 1
            if v2: heap.push((v2, k2))
            if v1: heap.push((v1, k1))
        return ret
```

# References
1. [重构字符串 简单的算法 - 重构字符串 - 力扣（LeetCode）](https://leetcode-cn.com/problems/reorganize-string/solution/zhong-gou-zi-fu-chuan-jian-dan-de-suan-fa-by-stran/)