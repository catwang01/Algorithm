[toc]

# Leetcode 211. 添加与搜索单词 - 数据结构设计

## 问题描述

[211. 添加与搜索单词 - 数据结构设计 - 力扣（LeetCode）](https://leetcode-cn.com/problems/design-add-and-search-words-data-structure/)

## 算法

### 解法1: trie

主要就是 search。需要实现通配符功能。如果没有通配符功能，每一层匹配的最多只有一个匹配。如果有通配符功能，每一层可能会有多个匹配，这时我们可以使用 bfs 遍历，保存每层的多个匹配结果。

##### 解法1: 实现：python

```
class Node:
    def __init__(self, val):
        self.val = val
        self.next = {}
        self.isword = False

class WordDictionary:

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.root = Node("")


    def addWord(self, word: str) -> None:
        """
        Adds a word into the data structure.
        """
        node = self.root
        for ch in word:
            if ch not in node.next:
                node.next[ch] = Node(ch)
            node = node.next[ch]
        node.isword = True

    def search(self, word: str) -> bool:
        """
        Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter.
        """
        q = deque()
        q.append(self.root)
        i = -1 # i 表示 node 的下一层节点匹配的字符的 idx
        while len(q):
            i += 1 
            levelsize = len(q)
            for _ in range(levelsize):
                node = q.popleft()
                if i == len(word) and node.isword:
                    return True
                for nextnode in node.next.values():
                    if i == len(word):  # 这里说明之前没有 i == len(word) 时没有返回
                                        # 说明 node.isword=False
                        continue
                    if nextnode.val == word[i] or word[i] == '.':
                        q.append(nextnode)
        return False 
```