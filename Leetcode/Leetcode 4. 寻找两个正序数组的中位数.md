[toc]

# Leetcode


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

#### 解法1:实现

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