[toc]

# Leetcode 120. 三角形最小路径和

## 问题描述

[120. 三角形最小路径和 - 力扣（LeetCode）](https://leetcode-cn.com/problems/triangle/)

给定一个三角形，找出自顶向下的最小路径和。每一步只能移动到下一行中相邻的结点上。

相邻的结点 在这里指的是 下标 与 上一层结点下标 相同或者等于 上一层结点下标 + 1 的两个结点。
 

例如，给定三角形：

[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
自顶向下的最小路径和为 11（即，2 + 3 + 5 + 1 = 11）。

 

说明：

如果你可以只使用 O(n) 的额外空间（n 为三角形的总行数）来解决这个问题，那么你的算法会很加分。

## 算法

### 解法1: 递归+记忆化

#### 解法1：实现

##### 解法1: python

```cpp
class Solution:
    def __init__(self):
        self.memo = {}
        
    def minimumTotal(self, triangle: List[List[int]]) -> int:
        return self.helper(triangle, 0, 0)
        
    def helper(self, triangle, i, j):
        if i == len(triangle):
            return 0
        if ((i,j) not in self.memo):
            self.memo[(i,j)] = triangle[i][j] + min(self.helper(triangle, i+1, j), self.helper(triangle, i+1, j+1))
        return self.memo[(i,j)]
```

### 解法2: dp 自下而上

在 triangle 上原地修改，从而节省 dp 表的内存。

一个道理：长最短路径从终点出发会比较简单。

#### 解法2:python 实现

##### 解法2: python

```
class Solution:
    def minimumTotal(self, triangle: List[List[int]]) -> int:
        n = len(triangle)
        if n==0: return 0
        if n==1: return triangle[0][0]
        for i in range(n-2, -1, -1):
            for j in range(len(triangle[i])):
                triangle[i][j] += min(triangle[i+1][j], triangle[i+1][j+1])
        return triangle[0][0]
```