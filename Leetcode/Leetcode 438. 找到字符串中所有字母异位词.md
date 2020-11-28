[toc]

# Leetcode 438. 找到字符串中所有字母异位词

## 问题描述

[438. 找到字符串中所有字母异位词 - 力扣（LeetCode）](https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/submissions/)

给定一个字符串 **s **和一个非空字符串 **p**，找到 **s **中所有是 **p **的字母异位词的子串，返回这些子串的起始索引。

字符串只包含小写英文字母，并且字符串 **s **和 **p **的长度都不超过 20100。

**说明：**

*   字母异位词指字母相同，但排列不同的字符串。
*   不考虑答案输出的顺序。

**示例 1:**
**输入:**
s: "cbaebabacd" p: "abc"
**输出:**
\[0, 6\]

**解释:**
起始索引等于 0 的子串是 "cba", 它是 "abc" 的字母异位词。
起始索引等于 6 的子串是 "bac", 它是 "abc" 的字母异位词。

** 示例 2:**
**输入:**
s: "abab" p: "ab"
**输出:**
\[0, 1, 2\]
**解释:**
起始索引等于 0 的子串是 "ab", 它是 "ab" 的字母异位词。
起始索引等于 1 的子串是 "ba", 它是 "ab" 的字母异位词。
起始索引等于 2 的子串是 "ab", 它是 "ab" 的字母异位词。

## 算法

### 解法一：bruteforce


计 n = len(s) m = len(p)

设置窗宽为同，从第0个字符开始向后取到 n-m，一共 n-m+1 个窗口。判断每个窗口是否满足条件；如果是，就记录，如果不是就向继续取窗口

有 n-m+1 个窗口，每个窗口中检查满足条件需要用时 $O(2m)=O(m)$

时间复杂度： $O(nm)$
空间复杂度： $O(m)$ 在 check 函数中需要建立一个 Counter，因此空间复杂度为 $O(m)$

#### 解法一python

超时

```
from collections import Counter

class Solution:
    def findAnagrams(self, s: str, p: str) -> List[int]:
        n, m = len(s), len(p)
        if n < m: return []
        p = Counter(p)
        def check(string): # 用时 O(2m)
            d = Counter(string) # 这个操作时间复杂度为 O(m)
            return d == p    # 判等的时间复杂度为 O(m)
        return [i for i in range(n-m+1) if check(s[i:i+m])]
```

### 解法一常数小优化


上面的计算中每个窗口都重新计算了一个 d，有重复计算；可以建立一个d，每次移动指针更新窗口时都更新这个d即可。

对于字符串 s[i:i+m] 更新时 d[s[i]] -= 1，d[s[i+m]] += 1，这里要注意 i<n-m 时才可以这样更新；

![1eb248ddebda7e4bb224a47ef36cc1cb.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p10512)@w=300


时间复杂度： $O(nm)$ 将 check 函数的时间复杂度从 $O(2m)$ 优化为 $O(m)$
空间复杂度： $O(m)$

#### 解法一小优化python

```
from collections import Counter
class Solution:
    def findAnagrams(self, s: str, p: str) -> List[int]:
        n, m = len(s), len(p)
        if n < m: return []
        p = Counter(p) # 统计目标串的字母个数
        d = Counter(s[:m])   # 统计窗口上的字母个数

        # 判断窗口是否满足条件
        def check(string):
            for k in p:
                if d.get(k, 0) < p[k]:
                    return False
            return True
            
        result = []
        for i in range(n-m+1):
            if check(s[i:i+m]):
                result.append(i)
            d[s[i]] -= 1
            if i < n-m:
                d[s[i+m]] = d.get(s[i+m], 0) + 1     
        return result
```

### 解法一再优化

上面的优化将 check 函数的时间复杂度从  $O(2m) = O(m)$，减低到了 $O(m)$，下面还可以进一步将check函数的时间复杂度优化为 $O(1)$

时间复杂度：$O(n)$
空间复杂度：$O(m)$

#### 解法一再优化python

```
from collections import Counter
class Solution:
    def findAnagrams(self, s: str, p: str) -> List[int]:
        n, m = len(s), len(p)
        if n < m: return []
        p = Counter(p)
        d = Counter(s[:m])

        n_needs = len(p)
        valid_nums = set() # 用来记录那些已经满足条件的字母
        for k in p:
            if d.get(k, 0) >= p[k]:
                valid_nums.add(k)

        result = []
        for i in range(n-m+1):
            if len(valid_nums) == n_needs: # 这个相当于check函数
                result.append(i)
            d[s[i]] -= 1
            if d[s[i]] == p[s[i]]-1: # 字母s[i]的频率-1后已经不满足条件了
                valid_nums.remove(s[i])
            if i < n-m:
                d[s[i+m]] = d.get(s[i+m], 0) + 1
                if d[s[i+m]] == p[s[i+m]]: # d[s[i+m]] 加1后刚好等于 p[s[i+m]]，说明 s[i+m] 从不满足条件到恰好满足条件
                    valid_nums.add(s[i+m])
```

### 解法2: 滑动窗口

这个还是子串问题，第一时间想得到滑动窗口。


1. 确定特征（考察单调性）

由于这道题考察的是某个词是否是异位词，因此我们考察 `是异位词` 这个特征是否满足单调性

