[toc]

# Leetcode 面试题41. 数据流中的中位数

## 问题描述

[面试题41. 数据流中的中位数 - 力扣（LeetCode）](https://leetcode-cn.com/problems/shu-ju-liu-zhong-de-zhong-wei-shu-lcof/) 

## 算法

### 解法1: 插入排序

#### 解法1:实现

##### 解法1: python

```
class MedianFinder:

    def __init__(self):
        self.len = 0
        self.data = []

    def addNum(self, num: int) -> None:
        if len(self.data) == 0:
            self.data.append(num)
            return
        for i in range(len(self.data)):
            if self.data[i] > num:
                self.data.insert(i, num)
                return
        self.data.append(num)

    def findMedian(self) -> float:
        length = len(self.data)
        if length==0:
            return 0.0
        mid = length >> 1
        if length & 1:
            return float(self.data[mid])
        else:
            return (self.data[mid-1] + self.data[mid]) / 2.0
```

### 解法2: 二分法

用二分法代替插入排序

#### 解法2:实现

##### 解法2: python

```
class MedianFinder:

    def __init__(self):
        self.len = 0
        self.data = []

    def bisearch(self, low, high, target, A):
        if target > A[high]:
            return high+1
        while low < high:
            mid = low + high >> 1
            if A[mid] >= target:
                high = mid
            else:
                low = mid + 1
        return low

    def addNum(self, num: int) -> None:
        if len(self.data) == 0:
            self.data.append(num)
            return
        idx = self.bisearch(0, len(self.data)-1, num, self.data)
        self.data.insert(idx, num)

    def findMedian(self) -> float:
        length = len(self.data)
        if length==0:
            return 0.0
        mid = length >> 1
        if length & 1:
            return float(self.data[mid])
        else:
            return (self.data[mid-1] + self.data[mid]) / 2.0
```

### 解法3: 大根堆 + 小根堆

# Todo - 2020-04-25 23:10 -- by ed 这个文字叙述不清！

维护两个堆。一个保存左边的数，是大根堆。一个保存右边的数，是小根堆。

我们总是维护这两个堆，使得左边的堆中的元素数目和右边的堆中的元素数目相等，或者比右边的堆中的元素数目多一。

当新来一个数字之后，比较两个堆中的个数。如果左边的堆中元素数目更多，说明这个数需要加到右边的堆中。但是不能直接回到左边的堆中，因为如果这个元素比右边的

python 中没有大根堆，因此将 -x 放入。

#### 解法3:实现

##### 解法3: 

```
import heapq

class MedianFinder:
    def __init__(self):
        self.len = 0
        self.heapleft = [] # 大 (-x)
        self.heapright = [] # 小 (x)

    def addNum(self, num: int) -> None:
        if len(self.heapleft)==len(self.heapright):
            val = heapq.heappushpop(self.heapright, num)
            heapq.heappush(self.heapleft, -val)
        else:
            val = heapq.heappushpop(self.heapleft, -num)
            heapq.heappush(self.heapright, -val)

    def findMedian(self) -> float:
        lenLeft, lenRight = len(self.heapleft), len(self.heapright)

        if lenLeft == 0:
            return 0.0
        if lenLeft > lenRight:
            return -self.heapleft[0]
        else:
            return (-self.heapleft[0] + self.heapright[0]) / 2
```


# References
1. [python题解--大小堆 - 数据流中的中位数 - 力扣（LeetCode）](https://leetcode-cn.com/problems/shu-ju-liu-zhong-de-zhong-wei-shu-lcof/solution/pythonti-jie-da-xiao-dui-by-xiao-xue-66/)
