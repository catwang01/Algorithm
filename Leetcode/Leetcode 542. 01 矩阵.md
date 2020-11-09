[toc]

# Leetcode 542. 01 矩阵

## 问题描述

[542. 01 矩阵 - 力扣（LeetCode）](https://leetcode-cn.com/problems/01-matrix/)

给定一个由 0 和 1 组成的矩阵，找出每个元素到最近的 0 的距离。

两个相邻元素间的距离为 1 。

**示例 1:**
输入:

0 0 0
0 1 0
0 0 0

输出:

0 0 0
0 1 0
0 0 0

**示例 2:**
输入:

0 0 0
0 1 0
1 1 1

输出:

0 0 0
0 1 0
1 2 1

**注意:**

1.  给定矩阵的元素个数不超过 10000。
2.  给定矩阵中至少有一个元素是 0。
3.  矩阵中的元素只在四个方向上相邻: 上、下、左、右。

## 算法

将每个元素看作图上的节点，两个元素相邻相当于两个元素对应的节点在图上有一条边。

假想有一个虚拟起始节点，连接所有 0 元素。我们从虚拟其实节点开始做层次遍历，那么每个元素到最近的 0 的距离实际上是层次遍历的层数。

### 解法1： bfs

##### 解法1: 实现：python

```
class Solution:
    def updateMatrix(self, matrix: List[List[int]]) -> List[List[int]]:
        if len(matrix)==0 or len(matrix[0])==0: return matrix
        nrow, ncol = len(matrix), len(matrix[0])
        UNSEEN, SEEN =  -1, -2
        ret = [[UNSEEN] * ncol for i in range(nrow)]

        q = deque()
        for i in range(nrow):
            for j in range(ncol):
                if matrix[i][j] == 0:
                    q.append((i, j))
                    ret[i][j] = SEEN
        directions = [[0, 1], [0, -1], [1, 0], [-1, 0]]
        level = -1
        while len(q):
            levelsize = len(q)
            level += 1
            for _ in range(levelsize):
                i, j = q.popleft()
                ret[i][j] = level
                for dx, dy in directions:
                    x = dx + i
                    y = dy + j
                    if 0 <= x < nrow and 0 <= y < ncol and ret[x][y] == UNSEEN:
                        q.append((x, y))
                        ret[x][y] = SEEN
        return ret
```
