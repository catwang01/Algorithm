[toc]

# Leetcode 5394. 对角线遍历 II

## 问题描述

[5394. 对角线遍历 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/diagonal-traverse-ii/)

## 算法

### 解法1: hashtab

由于同一个对角线上的元素的特点是行列下标之和相等。因此可以使用一个 hashtab 来保存行列坐标之和对应的值。

由于题目的对角线的方向是从下向上从左向右，因此在拼接时需要reverse一下。

#### 解法1:实现

##### 解法1: python

```
class Solution:
    def findDiagonalOrder(self, nums: List[List[int]]) -> List[int]:
        hashtab = dict()
        for i in range(len(nums)):
            for j in range(len(nums[i])):
                if i + j not in hashtab:
                    hashtab[i+j] = []
                hashtab[i+j].append(nums[i][j])
        ret = []
        for k, v in sorted(hashtab.items()): # 按照key排序
            ret.extend(reversed(v))
        return ret
```

