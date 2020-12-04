[toc]

# Leetcode 498. 对角线遍历

## 问题描述

## 算法

[498. 对角线遍历 - 力扣（LeetCode）](https://leetcode-cn.com/problems/diagonal-traverse/)

### 解法1：模拟

#### 解法1: 

对角线上的元素有一个特点，横纵坐标之和固定。假设横纵坐标为 i, j，那么 k = i + j 固定。

假设矩阵的行、列数分别为 nrow 和 ncol，那么 k 最大可以取到 `nrow - 1 +  ncol - 1 = nrow + ncol - 2`

因此 k 的遍历范围是 `[0, nrow + ncol - 1)`

我们还发现， k 为奇数时遍历方向从上往下（对应于横坐标从小到大），k 为偶数时从下往上（对应于横坐标从大到小）。

##### 解法1: 实现：

```
class Solution:
    def findDiagonalOrder(self, matrix: List[List[int]]) -> List[int]:
        ret = [] 
        if (len(matrix)==0 or len(matrix[0])==0): return ret
        nrow, ncol = len(matrix), len(matrix[0])
        for k in range(nrow + ncol - 1):
            if k & 1:
                for i in range(max(0, k - ncol + 1), min(k+1, nrow)): # 0 <= i < k+1
                    # 0 <= i < nrow 
                    # 0 <= k - i < ncol --> k - ncol < i <= k --> k - ncol + 1 <= i < k + 1
                    ret.append(matrix[i][k-i])
            else:
                for i in range(min(k, nrow-1), max(-1, k - ncol), -1): # -1 < i <= k
                    # 0 <= i < nrow --> -1 < i <= nrow - 1
                    #  0 <= k - i < ncol --> k - ncol < i <= k
                    ret.append(matrix[i][k-i])
        return ret
```

