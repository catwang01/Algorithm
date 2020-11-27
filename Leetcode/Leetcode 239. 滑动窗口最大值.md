

[toc]

# Leetcode 239. 滑动窗口最大值

## 问题描述


[239. 滑动窗口最大值 - 力扣（LeetCode）](https://leetcode-cn.com/problems/sliding-window-maximum/)

## 算法

### 解法一：bruteforce

时间复杂度：$O(nk)$ 求max的时间复杂度为 $O(k)$，循环了 n-k+1
空间复杂度：$O(1)$ 除了需要输出的数组外没有额外使用空间

```
class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        if nums == []: return []
        return [max(nums[l-k:l]) for l in range(k,len(nums)+1)]
```

### 解法二：滑动窗口 + 单调队列

时间复杂度： $O(n)$，s 中的每个元素最多进一次队列出一次队列，因此时间复杂度为 $O(n)$
空间复杂度： $O(k)$ 因为队列的长度最大为k

####  解法2：实现1

#####  解法2：实现1：python

```
class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        n = len(nums)
        if n == 0 or k==0: return []
        
        q = deque() 
        result = []
        j = 0
        while j < n:
            while len(q) > 0 and q[-1] < nums[j]:
                q.pop() # 队列中放入的下标，而不是元素本身。这样的好处是可以通过供下标来判断最大值是否处于窗口左边界  
            q.append(nums[j]) 
            if j >= k-1: # 当 j=[0,k-2]时，相当于初始化窗口；从j=k-1开始，每次移动窗口，都会产生一个最大值
                result.append(q[0]) # 记录这个最大值
                if q[0]== nums[j-k+1]: # 如果最大值位于窗口的左边界，下次会移出窗口
                    q.popleft()
            j += 1
        return result
```

下面的代码将单调队列的代码抽象出来，可以简化逻辑结构，具体可以参考 [单调队列解题详解 - 滑动窗口最大值 - 力扣（LeetCode）](https://leetcode-cn.com/problems/sliding-window-maximum/solution/dan-diao-dui-lie-by-labuladong/)


#### 解法2：实现2：抽象出MonotonicQueue类

##### 解法2：实现2：python

```
from collections import deque

class MonotonicQueue:

    def __init__(self):
        self.q = deque()

    def max(self):
        return self.q[0]   

    def popleft(self):
        return self.q.popleft()

    def append(self, x):
        while len(self.q) > 0 and self.q[-1] < x:
            self.q.pop()
        self.q.append(x)

class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        n = len(nums)
        if n == 0 or k==0: return []
        
        q = MonotonicQueue() 
        result = []
        j = 0
        while j < n:
            q.append(nums[j])
            if j >= k-1: # 当 j=[0,k-2]时，相当于初始化窗口；从j=k-1开始，每次移动窗口，都会产生一个最大值
                result.append(q.max()) # 记录这个最大值
                if q.max() == nums[j-k+1]: # 如果最大值位于窗口的左边界，下次会移出窗口
                    q.popleft()
            j += 1
        return result
```

# References

- [单调队列解题详解 - 滑动窗口最大值 - 力扣（LeetCode）](https://leetcode-cn.com/problems/sliding-window-maximum/solution/dan-diao-dui-lie-by-labuladong/)
