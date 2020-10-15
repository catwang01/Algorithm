[toc]

# Leetcode 118. 杨辉三角


## 问题描述

[118. 杨辉三角 - 力扣（LeetCode）](https://leetcode-cn.com/problems/pascals-triangle/)

## 算法

### 解法1: 找规律

找到规律就好了。

```
dp[i][j] = dp[i-1][j-1] + dp[i][j]
```

需要注意的是:

1. 边界值都为1。可以将数组初始化为 1，之后填值的时候只需要填非边界值就可以了
2. 第 i 行有 i+1 个数（i从0开始）

```
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ret;
        for(int i=0; i<numRows; i++) 
        {
            ret.push_back(vector<int>(i+1, 1)); // 第 i 行有 i+1 个数
            for (int j=1; j<i; j++)  // 去掉 j=1 和 j = i
            ret[i][j] = ret[i-1][j-1] + ret[i-1][j];
        }
        return ret;
    }
};
```

# References