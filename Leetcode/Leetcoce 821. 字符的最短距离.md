[toc]

# Leetcoce 821. 字符的最短距离

## 问题描述

[821. 字符的最短距离 - 力扣（LeetCode）](https://leetcode-cn.com/problems/shortest-distance-to-a-character/)

## 算法

### 解法1: 多源 bfs 

如果将数组上每个位置看作一个节点，相邻两个位置看作是节点相连，那么饿这个实际上是一个多源 bfs 问题，从所有的 0 开始出发做层次遍历，节点所在的层数就是返回的值。

##### 解法1: 实现：python

```
from collections import deque

class Solution:
    def shortestToChar(self, S: str, C: str) -> List[int]:
        n  = len(S)
        SEEN, UNSEEN = -1, -2
        ret = [UNSEEN] * n
        q = deque()
        for i in range(n):
            if S[i] == C:
                q.append(i)
                ret[i] = SEEN
        level = -1
        while len(q):
            levelsize = len(q)
            level += 1
            for _ in range(levelsize):
                k = q.popleft()
                ret[k] = level
                if k - 1 >= 0 and ret[k - 1] == UNSEEN:
                    q.append(k-1)
                    ret[k-1] = SEEN
                if k+1 < n and ret[k + 1] == UNSEEN:
                    q.append(k+1)
                    ret[k+1] = SEEN
        return ret
```

### 解法2

##### 解法2:实现：python

```
class Solution:
    def shortestToChar(self, S: str, C: str) -> List[int]:

        n = len(S)
        ret = [float("inf")] * n

        last = -float("inf")
        for i in range(n):
            if S[i] == C:
                ret[i] = 0
                last = i
            else:
                ret[i] = i - last   # 当左边没有 C 时，需要让 i - last 不可能被选择
                                    # 因此 last 取 -float("inf")

        last = float("inf")
        for j in range(n-1, -1, -1):
            if S[j] == C:
                ret[j] = 0
                last = j
            else:
                ret[j] = min(last - j, ret[j])  # 当右边没有 C 是，需要让 last - j 不可能被选择
                                                # 因此 last 取 float("inf")
        return ret
```