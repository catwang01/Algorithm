[toc]

# Leetcode 720. 词典中最长的单词

## 问题描述

[720. 词典中最长的单词 - 力扣（LeetCode）](https://leetcode-cn.com/problems/longest-word-in-dictionary/)

## 算法

### 解法1: trie + bfs

#### 解法1:实现：python


```
class Node:
    def __init__(self, val):
        self.val = val
        self.next = [None] * 26
        self.isword = False
    
def ch2idx(ch):
    return ord(ch) - ord('a')

class Trie:
    def __init__(self):
        self.root = Node("")
    
    def add(self, word):
        node = self.root
        for ch in word:
            idx = ch2idx(ch)
            if not node.next[idx]:
                node.next[idx] = Node(ch)
            node = node.next[idx]
        node.isword = True

from collections import deque
class Solution:
    def longestWord(self, words: List[str]) -> str:
        trie = Trie()
        for word in words:
            trie.add(word)

        # 对 Trie 进行 bfs
        q = deque()
        q.append((trie.root, ""))
        level = -1
        while len(q):
            ret = q[0][1] # ret 实际上是根节点到最后一层第一个节点练成的路径所表示的单词    
                        # 如果无答案，则 ret 是空串
            level += 1
            levelsize = len(q)
            for _ in range(levelsize):
                node, curword = q.popleft()
                for nextnode in node.next: # 是单词的才继续往下搜索
                    if nextnode and nextnode.isword:
                        q.append((nextnode, curword + nextnode.val))
        return ret
```