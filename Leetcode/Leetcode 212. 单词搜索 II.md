[toc]

# Leetcode 212. 单词搜索 II

## 问题描述

## 算法

### 解法1: 回溯 + trie 剪枝

这道题使用回溯法来解决。考虑使用 trie 来剪枝，因为 trie 可以快速判断一个字符串的前缀是否在字典中，如果不在，那么这个字符串就不可能构成解，直接可以减去。

同时，由于在回溯的过程中可能出现重复的字符串，我们需要考虑去重。一个最简单的是先用 set 来保存结果，最后返回时转化为 list。

这里考虑更好的一种去重方法，我们给 trie 添加删除操作，每往结果集中添加一个单词时，就删除 trie 中对应的这个单词。这里使用 count 来计数，当节点的 count 为0 时才会被删除。

这里需要注意，每删除一个单词是需要修改 isword 为 False！

##### 解法1: 实现：python

```
class Node:
    def __init__(self, val):
        self.next = {}
        self.val = val
        self.isword = False
        self.count = 0

# -1 not a prefix
# 0 a prefix but not a word
# 1 a prefix and a word
NOT_A_PREFIX, PREFIX, WORD = -1, 0, 1

class Trie:
    def __init__(self):
        self.root = Node("")

    def add(self, word):
        node = self.root
        for ch in word:
            if ch not in node.next:
                node.next[ch] = Node(ch)
            node.next[ch].count += 1
            node = node.next[ch]
        node.isword = True

    def hasPrefix(self, word):
        node = self.root
        for ch in word:
            if ch not in node.next:
                return NOT_A_PREFIX
            else:
                node = node.next[ch]
        return WORD if node.isword else PREFIX
    
    def delete(self, word):
        node = self.root
        for ch in word:
            node.next[ch].count -= 1
            if node.next[ch].count == 0:
                del node.next[ch]
                return
            else:
                node = node.next[ch]
        node.isword = False # 这个不能忘记！否则很难debug

        def __repr__(self):
            return self.root

class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        if len(board) == 0 or len(board[0])==0 or len(words) == 0:
            return []

        nrow, ncol = len(board), len(board[0])

        trie = Trie()
        for word in words:
            trie.add(word)

        ret = []
        directions = [[0, 1], [0, -1], [1, 0], [-1, 0]]
        seen = [[0] * ncol for i in range(nrow)]
        
        def dfs(i, j, curword): # curword 不包含于 board[i][j]
            # print(curword)
            nonlocal nrow, ncol

            curword += board[i][j]

            status = trie.hasPrefix(curword)
            if status == NOT_A_PREFIX:
                return
            elif status == WORD:
                ret.append(curword)
                trie.delete(curword)

            seen[i][j] = 1
            for dx, dy in directions:
                x, y = i + dx, j + dy
                if 0<= x < nrow and 0 <= y < ncol and seen[x][y] == 0:
                    dfs(x, y, curword)
            seen[i][j] = 0

        for i in range(nrow):
            for j in range(ncol):
                dfs(i, j, "")
        return ret
```
