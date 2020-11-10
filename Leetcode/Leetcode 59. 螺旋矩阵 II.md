[toc]

# Leetcode 59. 螺旋矩阵 II

## 问题描述

[59. 螺旋矩阵 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/spiral-matrix-ii/)

## 算法

### 解法1：使用状态量

```
class Solution:
    def generateMatrix(self, n: int) -> List[List[int]]:
        matrix = [[0] * n for _ in range(n)]
        x = 1
        x1 = y1 = 0
        x2 = y2 = n-1
        LEFT, RIGHT, DOWN, UP = 0, 1, 2, 3
        i, j = x1, y1
        direction = RIGHT
        while x <= n * n:
            matrix[i][j] = x
            x += 1
            if i == x1 + 1 and j == y1:
                x1 += 1
                y1 += 1
                x2 -= 1
                y2 -= 1
                i, j = x1, y1

            elif direction == RIGHT:
                j += 1
                if j == y2:
                    direction = DOWN

            elif direction == DOWN:
                i += 1
                if i == x2:
                    direction = LEFT
            
            elif direction == LEFT:
                j -= 1
                if j == y1:
                    direction = UP
            
            elif direction == UP:
                i -= 1
                if i == x1 + 1:
                    direction = RIGHT
        return matrix
```

### 解法2

```
class Solution:
    def generateMatrix(self, n: int) -> List[List[int]]:
        
        x = 1
        matrix = [[0] * n for _ in range(n)]

        def generateMatrixFromx(x1, x2, y1, y2): # [x1, x2) [y1, y2)
            nonlocal x
                    
            if x2 - x1 == 1:
                matrix[x1][y1] = x
                return
            if x1 > x2:
                return
            for j in range(y1, y2-1):
                matrix[x1][j] = x
                x += 1
            for i in range(x1, x2-1):
                matrix[i][y2-1] = x
                x += 1
            
            for j in range(y2-1, y1, -1):
                matrix[x2-1][j] = x
                x += 1
            
            for i in range(x2-1, x1, -1):
                matrix[i][y1] = x
                x += 1
            generateMatrixFromx(x1+1, x2-1, y1+1, y2-1)

        generateMatrixFromx(0, n, 0, n)

        return matrix
```