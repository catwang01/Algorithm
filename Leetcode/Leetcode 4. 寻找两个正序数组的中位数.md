[toc]

# Leetcode 4. 寻找两个正序数组的中位数

## 问题描述

[4. 寻找两个正序数组的中位数 - 力扣（LeetCode）](https://leetcode-cn.com/problems/median-of-two-sorted-arrays/)

## 算法

### 解法1: 二分法

由于要求时间复杂度为 $O(log (n+m))$，因此肯定是二分法没跑了。但是有一个问题：对什么二分？

要回答这个问题，首先要泛化原问题。原问题是求中位数，将其推广，其实上是求第 k 大数的问题。 我们定义这个求第 k 大数的函数为 findKthElement

由于中位数会根据 n + m 的奇偶不同而计算上有差别。一个可以统一奇偶的公式是 

```
median = findKthElement(( n + m + 1 ) // 2) + findKthElement(( n + m + 2 ) // 2) 
```

可以代入奇偶的情况测试，上述公式都是适用的。

比较常规的二分法是对数组长度进行二分。而这道题是对 k 进行二分。

二分法可以看做利用某种单调性对候选集合不断筛选的过程。那么首先我要明确候选集合。

#### 解法1: 正确性证明

参考自 [ 1 ]

1. 为什么这样做是正确的？

论证：

假设我们在 nums1 和 nums2 中分别找了一个 i，j。我们希望知道 i，j 在满足什么条件时可以排除一些值从而缩小范围。

```
[s1, ..., i, ..., e1]

[s2, ..., j, ..., e2]
```

假设 `nums1[i] > nums2[j]`，考虑 `[s2,...,j]` 这一段，它不大于 `[i, ..., e1]`，也不大于 `[j+1, ..., e2]`。
相当于这一段不大于 `e1 - i + 1 + e2 - j` 个数。

而不过某个数 x 是合并后的第 k 个数，那么它大于 `k-1` 个数，小于 `e1 - s1 + 1 + e2 - s2 + 1 - k` 个数。

```
....        x              ....
 ^          ^               ^
 |          |               |
 |          |               |
k-1 个数    1 个数    e1-s1+1+e2-s1+1-k 个数
```

因此如果 `[s2, ..., j]` 这一段不含 x，那么必须有

```
e1 - s1 + 1 + e2 - s2 + 1 - k < e1 - i + 1 + e2 - j
化简为
i - s1 + j - s2 < k - 1
```

而我们的更新规则为

```
i = s1 + min(len1, k // 2) - 1
j = s2 + min(len2, k // 2) - 1
```

接下来，我们只需要证明，在这个更新规则下， `i - s1 + j - s2 < k - 1` 必成立。我们先去掉上面的条件中的min

```
i = s1 + min(len1, k // 2) - 1 <= s1 + k // 2 - 1
j = s2 + min(len2, k // 2) - 1 <= s2 + k // 2 - 1
```

相当于我们将 i，j 放大了，我们要证明放大后的 i，j 仍然满足 `i - s1 + j - s2 < k - 1` 成立。

```
当 k = 2m 时
i - s1 + j - s2 = m -1 + m-1 = 2m-2 < 2m - 1 不等号成立
当 k = 2m+1 时
i - s1 + j - s2 = m-1 + m-1 = 2m-2 < 2m 不等号成立
```

即放大后的 i，j 都满足条件。因此放大之前的必然也满足条件。

2. 为什么这样做不会死循环？

论证：这样每次做会排除下列两个集合其中之一：

```
[s1, j] 或 [s2, i]
```

由于这两个集合有对称性，因此我们只看其中一个即可。

要达成死循环，当且仅当 `[s1,j]` 为空集，即 `j==s1-1`。

由于我们的更新条件，

```
j = s1 + min(len1, k//2)-1 ---> 只需说明 min(len1, k//2) > 0 恒成立。
```

k == 1 和 len==0 的情况，在两个特判时以及解决过了，因此 

```
k>=2 
且 
len>=1
```

因此 `min(len1, k//2) > 0` 恒成立。

上面的论证说到底只是证明，不能告诉我们为什么要这样做。这一点，还待之后考证。

#### 解法1: 复杂度分析

由于是对 k 二分，因此时间复杂度为 $O(log(k))$。

在这个题目中，$k = O(m + n)$，因此时间复杂度为 $O(log(m+m))$

#### 解法1:实现


##### 解法1： 实现1: python

```
class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        n1, n2 = len(nums1), len(nums2)
        if n1 + n2 & 1:
            return self.bisearch(nums1, nums2, 0, n1-1, 0, n2-1, (n1 + n2) // 2 + 1)
        else:
            left = self.bisearch(nums1, nums2, 0, n1-1, 0, n2-1, (n1 + n2) // 2) 
            right = self.bisearch(nums1, nums2, 0, n1-1, 0, n2-1, (n1 + n2) // 2 + 1)
            return (left + right) / 2

    def bisearch(self, nums1, nums2, s1, e1, s2, e2, k):
        len1, len2 = e1 - s1 + 1, e2 - s2 + 1
        # 保证 nums1 的长度小于 nums2，那么如果有一个数组长度为0，一定是 nums1 
        if len1 > len2: 
            return self.bisearch(nums2, nums1, s2, e2, s1, e1, k)
        if len1 <= 0: 
            return nums2[s2+k-1]

        if k==1: 
            return min(nums1[s1], nums2[s2]);
        # 开始二分
        i = s1 + min(len1, k//2) - 1
        j = s2 + min(len2, k//2) - 1
        if (nums1[i] > nums2[j]):
            return self.bisearch(nums1, nums2, s1, e1, j+1, e2, k-(j-s2+1))
        else:
            return self.bisearch(nums1, nums2, i+1, e1, s2, e2, k-(i-s1+1))
```

##### 解法1: python

```
class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        n1, n2 = len(nums1), len(nums2)
        k1 = (n1+n2+1)//2
        k2 = (n1 + n2 + 2) // 2
        return (
            self.findKthElement(0, min(n1, k1), nums1, 0, min(n2, k1), nums2, k1)
         + self.findKthElement(0, min(n1, k2), nums1, 0, min(n2, k2), nums2, k2)
        ) / 2

    def findKthElement(self, low1, high1, nums1, low2, high2, nums2, k):
        # candidate [low1, high1) [low2, high2)
        # 如果有某个集合为空
        if low1 >= high1:
            return nums2[low2+k-1]
        if low2 >= high2:
            return nums1[low1+k-1]
        # base case
        if k == 1:
            return min(nums1[low1], nums2[low2])
        mid = k // 2 # mid 表示前 mid 个元素
                    # 注意第 mid 个元素的下标为 low1 + mid - 1 和 low2 + mid - 1
                    # 有可能区间长度不足 mid 个元素，因此需要使用 min
        idx1 = min(low1+mid-1, high1-1) 
        idx2 = min(low2+mid-1, high2-1)
        if nums1[idx1] <= nums2[idx2]:
            n_excluded = idx1 - low1 + 1 # 排除的可能的解的个数
            return self.findKthElement(idx1+1, high1, nums1, low2, min(low2 + k - n_excluded, high2), nums2, k - n_excluded)
        else:
            n_excluded = idx2 - low2 + 1
            return self.findKthElement(low1, min(low1 + k - n_excluded, high1), nums1, idx2+1, high2, nums2, k - n_excluded)
```

# References
1. [九章算法 | 微软面试题：两个排序数组的中位数 - 知乎](https://zhuanlan.zhihu.com/p/210177588)
