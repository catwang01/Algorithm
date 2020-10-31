[toc]

# Leetcode 1143. 最长公共子序列

## 问题描述

[1143. 最长公共子序列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/longest-common-subsequence/submissions/)

## 算法

### 解法一：动态规划

设 n = text1.size(), m = text2.size()，则复杂度分析如下：

时间复杂度：$O(mn)$
空间复杂度：$O(mn)$

1.定义状态
动态规划主要要明确 dp 表所代表的含义。这里我们用 dp[i][j] 表示 text1[:i] 和 text[:j] 的最长公共子序列。由些可以得到 i 的范围是 [0, n]， j 的范围是 [0, m]

2. 转移方程。

    1. 如果 text1[i-1] == text2[j-1]，说明 text1[:i] 和 text2[:j] 的末尾元素相同。那么最长公共子序列为去掉末尾元素后剩余元素的最长公共子序列，即`dp[i][j] = 1 + dp[i-1][j-1]`
    2. 如果 text1[i-1] != text2[j-1]，这种情况下，相当于在 text1[:i-1] 和 text2[:j-1] 的基础上分别在末尾添加了 1 个元素 text1[i-1] 和 text2[j-1]，这两个元素虽然不相同，但是 text1[i-1] 可能和 text2[:j-1] 中的元素相同，这转换为了求 text1[:i] 和 text2[:j-1] 的最长公共子序列，即求 dp[i][j-1]；同理，也要考虑 dp[i-1][j]。此时，转移方程为 `dp[i][j] = max(dp[i][j-1], dp[i-1][j])`

综上，转移方程为

$$
dp[i][j] =
\begin{cases}
dp[i-1][j-1] + 1, \quad A[i-1]==B[j-]1\\
max(dp[i][j-1],dp[i-1][j])  \quad A[i-1] == B[j-1] 
\end{cases}
$$

##### 解法1: c++

```
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n1 = text1.size(), n2 = text2.size();
        // dp[i][j] 表示 text1[:i] 和 text[:j] 的最长公共子序列
        // 0<= i <= text1.size() 0<= j <= text2.size()
        vector<vector<int>> dp(n1+1, vector<int>(n2+1, 0));

        // dp[0][j] 和 dp[i][0] 初始化为0
        for (int i=1; i<=n1; i++)
        {
            for (int j=1; j<=n2; j++)
            {
                if (text1[i-1] == text2[j-1])
                    dp[i][j] = dp[i-1][j-1] + 1;
                else 
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        return dp[n1][n2];
    }
};
```

### 解法一空间优化

#### 对滚动数组的处理值得参考

由于dp方程更新过程中只用到了左上、左、上三个位置的元素，因此可以考虑使用滚动数组进行空间优化。


![6151ced2e62eef0260105a4bdb8a6941.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p10107)


1. 由于在计算 dp[i][j-1] 时 dp[i-1][j-1] 在滚动数组中已经被 dp[i][j-1] 覆盖了（它们都位于 dp[j-1]处），因此需要再加一个元素保存 dp[i-1][j-1]
2. 由于不需要 n x m 维的数组只需要 m 维的数组，因此不妨再将 m 取成 min(n,m)，这样可以最小化额外空间。

时间复杂度： $O(mn)$
空间复杂度： $O(min(n,m))$

#### 解法一空间优化python实现

```
class Solution:
    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        if len(text1) > len(text2):
            A, B = text1, text2
        else:
            A, B = text2, text1
        # m 对应 B 的长度，B是长度较小的数组
        n, m = len(A), len(B)
        dp = [0] * (m+1)
        max_len = 0
        prev = 0
        for i in range(1, n+1):
            prev = dp[0]
            for j in range(1, m+1):
                tmp = dp[j]
                if A[i-1] == B[j-1]:
                    dp[j] = prev + 1
                else:
                    dp[j] = max(dp[j], dp[j-1])
                prev = tmp
                max_len = max(max_len, dp[j])
        return max_len
```