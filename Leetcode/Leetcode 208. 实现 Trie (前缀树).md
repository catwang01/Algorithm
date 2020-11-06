[toc]

# Leetcode 208. 实现 Trie (前缀树)

## 问题描述

[208. 实现 Trie (前缀树) - 力扣（LeetCode）](https://leetcode-cn.com/problems/implement-trie-prefix-tree/)


## 算法

### 解法

#### 实现1: 使用 hashtab 实现

##### 解法1: python

```
class Node:
    def __init__(self, val):
        self.child = {}
        self.val = val
        self.isword = False

class Trie:

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.root = Node('')

    def insert(self, word: str) -> None:
        """
        Inserts a word into the trie.
        """
        if word == "": return
        node = self.root
        for ch in word:
            if ch not in node.child:
                node.child[ch] = Node(ch)
            node = node.child[ch]
        node.isword = True

    def search(self, word: str) -> bool:
        """
        Returns if the word is in the trie.
        """
        if word == "": return False
        node = self.root
        for ch in word:
            if ch in node.child:
                node = node.child[ch]
            else:
                return False
        return node.isword
            

    def startsWith(self, prefix: str) -> bool:
        """
        Returns if there is any word in the trie that starts with the given prefix.
        """
        if prefix == "": return True
        node = self.root
        for ch in prefix:
            if ch in node.child:
                node = node.child[ch]
            else:
                return False
        return True
```