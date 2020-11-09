
[toc]

# Leetcode 973. 最接近原点的 K 个点

## 问题描述

[973. 最接近原点的 K 个点 - 力扣（LeetCode）](https://leetcode-cn.com/problems/k-closest-points-to-origin/submissions/)

## 算法

### 解法一：快速选择

由于可以返回任何顺序，所以可以使用快速选择

时间复杂度： $O(n)$ （平均情况）
空间复杂度： $O(1)$

#### 解法一python实现

```
import math
import random

class Solution:
    def kClosest(self, points: List[List[int]], K: int) -> List[List[int]]:
        self.quickSelect(points, 0, len(points)-1, K-1)
        return points[:K]

    def dist(self, p):
        return math.sqrt(p[0] ** 2 + p[1] ** 2)
        
    def quickSelect(self, A, low, high, k):
        if low < high:
            pivot_idx = random.randint(low, high)
            pivot = self.dist(A[pivot_idx])
            A[pivot_idx], A[high] = A[high], A[pivot_idx]
            i = low - 1
            for j in range(low, high+1):
                if self.dist(A[j]) <= pivot:
                    i += 1
                    if A[i] != A[j]:
                        A[i], A[j] = A[j], A[i]
            if i>k: 
                self.quickSelect(A, low, i-1, k)
            if i<k: 
                self.quickSelect(A, i+1, high, k)
```

### 解法2: 堆

#### 解法2: 实现：大根堆

##### 解法2: 实现：python

```
def distance(point):
    return sqrt(point[0] ** 2 + point[1] ** 2)
    
class BigRootHeap:
    def __init__(self):
        self.data = []
    
    def push(self, point):
        dis = distance(point)
        heapq.heappush(self.data, (-dis, point)) # 距离相反数入栈，模仿大根堆

    def top(self):
        return self.data[0][1]

    def pop(self):
        return heapq.heappop(self.data)[1]
    
    def __len__(self):
        return len(self.data)

class Solution:
    def kClosest(self, points: List[List[int]], K: int) -> List[List[int]]:
        heap = BigRootHeap()
        for i in range(len(points)):
            if i < K:
                heap.push(points[i])
            else:
                if distance(points[i]) < distance(heap.top()):
                    heap.pop()
                    heap.push(points[i])
        ret = []
        while len(heap):
            ret.append(heap.pop())
        return ret
```
