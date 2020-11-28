
[toc]

# Leetcode 30. 串联所有单词的子串

## 问题描述

[30. 串联所有单词的子串 - 力扣（LeetCode）](https://leetcode-cn.com/problems/substring-with-concatenation-of-all-words/)

给定一个字符串 **s **和一些长度相同的单词 **words。**找出 **s** 中恰好可以由 **words** 中所有单词串联形成的子串的起始位置。
注意子串要与 **words** 中的单词完全匹配，中间不能有其他字符，但不需要考虑 **words **中单词串联的顺序。

**示例 1：**

**输入：
  s =** "barfoothefoobarman",
 **words =** ["foo","bar"]
**输出：**`[0,9]`
**解释：**
从索引 0 和 9 开始的子串分别是 "barfoo" 和 "foobar" 。
输出的顺序不重要, [9,0] 也是有效答案。

**示例 2：**

**输入：
  s =** "wordgoodgoodgoodbestword",
 **words =** ["word","good","best","word"]
`**输出：**[]`


## 算法


### 解法一：bruteforce

计 len(s) = n, len(words) = m, wordLen = len(words[0]), k = wordLen * m


时间复杂度： $O(nm)$ for 循环运行了 n-k+1次，chech函数的时间复杂度为 $O(m)$
空间复杂度： $O(m)$ 对于每个 s[i:i+k] 都在 check 函数中建立了一个 counter，其大小为m



#### 解法一python

```
from collections import Counter
class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        n, m = len(s), len(words)
        if n==0 or m==0: return []
        wordLen = len(words[0])
        k = m * wordLen
    
        words = Counter(words)
    
        def check(string):
            splited = Counter(string[i*wordLen:(i+1)*wordLen] for i in range(m)) # 建立 splited 用时 $O(m)$
            return words == splited  # 判等用时 $O(m)$

        result = []
        for i in range(n-k+1):
            if check(s[i:i+k]):
                result.append(i)
        return result
```

### 解法一优化

解法一中的check函数的时间复杂度比较高，下面研究如何减少check的时间复杂度

可以用dict来记录words中的每个单词的出现次数

如果只用一个dict进行记录，由于单词是以 wordLen 为单位分割的，因此按照下面的方式

![91fe0bf5e2b1792cf6ed6d2b1b1ef58a.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p10511)

时间复杂度： $O(nm)$，虽然有两重循环
空间复杂度： $O(m)$

#### 解法一优化

```
from collections import Counter
class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        n, m = len(s), len(words)
        if n==0 or m==0: return []
        wordLen = len(words[0])
        k = m * wordLen
        if k > n: return []
        words = Counter(words)

        d, result = {}, []
        for i in range(wordLen):
            d.clear()
            for j in range(i, n-wordLen+1, wordLen):
                # 移动窗口，更新dicts
                last = s[j:j+wordLen]
                d[last] = d.get(last, 0) + 1
                if j >= i+k:
                    prev = s[j-k:j-k+wordLen] 
                    d[prev] -= 1
                    if d[prev] == 0:
                        del d[prev]
                if d == words: # 判断是否满足条件
                    result.append(j+wordLen-k)
        return result
```

### 解法一再优化

上面的过程中判断是否满足条件是通过需要 $O(n)$ 的时间复杂度，下面可以将其优化为 $O(1)$

引入 n_valid 表示满足条件的数的个数； n_needs 表示一共有多少个数需要满足条件，因此判断是否满足条件只需要 `n_valid == n_needs`，而 n_valid 在窗口移动时会更新。

#### 解法一再优化python

```
from collections import Counter

class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        n, m = len(s), len(words)
        if n==0 or m==0: return []
        wordLen = len(words[0])
        k = m * wordLen
        if k > n: return []
        words = Counter(words)
        n_needs = len(words)
        
        d, result = {}, []
        for i in range(wordLen):
            d.clear()
            n_valid = 0
            for j in range(i, n-wordLen+1, wordLen):
                # 移动窗口，更新dicts
                last = s[j:j+wordLen]
                d[last] = d.get(last, 0) + 1
                if last in words and d[last] == words[last]:
                    n_valid += 1
                if j >= i+k:
                    prev = s[j-k:j-k+wordLen] 
                    if d[prev]==words[prev]:
                        n_valid -= 1
                    d[prev] -= 1
                # 判断是否满足条件
                if n_valid == n_needs:
                    result.append(j+wordLen-k)
        return result
```

### 解法2：固定窗宽滑动窗口

注意 words 中的所有单词是等长的，长度为 len(words[0])。 为了让之前的单词重复被使用，我们可以考虑以 len(words[0]) 为单位移动。

这样可能会导致只有某些特定的位置会被考虑到。因此我们添加一个 start 参数来改变窗口的起点

##### 解放2: 实现：python

```
class Window:
    def __init__(self, s, words, start):
        """
        start 是改变窗口的起点
        """
        self.s = s

        self.nwords = len(words)
        self.wordlen = len(words[0])

        self.target = {}
        for word in words: 
            self.target[word] = self.target.get(word, 0) + 1
            
        self.left = self.right = start
        self.window = {}
        self.nmatched = 0

    def moveright(self):
        word = self.s[self.right: self.right + self.wordlen]
        self.window[word] = self.window.get(word, 0) + 1
        if word in self.target:
            if self.target[word] == self.window[word]:
                self.nmatched += 1
            elif self.window[word] - self.target[word] == 1:
                self.nmatched -= 1
        self.right += self.wordlen

    def moveleft(self):
        word = self.s[self.left: self.left + self.wordlen]
        self.window[word] -= 1
        if word in self.target:
            if self.window[word] == self.target[word]:
                self.nmatched += 1
            elif self.target[word] - self.window[word] == 1:
                self.nmatched -= 1
        if self.window[word] == 0:
            del self.window[word]
        self.left += self.wordlen

    def size(self):
        return self.right - self.left

    def check(self):
        return self.nmatched == len(self.target)
            
class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        n = len(s)
        ret = []
        for i in range(len(words[0])):
            window = Window(s, words, i)
            while window.right < n:
                window.moveright()
                if window.size() == len(words) * len(words[0]):
                    if window.check():
                        ret.append(window.left)
                    window.moveleft()
        return ret
```
