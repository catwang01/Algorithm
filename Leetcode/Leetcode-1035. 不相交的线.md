[toc]

# Leetcode 1035. 不相交的线

## 问题描述

[1035. 不相交的线 - 力扣（LeetCode）](https://leetcode-cn.com/problems/uncrossed-lines/)

## 算法

### 解法1: 最长公共子序列

此题实际上就是 [1143. 最长公共子序列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/longest-common-subsequence/)

#### 解法1:实现

##### 解法1: c++

```
class Solution {
public:
    int maxUncrossedLines(vector<int>& A, vector<int>& B) {
        int n1 = A.size(), n2 = B.size();
        // dp[i][j] 表示 A[:i] B[:j] 的最长公共子序列
        // i in [0, n1] j in [0, n2]
        vector<vector<int>> dp(n1+1, vector<int>(n2+1));
        // dp[0][j] 和 dp[i][0] 已被自己初始化

        for (int i=1; i<=n1; i++)
        {
            for(int j=1; j<=n2; j++)
            {
                if (A[i-1]==B[j-1])
                {
                    dp[i][j] = dp[i-1][j-1] + 1;
                }
                else
                {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return dp[n1][n2];
    }
};
```
