
[toc]


# Leetcode 1027. 最长等差数列

## 问题描述

[1027. 最长等差数列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/longest-arithmetic-sequence/)

## 算法

### 解法一：bruteforce

由于等差数列的开头两项就可以确定一个等差数列，因此对于所有的 i，j组合，分别以 A[i], A[j] 为等差数列的前两项计算等差数列的长度，并维护最大值并更新即可。

时间复杂度： $O(n^3)$
空间复杂度： $O(1)$

#### 解法一bruteforce python 超时

![d353c5ee55db5e92999a97f80f401dfa.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p10646)

```
class Solution:
    def longestArithSeqLength(self, A: List[int]) -> int:
        n = len(A)
        if n <= 2: return n
        ret = 2

        def getLength(i, j):
            d = A[j] - A[i]
            length = 2
            i = j
            j = i + 1
            while j < len(A):
                if A[j] - A[i] == d:
                    length += 1
                    i = j
                j += 1
            return length

        for i in range(n):
            for j in range(i+1, n):
                ret = max(ret, getLength(i, j))
        return ret
```

### 解法二：递归

时间复杂度： $O(n^3)$
空间复杂度： $O(1)$

将上面的 getLen 修改为递归

#### 解法二：递归 python

![6bf86406a44a80b28eb54bc66c4bc9f1.png](evernotecid://7C71FA3B-B5E0-41C4-AF1B-AB35446A037A/appyinxiangcom/22483756/ENResource/p11649)

```
class Solution:
    def longestArithSeqLength(self, A: List[int]) -> int:
        n = len(A)
        def getLen(i, j): # 计算开头两项为 A[i], A[j]的等差数列的长度
            k = j + 1
            while k < n:
                if A[k] == A[j] + A[j] - A[i]:
                    break
                k += 1
            if k == n:
                return 2
            else:
                return getLen(j, k) + 1

        maxLen = 2
        for i in range(n-1): # i=[0,...,n-2]
            for j in range(i+1, n): # j=[i+1, ..., n-1]
                maxLen = max(maxLen, getLen(i,j))
        return maxLen
```



### 解法二：递归 + 记忆化 

时间复杂度： $O(n^3)$
空间复杂度： $O(n^2)$

#### 解法二：递归 + 记忆化 python

```
class Solution:
    def longestArithSeqLength(self, A: List[int]) -> int:
        n = len(A)

        memo = {}
        def getLen(i, j): # 计算开头两项为 A[i], A[j]的等差数列的长度
            if (i,j) not in memo:
                k = j + 1
                while k < n:
                    if A[k] == A[j] + A[j] - A[i]:
                        break
                    k += 1
                if k == n:
                    memo[i,j] = 2
                else:
                    memo[i,j] = getLen(j, k) + 1
            return memo[i,j]
    
        maxLen = 2
        for i in range(n-2, -1, -1): # i=[0,...,n-2]
            for j in range(n-1, i, -1): # j=[i+1, ..., n-1]
                maxLen = max(maxLen, getLen(i,j))
        return maxLen
```

### 解法三：dp

将上面的记忆化递归修改为dp，用dict来保存dp table 而不是二维数组，因为二维数组中的一半元素是没有意义的（那些 i < j 的 dp[i,j]）

#### 解法三dp python

```
from collections import defaultdict
class Solution:
    def longestArithSeqLength(self, A: List[int]) -> int:
        n = len(A)

        dp = {}
        maxLen = 2
        for i in range(n-2, -1, -1): # i=[0,...,n-2]
            for j in range(n-1, i, -1): # j=[i+1, ..., n-1]
                k = j + 1
                while k < n:
                    if A[k] == A[j] + A[j] - A[i]:
                        break
                    k += 1
                if k == n:
                    dp[i,j] = 2
                else:
                    dp[i,j] = dp[j,k] + 1
                    maxLen = max(maxLen, dp[i,j])
        return maxLen
```

#### 解法3: 实现2:

定义 `dp[i][j]` 为以 `nums[i]`, `nums[j]` 结尾的最长等差序列的长度。则我们可以得到递推方程

```
dp[i][j] = 2
for k in range(i):
    if A[j] - A[i] == A[i] - A[k]:
        dp[i][j] = max(dp[i][j], dp[k][i] + 1)
```

这个递推方程还可以再优化一下。考虑重复子序列的情况，假设我们现在在计算 dp[i][j]，有 A[k1] 和 A[k2] 都满足 和 nums[i], nums[j] 构成等差序列，且满足 k1 < k2，那么我们应该选那个？

实际上，我们应该选 k2，因为在这种情况下，必有 `dp[k1][i] <= dp[k2][i]`。

如果等差序列的差不为零，那么 `dp[k1][i] == dp[k2][i]`
如果等差序列的差为0，那么可能出现 `dp[k1][i] < dp[k2][i]` 的情况。

因此我们不需要计算所有的 k，只需要从后向前，遇到第一个能够构成等差序列的 k 就可以 break 了

```
dp[i][j] = 2
for k in range(i-1, -1, -1):
    if A[j] - A[i] == A[i] - A[k]:
        dp[i][j] = max(dp[i][j], dp[k][i] + 1)
        break
```

##### 解法3: 实现2: python

```
class Solution:
    def longestArithSeqLength(self, A: List[int]) -> int:
        n = len(A)
        if n <= 2: return n
        ret = 2

        dp = [[2] * n for i in range(n)]
        for i in range(n):
            for j in range(i+1, n):
                for k in range(i-1, -1, -1):
                    if A[j] - A[i] == A[i] - A[k]:
                        dp[i][j] = max(dp[i][j], dp[k][i] + 1)
                ret = max(ret, dp[i][j])
        return ret
```

### 解法四：dp + hash

我们在之前的方法中，是通过遍历 [0,...,i] 的值来得到 k 的。其中，有许多数不满足等差序列的条件，我们根本没有必要遍历这些数。能不能只在那些可以形成等差数列的下标中寻找 k 呢？

当我们寻找 k 时，我们希望 `A[j] - A[i] == A[i] - A[k]`，相当于需要 k 满足：

```
A[k] = 2 * A[i] - A[j]
```

因此，我们可以将 A 中值和对应下标创建一个哈希表，这样我们就可以直接在这个哈希表中通过值来获取 k 的下标的。

但是，A 中的元素是可以重复的，因此我们的哈希表中的元素应该是一个 list，用来保存相同值的不同下标.


- 时间复杂度： $O(n^3)$
建立idxMap用时 $O(n)$，填 dp 表用了三个循环，因此时间为 $O(n^3)$

- 空间复杂度： $O(n^2)$ 
两个hash表，idxMap这个表大小为 $O(n)$， dp 这个表大小为 $O(n^2)$

#### 解法四：dp + hash python

```
from collections import defaultdict
class Solution:
    def longestArithSeqLength(self, A: List[int]) -> int:
        n = len(A)

        idxMap = defaultdict(list)
        for i in range(n):
            idxMap[A[i]].append(i)
    
        dp = defaultdict(lambda: 2)
        maxLen = 2
        for j in range(n-1, 0, -1): # j=[n-1, ..., 1]
            for i in range(j-1, -1, -1): # i = [j-1, ..., 0]
                target = A[j] + A[j] - A[i]
                for k in idxMap[target]:
                    if k > j:
                        dp[i,j] = dp[j,k] + 1
                        maxLen = max(maxLen, dp[i,j])
                        break
        return maxLen
```