[toc]


# Leetcode 1375. 灯泡开关 III

## 问题描述

[1375. 灯泡开关 III - 力扣（LeetCode）](https://leetcode-cn.com/problems/bulb-switcher-iii/)

## 算法

### 解法1：双指针


假设当前亮着的最大的灯泡的编号为 j。我们需要达到这样一个效果

如果点亮灯泡 light[k] 之后，[1,...,j] 这些灯泡都亮着的话，那么计数就加 1。

我们用一个指针 i 来表示 [1, i) 上亮着的灯泡。当我们每点亮一个灯泡时，做下面几件事情

1. 更新亮着的最大的灯泡编号 j
2. 检查 i 指针是否可以移动，如果可以移动，那么就移动 i 指针直到不能移动为止。3. 判断 `i - 1 == j` 是否成立，成立的话，相当于 `[1, ..., i) = [1, ..., j]` 的灯泡都亮，此时计数加 1. 

时间复杂度： $O(n)$，因为 i, j 最多移动 n 次
空间复杂度： $O(n)$，isopen 数组的开销

##### 解法1: 实现： python

```
class Solution:
def numTimesAllBlue(self, light: List[int]) -> int:
    n = len(light)
    # [1, i) 蓝色的
    # j 表示亮着的灯泡的最大的编号
    isopen = [0] * (n + 1)# isopen[0] 是对齐的
    i, j = 1, 0
    ret = 0
    for k in range(n):
        isopen[light[k]] = 1 # 点亮灯泡
        j = max(light[k], j) # 更新 j
        while i < n + 1 and isopen[i] == 1: # 移动 i 指针
            i += 1
        if i - 1 == j:
            ret += 1
    return ret
```
                
### 解法2: 记录最大值

根据题意，只需要当前亮的编号最大的灯泡编号等于亮的灯泡的数量即可。而由于第 k 时刻打开灯泡后，一定有 k + 1 个灯泡是亮着的，我们值需要记录每个时刻的最大值，然后是判断 `j == max(light[k], j)`，如果等号成立，计数加 1。

##### 解法2: 实现：python

```
class Solution:
    def numTimesAllBlue(self, light: List[int]) -> int:
        n = len(light)
        # [1, i) 蓝色的
        # j 表示最大的
        j = 0
        ret = 0
        for k in range(n):
            j = max(light[k], j)
            if j == k + 1:
                ret += 1
        return ret
```