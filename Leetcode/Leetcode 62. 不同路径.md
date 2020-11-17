
[toc]

# Leetcode 62. 不同路径

## 问题描述

[62. 不同路径 - 力扣（LeetCode）](https://leetcode-cn.com/problems/unique-paths/)

## 算法

### 解法一：dp1 从起点到终点


$$dp[i][j] = \{\text{从(1,1)出发到达(i,j)的路径数}\}$$
则有 
$$dp[i][j] = dp[i-1][j] + dp[i][j-1]$$

这样定义的好处是填表是正着填的不是倒着填的。

![96b816bfccbe9de211ac437182574aed.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p9974)


##### 解法1: 实现：c++

```
class Solution {
public:
    int uniquePaths(int m, int n) {
        if(n==1 || m==1) return 1;
        int dp[m+1][n+1] = {};
        int i,j;
        for (i=1;i<=m;i++) {
            for (j=1;j<=n; j++) {
                if ((i==1) && (j==1)) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
                }
            }
        }
        return dp[m][n];
    }
};
```

#### 解法1： 实现：python

```
class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        if m == 0 or n == 0: return 0
        dp = [[0] * n for i in range(m)]
        for i in range(m):
            dp[i][0] = 1
        for j in range(n):
            dp[0][j] = 1
        for i in range(1, m):
            for j in range(1, n):
                dp[i][j] = dp[i-1][j] + dp[i][j-1]
        return dp[m-1][n-1]      
```

### 解法2: dp2

另一种定义dp数组的方式是  
$$dp[i][j]= \{\text{从 (i,j) 点出发到达(m,n)的路径数}\}$$

则 
$$dp[i][j] = dp[i][j+1] + dp[i+1][j]$$

这种方法和第一种方式相比，填表要倒着填。这时i==0或j==0的元素只是为了对齐，不是边界条件。

![42b1eca8b6d0d96986f165d2eb7b704f.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p9973)


时间复杂度：$O(mn)$
空间复杂度：$O(mn)$

##### 解法2: 实现： c++

```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        if(n==1 || m==1) return 1;
        int dp[m+1][n+1];
        int i,j;
        for (i=1; i<m; i++) {
            dp[i][n] = 1;
        }
        for (j=1; j<n; j++) {
            dp[m][j] = 1;
        }
        for (i=m-1;i>=1;i--) {
            for (j=n-1;j>=1; j--) {
                dp[i][j] = dp[i+1][j] + dp[i][j+1];
            }
        }
        return dp[1][1];
    }
};
```

### 解法3：dp优化

以dp1为例


注意到，
$$dp[i][j] = dp[i-1][j] + dp[i][j-1]$$
中，`dp[i-1][j]` 在计算完 `dp[i][j]` 之后就用不到了，因此可以直接将 `dp[i][j]` 的值保存到 `dp[i-1][j]` 中。这样可以只有一个n个元素的一维数组来作dp数组，而非一个m*n的二维数组


![35d2d9b2331209dcee006d40a7f18a3c.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p9972)

时间复杂度：$O(mn)$
空间复杂度：$O(n)$

代码基本没有什么变化，就是把两个下标变成删掉一个变成一个下标了。

#### 解法3: 实现：c++

```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        if(n==1 || m==1) return 1;
        int dp[n+1] = {};
        int i,j;
        for (i=1;i<=m;i++) {
            for (j=1;j<=n; j++) {
                if ((i==1) && (j==1)) {
                    dp[j] = 1;
                } else {
                    dp[j] = dp[j] + dp[j-1];
                }
            }
        }
        return dp[n];
    }
};
```
