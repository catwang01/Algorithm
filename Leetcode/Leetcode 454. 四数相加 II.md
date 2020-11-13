[toc]

# Leetcode 454. 四数相加 II

## 问题描述

[454. 四数相加 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/4sum-ii/submissions/)

## 算法

### 解法1：hash 表法

将 A[i] + B[j] 的值放入 hashtab 中，然后检查 - (C[k] + D[l]) 是否在表中

时间复杂度： $O(n^2)$
空间复杂度： $O(n^2)$

##### 解法1: 实现：python

```
from collections import defaultdict
class Solution:
    def fourSumCount(self, A: List[int], B: List[int], C: List[int], D: List[int]) -> int:
        n = len(A)
        hashtab = defaultdict(int)
        for i in range(n):
            for j in range(n):
                hashtab[A[i] + B[j]] = hashtab[A[i] + B[j]] + 1
        ret = 0
        for k in range(n):
            for l in range(n):
                ret += hashtab[ - C[k] - D[l] ]
        return ret
```

### 解法2: 双指针

  
和 [18. 四数之和 - 力扣（LeetCode）](https://leetcode-cn.com/problems/4sum/) 相比，这道题并不适合双指针。

[18. 四数之和 - 力扣（LeetCode）](https://leetcode-cn.com/problems/4sum/) 要求不计算重复的数字，可以用双指针用来排除不可能的情况，而这个需要计算重复的数字，直接套用双指针可能会漏解。

关键问题是在 A[i] + B[j] + C[k] + D[j] == 0 是如何移动指针。
对于 [18. 四数之和 - 力扣（LeetCode）](https://leetcode-cn.com/problems/4sum/) 来说，这种情况可以 k += 1，也可以 j -= 1。

但是对于这道题来说，不能这样，因为这样会漏掉解。比如

```
A -1 1
B -1 1
C 1 2
D 1 1
```

假设此时我们的 i = j = k = 0, l = 0，此时有 `A[i] + B[j] + C[k] + D[j] == 0`，假如我们这里随便将 k += 1，此时 i = j = 0, l = 1, k = 1,
`A[i] + B[j] + C[k] + D[j] == 1`。这时，我们漏掉了 `i = j =0, k = l = 0` 这种情况。因为 D[0] = D[1]，D[1] 可以构成解，D[0] 也可以，但是我们用过移动 k，将 D[0] 这种情况漏掉了。

同理，当 `A[i] + B[j] + C[k] + D[j] == 0` 时也不能简单的 `l -= 1`。

我们可以这样做：

1. 累计结果
为了计算重复的，我们可以用四个 hashtab 分别来统计每个数组中每个数字都重复了多少次，在得到 `A[i] + B[j] + C[k] + D[j] == 1` 时，我们每次都 `ret += map_A[A[i]] * map_B[B[j]] * map_C[C[k]] * map_D[D[l]]`

2. 更新指针
我们通过 hashtab 来计算重复的结果，那么我们在更新指针的时候就不需要考虑重复的情况了。也就是，我们希望我们的 k += 1 这个操作可以自动忽略重复的值，我们可以用一个函数 next_larger 来实现这个功能，这个函数的定义如下。

```
def next_larger(nums, k):
    whkle k + 1 < len(nums) and nums[k+1] == nums[k]:
        k += 1
    k += 1
    return k
```

注意到，函数的功能是在 nums[k+1:len(nums)] 中寻找最小的 j 满足 `nums[k] < nums[j]`，考虑到 nums[k+1:len(nums)] 是有序的，我们可以用二分法来实现这个功能

```
def next_bigger(nums, k):
    # min(nums[k] < nums[j])
    low = k + 1
    high = len(nums) # [low, high)
    if high - low <= 0: return high

    # 注意这种情况很容易漏掉
    # 即 nums[i] = nums[i+1] = ... = nums[len(nums)-1] 的情况
    if nums[high-1] == nums[k]: return high

    while high - low > 2:
        mid = (low + high) // 2
        if nums[k] < nums[mid]:
            high = mid + 1
        else:
            low = mid + 1
    if nums[k] < nums[low]:
        return low
    return high - 1
```




##### 解法2: 实现：python 超时

```
class Solution:
    def fourSumCount(self, A: List[int], B: List[int], C: List[int], D: List[int]) -> int:
        n = len(A)
        A.sort()
        B.sort()
        C.sort()
        D.sort()
        map_A = Counter(A)
        map_B = Counter(B)
        map_C = Counter(C)
        map_D = Counter(D)
        ret = 0

        def next_bigger(nums, k):
            # min(nums[k] < nums[j])
            low = k + 1
            high = len(nums) # [low, high)
            if high - low <= 0: return high
            if nums[high-1] == nums[k]: return high

            while high - low > 2:
                mid = (low + high) // 2
                if nums[k] < nums[mid]:
                    high = mid + 1
                else:
                    low = mid + 1
            if nums[k] < nums[low]:
                return low
            return high - 1
        
        def next_smaller(nums, l):
            # max(nums[j] < nums[l])
            low = 0
            high = l # [low, high)
            if high - low <= 0: return -1
            if nums[low] == nums[l]: return -1

            while high - low > 2:
                mid = (low + high) // 2
                if nums[mid] < nums[l]:
                    low = mid
                else:
                    high = mid
            if nums[high-1] < nums[l]:
                return high - 1
            return low

        i = 0
        while i < n:
            j = 0
            while j < n:
                k, l = 0, n - 1
                while k < n and l >= 0:
                    s = A[i] + B[j] + C[k] + D[l]
                    if s == 0:
                        ret += map_A[A[i]] * map_B[B[j]] * map_C[C[k]] * map_D[D[l]]
                        k = next_bigger(C, k)
                        l = next_smaller(D, l)
                    elif s < 0:
                        k = next_bigger(C, k)
                    else:
                        l = next_smaller(D, l)
                j = next_bigger(B, j)
            i = next_bigger(A, i)
        return ret
```