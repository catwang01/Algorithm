
[toc]

# Leetcode 6. Z 字形变换

## 问题描述

[6. Z 字形变换 - 力扣（LeetCode）](https://leetcode-cn.com/problems/zigzag-conversion/)

## 算法

### 解法1

#### 解法1: 实现

##### 解法1: 实现： python

```
class Solution:
    def convert(self, s: str, numRows: int) -> str:
        if numRows == 1: return s
        n = len(s)
        rows = [""] * numRows
        row = 0
        UP, DOWN = 0, 1
        direction = UP
        for i in range(n):
            rows[row] += s[i]
            if direction == UP:
                if row == 0:
                    row += 1
                    direction = DOWN
                else:
                    row -= 1
            else:
                if row == numRows - 1:
                    row -= 1
                    direction = UP
                else:
                    row += 1
        return "".join(rows)
```
            
                    


