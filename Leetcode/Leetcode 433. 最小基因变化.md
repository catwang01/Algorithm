[toc]

# Leetcode 433. 最小基因变化.md

## 问题描述

[433. 最小基因变化 - 力扣（LeetCode）](https://leetcode-cn.com/problems/minimum-genetic-mutation/)

## 算法


这个是所谓的 `状态图搜索问题`。可以将其转化为图然后进行 bfs 操作。

### 解法1: bfs


```
from collections import deque
# 定义节点
class Node:
    def __init__(self, s):
        self.s = s
        self.seen = False
        self.next = []

    def __eq__(self, other):
        return self.s == other.s

    @classmethod
    def isconnect(cls, node1, node2):
        ret = 0
        for i in range(8):
            if node1.s[i] != node2.s[i]:
                ret += 1
        return ret == 1

class Solution:
    def minMutation(self, start: str, end: str, bank: List[str]) -> int:
        # 初始化节点
        startNode = Node(start)
        endNode = Node(end)
        bankNodes = [Node(s) for s in bank]

        if endNode not in bankNodes:
            return -1
        
        # 这里是建图过程
        n = len(bankNodes)
        for i in range(n):
            for j in range(i+1, n):
                if Node.isconnect(bankNodes[i], bankNodes[j]):
                    bankNodes[i].next.append(bankNodes[j])
                    bankNodes[j].next.append(bankNodes[i])
        
        for i in range(n):
            if Node.isconnect(startNode, bankNodes[i]):
                bankNodes[i].next.append(startNode)
                startNode.next.append(bankNodes[i])
        
        # 以下是 bfs
        q = deque()
        q.append(startNode)
        startNode.seen = True
        changeTimes = -1

        while len(q):
            changeTimes += 1
            levelsize = len(q)
            for _ in range(levelsize):
                node = q.popleft()
                if node == endNode:
                    return changeTimes
                for nextnode in node.next:
                    if not nextnode.seen:
                        q.append(nextnode)
                        nextnode.seen = True
        return -1
```

# References

1. [Java单向广度优先搜索和双向广度优先搜索 - 最小基因变化 - 力扣（LeetCode）](https://leetcode-cn.com/problems/minimum-genetic-mutation/solution/javadan-xiang-yan-du-you-xian-sou-suo-he-shuang-xi/)