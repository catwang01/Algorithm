[toc]

# Leetcode 300. 最长上升子序列 （LIS）


## 问题描述

- leetcode: [300. 最长上升子序列](https://leetcode-cn.com/problems/longest-increasing-subsequence/solution/)


给定一个无序的整数数组，找到其中最长上升子序列的长度。

输入: [10,9,2,5,3,7,101,18]
输出: 4 
解释: 最长的上升子序列是 [2,3,7,101]，它的长度是 4。

注：
1. 这里的上升指严格上升。如 [1,1,1] 的最长上升子序列的长度为1，不是3
2. 只要求输出长度，不用输出具体的 最长上升子序列

## 算法

### 法一：动态规划

记序列为$s(1:n)$，设 $l(i)$ 表示
**以 $s(i)$ 为最后一位元素的所有上升子序列中最长的那个子序列的长度**，则 $s(1:n)$ 的最长上升子序列的长度为 $max_{1 \leq i \leq n}l(i)$

例如 $s(1:3)=[2,4,1]$

则 
1. 以 $s(1)=2$ 为最后一位的最长上升子序列为[1]，长度为1，故$l(1)=1$

2. 以 $s(2)=4$ 为最后一位的最长上升子序列为 [2，4]，长度为2，故 $l(2)=2$

3. 以 $s(3)=1$ 为最后一位的最长上升子序列为 [1]，长度为1，故 $l(3)=1$


转移方程为

![e557f4e05e7a3f0736f641691d2cd231.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p11158)


注意，这里的 $l(i)$ 的定义很巧妙，它不是子列 $s(1:i)$ 的最长上升子序列的长度。因为从 $i$ 添加一个元素到 $i+1$ 的过程实际上要与上升子序列的最后一位做比较。

而比较容易想到的定义是将 $l(i)$ 定义为 $s(1:i)$ 的最长上升子序列的长度，这种定义下问题不具有最优子结构性质，即 $i+1$ 情况下的解不一定是由 $i$ 情况下的解构成的。如：


- 时间复杂度： $O(n^2)$ 。有两个n重循环。
- 空间复杂度： $O(n)$ ，用了大小为 n 的向量 dp。

#### 解法一：实现


##### 解法一：python

```
class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        n = len(nums)
        if n <= 1: return n
        dp = [1] * n
        maxLen = 1
        for i in range(1, n):
            for j in range(i): # j=[0,...,i-1]
                if nums[j] < nums[i] and dp[i] < dp[j] + 1:
                    dp[i] = dp[j] + 1
            maxLen = max(maxLen, dp[i])
        return maxLen
```

##### 解法一：C++

```
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if (n<=1) return n;
        int maxLen = 1;
        vector<int> dp(n, 1);
        for (int i=1; i<n; i++) {
            for (int j=0; j<i; j++) {
                if (nums[j] < nums[i] && dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                }
            }
            maxLen = max(maxLen, dp[i]);
        }
        return maxLen;
    }
};
```


##### 解法一：scala

```
import scala.math.max
object Solution {
    def lengthOfLIS(nums: Array[Int]): Int = {
        // dp[i] 表示以i结尾的最长上升子序列的长度
        if (nums.length == 0) return 0
        var dp = new Array[Int](nums.length).map(x=>1)
        var maxLen = 1
        for (i <-0 until nums.length; j<- 0 until i) {
            if (nums(j) < nums(i) ) {
                dp(i) = max(dp(i), dp(j)+1)
                maxLen = max(dp(i), maxLen)
            }
        }
        maxLen
    }
}
```
