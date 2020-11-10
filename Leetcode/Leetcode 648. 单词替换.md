
[toc]

# Leetcode 648. 单词替换

## 问题描述

[648. 单词替换 - 力扣（LeetCode）](https://leetcode-cn.com/problems/replace-words/)

## 算法

### 解法1: 前缀树

#### 解法1: 实现1

##### 解法1: python

```
class Node:
    def __init__(self, val):
        self.next = {}
        self.val = val
        self.isword = False

class Trie:

    def __init__(self):
        self.root = Node("")

    def add(self, word):
        node = self.root
        for ch in word:
            if ch not in node.next:
                node.next[ch] = Node(ch)
            node = node.next[ch]
        node.isword = True

    def findPrefix(self, word):
        # if find Prefix, return it; if not, return word
        node = self.root
        for i in range(len(word)):
            ch = word[i]
            if ch in node.next:
                node = node.next[ch]
                if node.isword: 
                    return word[:i+1]
            else: 
                return word
        return word
        

class Solution:
    def replaceWords(self, dictionary: List[str], sentence: str) -> str:
        words = sentence.split(" ")
        trie = Trie()
        for word in dictionary:
            trie.add(word)
    
        for i in range(len(words)):
            words[i] = trie.findPrefix(words[i])
        
        return " ".join(words)
```