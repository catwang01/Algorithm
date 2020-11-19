[toc]


# Leetcode 剑指 Offer 46. 把数字翻译成字符串

## 问题描述

[剑指 Offer 46. 把数字翻译成字符串 - 力扣（LeetCode）](https://leetcode-cn.com/problems/ba-shu-zi-fan-yi-cheng-zi-fu-chuan-lcof/)

## 算法


这个问题类似于 

[91. 解码方法 - 力扣（LeetCode）](https://leetcode-cn.com/problems/decode-ways/)

### 解法1：dp

dp 的思路是很清晰的，这里从 [ 1 ] 和 [ 2 ] 中挑出一些思考，可以从别的角度提供一些思考。

翻译 2163 可以分解成：翻译 2 和剩下的 163 、翻译 21 和剩下的 63

*   每次都有 2 种选择：翻译 1 个数、翻译 2 个数，但有的两位数没有对应的字母，只能翻译 1 个数，只有 1 种选择。
*   指针从左往右扫描，可以画出下面的递归树，2 种选择对应了 2 个分支，1 种选择对应 1 个分支。
*   当指针到达边界或越界，都返回 1 ，使得标记 △△△ 的分支返回 0 ，是一条死支。

![image.png](https://pic.leetcode-cn.com/f79e01824ed5315462d76c3d4de898eaccf081ee25a7c78c4320dd0a8e569f94-image.png)

#### 解法1: 实现


```
class Solution:
    def translateNum(self, num: int) -> int:
        s = str(num)
        n = len(s)
        dp = [0] * n
        dp[0] = 1
        for i in range(1, n):
            dp[i] += dp[i-1]
            if 10 <= int(s[i-1:i+1]) <= 25:
                if i - 2 >= 0:
                    dp[i] += dp[i-2]
                else:
                    dp[i] += 1
        return dp[n-1]
```

# References
1. [『手画图解』递归>记忆化递归>动态规划>降维优化 - 把数字翻译成字符串 - 力扣（LeetCode）](https://leetcode-cn.com/problems/ba-shu-zi-fan-yi-cheng-zi-fu-chuan-lcof/solution/shou-hui-tu-jie-dfsdi-gui-ji-yi-hua-di-gui-dong-ta/)
2. [【把数字翻译成字符串】：回溯，动态规划 - 把数字翻译成字符串 - 力扣（LeetCode）](https://leetcode-cn.com/problems/ba-shu-zi-fan-yi-cheng-zi-fu-chuan-lcof/solution/ba-shu-zi-fan-yi-cheng-zi-fu-chuan-hui-su-dong-tai/)