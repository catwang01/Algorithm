[toc]

# Leetcode 221. 最大正方形

## 问题描述

[221. 最大正方形 - 力扣（LeetCode）](https://leetcode-cn.com/problems/maximal-square/)

## 算法

### 解法一：bruteforce

#### 复杂度分析

时间复杂度： $O(m * n * min(m,n)^3)$
空间复杂度： $O(1)$

#### 解法一实现

##### 解法1: python

```
class Solution:
    def maximalSquare(self, matrix: List[List[str]]) -> int:
        n= len(matrix)
        if n == 0: return 0
        m = len(matrix[0])
        if m==0: return 0

        maxArea = 0
        for i in range(n):
            for j in range(m):
                for k in range(min(n-i, m-j)):
                    flag = True
                    for x in range(i, i+k+1):
                        if '0' in matrix[x][j:j+k+1]:
                            flag = False
                            break
                    if flag:
                        print(matrix[x][j:j+k+1])
                        maxArea = max(maxArea, (k+1)**2)
        return maxArea
```

### 解法2: 三维 dp

考虑如何表示一个正方形。最直接的是对角线的两个顶点来表示。如果用这个来 dp，则需要一个四维的 dp 表才能表示所有的正方形，其中 dp表的元素 dp[x1][y1][x2][y2] 表示以 (x1, y1) 和 (x2, y2) 分别为左上角顶点和右上角顶点的正方形。

这种方法的复杂度会到 $O(m^2n^2)$。

考虑压缩空间。一个正方形可以用左上角顶点和边长表示。这是就可以用一个三维的 dp 表来表示所有正方形。 dp[i][j][k] = true 表示以 (i, j) 为左上角顶点，边长为 k+1 的正方形是全为1的正方形。

转移方程为

$$
dp[i][j][k] = dp[i][j][k-1] && dp[i+1][j][k-1] && dp[i][j+1][k-1] && dp[i+1][j+1][k-1]
$$

时间复杂度：$O(m * n * min(m,n))$ 三重循环，循环体用时为 $O(1)$
空间复杂度：$O(m * n * min(m,n))$ dp数组的大小

#### 解法2：实现

##### 解法2: c++

```cpp
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int nrow = matrix.size();
        if (!nrow) return 0;
        int ncol = matrix[0].size();
        if (!ncol) return 0;

        vector<vector<vector<int>>> dp(nrow, vector<vector<int>> (ncol, vector<int>(min(nrow, ncol), false)));
        int ret = 0; // ret 表示的是正方形的最大边长
        // 初始化
        for (int i=0; i<nrow; i++) 
        {
            for (int j=0; j<ncol; j++)
            {
                if (matrix[i][j]=='1') 
                {
                    if (ret==0) ret = 1;
                    dp[i][j][0] = true;
                    
                }
            }
        }
        if (!ret) return 0;
        for (int k=1; k<min(nrow, ncol); k++) 
        {
            for (int i=0; i < nrow-k; i++) 
            {
                for (int j=0; j < ncol-k; j++) 
                {
                    dp[i][j][k] = dp[i][j][k-1] && dp[i+1][j][k-1] && dp[i][j+1][k-1] && dp[i+1][j+1][k-1];
                    if (dp[i][j][k]) ret = max(ret, k + 1);
                 }
            }
        }
        return ret * ret; // 返回最大面积
    }
};
```

### 解法3: 二维dp

上面的三维 dp 还是有可以压缩的地方。

解法2中，我们利用正方形左上角的顶点坐标 (x, y) 和 k 三个数就可以表示 matrix 中出现的**任意一个**正方形。
但是，实际上我们不需要**任意一个**正方形的结果，我们只需要以某个点为右下角顶点的最大的正方形的结果。

而本题的也可以用 dp[i][j] 来表示 **以 (i,j) 为右下角顶点的最大正方形的边长**。和解法2

转移方程：

$$
dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
$$

#### 解法3:复杂度分析

时间复杂度：$O(n*m)$
空间复杂度： $O(n*m)$

#### 解法3:实现

##### 解法3: c++

```cpp
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int nrow = matrix.size();
        if (!nrow) return 0;
        int ncol = matrix[0].size();
        if (!ncol) return 0;

        int ret = 0; // 最大正方形的边长
        vector<vector<int>> dp (nrow, vector<int>(ncol));
        for (int i=0; i<nrow; i++) 
        {
            dp[i][0] = matrix[i][0]== '1';
            ret = max(ret, dp[i][0]);
        }
        for (int j=0; j<ncol; j++) 
        {
            dp[0][j] = matrix[0][j] == '1';
            ret = max(ret, dp[0][j]);
        }
        
        for (int i=1; i < nrow; i++)
        {
            for (int j=1; j< ncol; j++) 
            {
                if (matrix[i][j] == '1')
                {
                    dp[i][j] = 1 + min(min(dp[i-1][j-1], dp[i][j-1]), dp[i-1][j]);  
                    ret = max(ret, dp[i][j]);
                }
            }
        }
        return ret * ret;
    }
};
```