

[toc]

# Leetcode 48. 旋转图像 

## 问题描述

[48. 旋转图像 - 力扣（LeetCode）](https://leetcode-cn.com/problems/rotate-image/)
[面试题 01.07. 旋转矩阵 - 力扣（LeetCode）](https://leetcode-cn.com/problems/rotate-matrix-lcci/)

## 算法

### 解法一

![80d835b78592ddc2c0ee274425365728.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p12400)

#### 解法一实现

##### 解法一：python


```
class Solution:
    def rotate(self, matrix: List[List[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """
        n = len(matrix)

        def swap(x1, y1, x2, y2):
            matrix[x1][y1], matrix[x2][y2] = matrix[x2][y2], matrix[x1][y1]
        
        def helper(x1, x2, y1, y2):
            if x1 >= x2: return
            # (x1+i, y2)->(x1, y1+i)->(x2-i, y1)->(x2, y2-i)
            for i in range(x2-x1):
                swap(x1+i, y2, x1, y1+i)
                swap(x1, y1+i, x2-i, y1)
                swap(x2-i, y1, x2, y2-i)

            helper(x1+1, x2-1, y1+1, y2-1)
        
        helper(0, n-1, 0, n-1)
```

##### 解法1:c++

```
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        rotateRange(0, matrix.size()-1, matrix);
    }
    void rotateRange(int i, int j, vector<vector<int>>&matrix) {
        if (i>=j) return;
        for (int k=i+1; k<=j; k++) 
        {
         swap(matrix[k][j], matrix[i][k]);
         swap(matrix[i][k], matrix[i+j-k][i]);
         swap(matrix[k][i], matrix[j][k]);
        }
        rotateRange(i+1, j-1, matrix);
     }
};
```
