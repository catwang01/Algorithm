[toc]

# Leetcode 791. 自定义字符串排序

## 问题描述
[791. 自定义字符串排序 - 力扣（LeetCode）](https://leetcode-cn.com/problems/custom-sort-string/)

## 算法

### 解法1: 调用内置函数

```
class Solution:
    def customSortString(self, S: str, T: str) -> str:
        ch2idx = {ch: i for i, ch in enumerate(S)}
        return "".join(sorted(T, key=lambda ch: ch2idx.get(ch, len(T))))
```

### 解法2: 手写归并排序

```
class Solution:
    def __init__(self):
        self.aux = None

    def customSortString(self, S: str, T: str) -> str:
        list_T = list(T)
        self.aux = list_T[:]
        ch2idx = {ch: i for i, ch in enumerate(S)}
        self.mergeSort(list_T, 0, len(list_T), ch2idx)
        return "".join(list_T)

    def mergeSort(self, A, low, high, ch2idx): # [i, j)
        if high - low <= 1: return
        mid = (low + high) // 2
        self.mergeSort(A, low, mid, ch2idx)
        self.mergeSort(A, mid, high, ch2idx)
        self.merge(A, low, mid, high, ch2idx)

    def merge(self, A, low, mid, high, ch2idx):
        i, j = low, mid
        k = low
        while i < mid and j < high:
            if ch2idx.get(A[i], -1) <= ch2idx.get(A[j], -1):
                self.aux[k] = A[i]
                k += 1
                i += 1
            else:
                self.aux[k] = A[j]
                k += 1
                j += 1
        while i < mid:
            self.aux[k] = A[i]
            k += 1
            i += 1
        while j < high:
            self.aux[k] = A[j]
            k += 1
            j += 1

        for k in range(low, high):
            A[k] = self.aux[k]
```