```
如果 s[i:j] 是异位词
1. s[i:j+1] 不是异位词
2. s[i+1:j] 不是异位词，但是是异位词的一部分 ---> 这一点说明是异位词本身不是单调的，但是 异位词的一部分 这个特征是单词的

如果 s[i:j] 不是异位词，
1. s[i:j+1] 不是异位词，
2. s[i+1:j] 可能是异位词，也可能不是异位词
```

因此我们的特征是： `s[i:j]` 是异位词的一部分。这个特征是单调的。

2. 实现 check 函数

我们考虑用一个 dict 来代表我们的窗口 window，同时 p 也可以转化为一个 dict（我们这里用 Counter来实现）

```
target = Counter(p)
window = Counter()
```

每添加一个单词，我们就往 window 中添加。我们的判断标准是

1. 如果 window 中的 key 的数量多于 target 中 key 的数量，说明 window 中有 target 中不存在的 key，此时不满足 `s[i:j]` 是异位词的一部分

2. 否则，我们比较 window 和 target 两个 dict 是否满足

```
all(window[ch] <= target[ch] for ch in target) == True
```

综上，我们的 check 函数为

```
def check(window):
    return not set(window.keys()) - set(target.keys()) and all(window[ch] <= target[ch] for ch in target)
```

#### 解法2:实现1: 单调递减滑动窗口

##### 解法2:实现1:python

```
from collections import Counter
class Solution:
    def findAnagrams(self, s: str, p: str) -> List[int]:
        # 单调递减！
        n = len(s)
        left = right = 0
        target = Counter(p)
        window = Counter()

        def check(window):
            return not set(window.keys()) - set(target.keys()) and all(window[ch] <= target[ch] for ch in target)

        ret = []
        while right < n: # [left, right)
            window[s[right]] = window.get(s[right], 0) + 1
            while not check(window):
                window[s[left]] -= 1
                if window[s[left]] == 0:
                    del window[s[left]]
                left += 1
            if window == target: 
                ret.append(left)
            right += 1
        return ret
```


### 解法3: 固定窗宽单调递减滑动窗口

这个问题我们还可以看做是一个固定窗宽的滑动窗口问题，因为我们的目标是找到满足和给定字符串 p 是 `异位词` 子串。因此，可能的结果的窗口大小只可能是 len(p)，相当于是一个窗口大小为 len(p) 的固定窗宽的滑动窗口问题。

我们仍然在用一个 dict 来表示我们的窗宽。但是这次由于我们固定了窗口大小，因此我们的 check 函数可以小小的简化一下。

我们用一个 nmatched 来表示满足 `window[ch] == target[ch]` 的字符串。当 `nmatched == len(target)` 时，我们就可以判定 window 对应的子串满足条件，即我们的 check 函数为

```
def check(nmatched):
    return nmatched == len(target)
```

这个 check 函数的时间复杂度为 $O(1)$，但是我们需要在移动窗口时恰当地更新 nmatched

#### 解法3: 实现1: 单调递减滑动窗口

##### 解法3: 实现1: python

```
from collections import Counter
class Solution:
    def findAnagrams(self, s: str, p: str) -> List[int]:
        n = len(s)
        left = right = 0
        target = Counter(p)
        window = Counter()
        nmatched = 0

        def check(nmatched):
            return nmatched == len(target)

        ret = []
        while right < n: # [left, right)
            window[s[right]] = window.get(s[right], 0) + 1
            if s[right] in target:
                if window[s[right]] == target[s[right]]:
                    nmatched += 1
                elif window[s[right]] == target[s[right]] + 1:
                    nmatched -= 1
            if right - left + 1 == len(p):
                if check(nmatched):
                    ret.append(left)
                window[s[left]] -= 1
                if s[left] in target:
                    if window[s[left]] == target[s[left]]:
                        nmatched += 1
                    elif target[s[left]] - window[s[left]] == 1:
                        nmatched -= 1
                left += 1
            right += 1
        return ret
```

#### 解法3: 实现2: 面向对象的写法

##### 解法3: 实现2: python

```
class Window:
    def __init__(self, s, p):
        self.nmatched = 0
        self.target = Counter(p)
        self.window = {}
        self.s = s
        self.left = self.right = 0

    def moveright(self):
        ch = self.s[self.right]
        self.window[ch] = self.window.get(ch, 0) + 1
        if ch in self.target:
            if self.window[ch] == self.target[ch]:
                self.nmatched += 1
            elif self.window[ch] == self.target[ch] + 1:
                self.nmatched -= 1
        self.right += 1

    def moveleft(self):
        ch = self.s[self.left]
        self.window[ch] -= 1
        if ch in self.target:
            if self.window[ch] == self.target[ch]:
                self.nmatched += 1
            elif self.target[ch] - self.window[ch] == 1:
                self.nmatched -= 1
        self.left += 1
    
    def check(self):
        return self.nmatched == len(self.target)

    def size(self):
        return self.right - self.left


class Solution:
    def findAnagrams(self, s: str, p: str) -> List[int]:
        n = len(s)
        window = Window(s, p)
        ret = []
        while window.right < n: # [left, right)
            window.moveright()
            if window.size() == len(p):
                if window.check():
                    ret.append(window.left)
                window.moveleft()
        return ret
```