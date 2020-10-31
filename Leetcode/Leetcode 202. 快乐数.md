[toc]

# Leetcode 202. 快乐数

## 问题描述

[202. 快乐数 - 力扣（LeetCode）](https://leetcode-cn.com/problems/happy-number/)

## 算法


### 解法1：使用 hashset 来判断重复

这个算法的复杂度分析有点复杂。

#### 解法1: python

```
class Solution:
    def isHappy(self, n: int) -> bool:
        history = set()
        history.add(n) 
        while True:
            new_n = 0
            while n:
                new_n += (n % 10) ** 2
                n //= 10
            n = new_n
            if n == 1:
                return True
            else:
                if n in history:
                    return False
                else:
                    history.add(n)
        return True
```
            
### 解法2: 使用快慢指针来判断重复

使用 hash 表需要额外空间。可以使用快慢指针来实现判断重复

#### 解法2: 实现

##### 解法2: python

```
class Solution:
    def isHappy(self, n: int) -> bool:
        slow, fast = n, n
        while True:
            slow = self.countVal(slow)
            # fast 指针前移
            fast = self.countVal(fast)
            if fast == 1: return True

            # fast 指针前移
            fast = self.countVal(fast)
            if fast == 1: return True
            if fast == slow:
                break
        return False
    
    def countVal(self, n):
        ret = 0
        while n:
            ret += (n % 10)**2
            n //= 10
        return ret
```

#### 解法2: python 改进：记忆化减少重复计算

使用快慢指针来判断循环会有重复计算，可以使用记忆化来减少重复计算

```
class Solution:
    def __init__(self):
        self.memo = {}

    def isHappy(self, n: int) -> bool:
        slow, fast = n, n
        while True:
            slow = self.countVal(slow)
            # fast 指针前移
            fast = self.countVal(fast)
            if fast == 1: return True

            # fast 指针前移
            fast = self.countVal(fast)
            if fast == 1: return True
            if fast == slow:
                break
        return False
    
    def countVal(self, n):
        if n not in self.memo:
            self.memo[n] = 0
            m = n
            while m:
                self.memo[n] += (m % 10) ** 2
                m //= 10
        return self.memo[n]
```

# References
1. [快乐的知识点增加了 - 快乐数 - 力扣（LeetCode）](https://leetcode-cn.com/problems/happy-number/solution/kuai-le-de-zhi-shi-dian-zeng-jia-liao-by-sweetiee/)