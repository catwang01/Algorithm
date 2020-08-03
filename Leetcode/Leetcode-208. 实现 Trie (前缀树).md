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
    def __init__(self):
        self.isword = False
        self.next = {}

class Trie:

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.root = Node()


    def insert(self, word: str) -> None:
        """
        Inserts a word into the trie.
        """
        n = len(word)
        node = self.root
        for i in range(n):
            if word[i] not in node.next:
                node.next[word[i]] = Node()
            if i == n - 1:
                node.next[word[i]].isword = True
            node = node.next[word[i]]
            

    def search(self, word: str) -> bool:
        """
        Returns if the word is in the trie.
        """
        n = len(word)
        node = self.root
        for i in range(n):
            if word[i] not in node.next:
                return False
            if i == n - 1:
                return node.next[word[i]].isword
            node = node.next[word[i]]

    def startsWith(self, prefix: str) -> bool:
        """
        Returns if there is any word in the trie that starts with the given prefix.
        """
        n = len(prefix)
        node = self.root
        for i in range(n):
            if prefix[i] not in node.next:
                return False
            node = node.next[prefix[i]]
        return True
```