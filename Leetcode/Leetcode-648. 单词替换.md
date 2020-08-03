
[toc]

# Leetcode 648. 单词替换

## 问题描述

[648. 单词替换 - 力扣（LeetCode）](https://leetcode-cn.com/problems/replace-words/)

## 算法

### 解法1: 前缀树

#### 解法1: 实现1

##### 解法1: python

```
class Solution:
def replaceWords(self, d: List[str], sentence: str) -> str:
    trie = Trie()
    for prefix in d:
        trie.insert(prefix)

    split_sentence = sentence.split()
    for i in range(len(split_sentence)):
        ret = trie.prefix(split_sentence[i])
        if ret != "":
            split_sentence[i] = ret
    return " ".join(split_sentence)


class Node:
def __init__(self, val):
    self.next = {}
    self.isword = False
    self.val = val

class Trie:
def __init__(self):
    self.root = Node("")

def insert(self, word):
    n = len(word)
    node = self.root
    for i in range(n):
        if word[i] not in node.next:
            node.next[word[i]] = Node(word[i])
        if i == n - 1:
            node.next[word[i]].isword = True
        node = node.next[word[i]]

def prefix(self, word):
    n = len(word)
    node = self.root
    for i in range(n):
        if word[i] not in node.next:
            return ""
        else:
            if node.next[word[i]].isword:
                return word[:i+1]
        node = node.next[word[i]]
    return ""
```



