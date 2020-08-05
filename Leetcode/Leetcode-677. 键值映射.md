[toc]

# Leetcode 677. 键值映射

## 问题描述

[677. 键值映射 - 力扣（LeetCode）](https://leetcode-cn.com/problems/map-sum-pairs/)

## 算法

### 解法1: 前缀树

#### 解法1: 实现

##### 解法1: python

```
class Node:
    def __init__(self, val=None):
        self.next = {}
        self.val = val

class MapSum:

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.root = Node()

    def insert(self, key: str, val: int) -> None:
        node = self.root
        n = len(key)
        for i in range(n):
            if key[i] not in node.next:
                node.next[key[i]] = Node()
            node = node.next[key[i]]
        node.val = val

    def sum(self, prefix: str) -> int:
        n = len(prefix)
        node = self.root
        for i in range(n):
            if prefix[i] not in node.next:
                return 0
            node = node.next[prefix[i]]

        ret = 0
        def dfs(node):
            nonlocal ret
            if node.val:
                ret += node.val
            for nextnode in node.next.values():
                dfs(nextnode)

        dfs(node)
        return ret
```
