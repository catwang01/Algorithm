
[toc]

# Leetcode 54. 螺旋矩阵

[面试题29. 顺时针打印矩阵 - 力扣（LeetCode）](https://leetcode-cn.com/problems/shun-shi-zhen-da-yin-ju-zhen-lcof/)
[54. 螺旋矩阵 - 力扣（LeetCode）](https://leetcode-cn.com/problems/spiral-matrix/)

## 问题描述

## 算法

### 解法一：按层打印——递归

#### 解法一：实现

##### 解法1: 实现1: python

```
class Solution:
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        # 特判
        m = len(matrix)
        if m==0: return []
        n = len(matrix[0])
        if n==0: return []

        result = []
        def aux(row1, row2, col1, col2):
            if row1 > row2 or col1 > col2: return
            # 只有一行
            if row1==row2:
                result.extend(matrix[row1][col1:col2+1])
                return
            # 只有一列
            if col1==col2:
                for row in range(row1, row2+1):
                    result.append(matrix[row][col1])
                return
            
            # left top -> right top
            for col in range(col1, col2):
                result.append(matrix[row1][col])
            # right top -> right bottom
            for row in range(row1, row2):
                result.append(matrix[row][col2])
            # right bottom -> left bottom
            for col in range(col2, col1, -1):
                result.append(matrix[row2][col])
            # left bottom -> right top
            for row in range(row2, row1, -1):
                result.append(matrix[row][col1])
            # 递归
            aux(row1+1, row2-1, col1+1, col2-1)

        aux(0, m-1, 0, n-1)
        return result
```

##### 解法1: 实现：c++

```
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ret;
        if (matrix.size()==0|| matrix[0].size()==0) return ret;
        int nrow = matrix.size(), ncol = matrix[0].size();
        helper(matrix, 0, nrow, 0, ncol, ret);
        return ret;
    }

    void helper(vector<vector<int>>& matrix, int x1, int x2, int y1, int y2, vector<int>& ret)
    // [x1, x2) [y1, y2)
    {
        cout << x1 << " " << x2 << endl;
        if (x1 >= x2 || y1 >= y2) return;

        int i, j;
        if (x2 - x1 == 1) {
            for (i=x1, j=y1; j<y2; j++) ret.push_back(matrix[i][j]); 
            return;
        }
        if (y2 - y1 == 1)
        {
            for (j=y1, i=x1; i<x2; i++) ret.push_back(matrix[i][j]);
            return;
        }
        for (i=x1, j=y1; j<y2-1; j++) ret.push_back(matrix[i][j]);
        for (j=y2-1, i=x1; i < x2-1; i++) ret.push_back(matrix[i][j]);
        for (i=x2-1, j=y2-1; j >= y1+1; j--) ret.push_back(matrix[i][j]);
        for (j=y1, i=x2-1; i >= x1+1; i--) ret.push_back(matrix[i][j]);
        helper(matrix, x1+1, x2-1, y1+1, y2-1, ret);
    }
};
```