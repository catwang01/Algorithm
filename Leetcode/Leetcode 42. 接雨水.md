[toc]

# Leetcode 42. 接雨水

## 问题描述

- leetcode: [42. 接雨水 - 力扣（LeetCode）](https://leetcode-cn.com/problems/trapping-rain-water/)

给定 *n* 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

![](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/10/22/rainwatertrap.png)

上面是由数组 \[0,1,0,2,1,0,1,3,2,1,2,1\] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。
**示例:**

**输入:** \[0,1,0,2,1,0,1,3,2,1,2,1\]
**输出:** 6


## 算法


### 解法1:

#### 核心思想——如何计算容下的水量

![6f50a99bab18c9a8bac0b45af937f8bd.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p12626)

#### 解法1:实现1: bruteforce


时间复杂度：$O(n^2)$

##### 解法1:实现1: python


```
class Solution:
    def trap(self, height: List[int]) -> int:
        n = len(height)
        water = 0
        for i in range(1, n-1):
            leftmax = max(height[:i])
            rightmax = max(height[i+1:])
            shortest = min(leftmax, rightmax)
            if height[i] < shortest:
                water += shortest - height[i]
        return water
```

#### 解法1:实现2：动态规划

在上面的计算中，我们没有必要每次都遍历所有小于i的数和大于i的数来分别计算leftmax 和 rightmax，注意要有递推关系

```
leftmax[i] = max(leftmax[i-1], height[i-1])
rightmax[i] = max(rightmax[i+1], height[i+1])
```

因此可以将 `leftmax` 和 `rightmax` 的值保存成列表以避免重复计算

时间复杂度：$O(n)$
空间复杂度：$O(n)$

##### 解法1：实现2：python

```
class Solution:
    def trap(self, height: List[int]) -> int:
        n = len(height)
        water = 0
        leftmax = [0] * n
        rightmax  = [0] * n

        for i in range(1, n-1): # O(n)
            leftmax[i] = max(leftmax[i-1], height[i-1])
        for i in range(n-2, 0, -1): # O(n)
            rightmax[i] = max(rightmax[i+1], height[i+1])
            
        for i in range(1, n-1): # O(n)
            shortest = min(leftmax[i], rightmax[i])
            if height[i] < shortest:
                water += shortest - height[i]
        return water
```

#### 解法1：实现3：滚动数组优化

由于 leftmax 和 rightmax 只使用了一个，因此可考虑不使用数组来保存它们

先保持rightmax不动，将leftmax换成一个变量，而非一个数组

```
class Solution:
    def trap(self, height: List[int]) -> int:
        n = len(height)
        water = 0
        leftmax = 0
        rightmax  = [0] * n
        
        for i in range(n-2, 0, -1): # O(n)
            rightmax[i] = max(rightmax[i+1], height[i+1])
            
        for i in range(1, n-1): # O(n)
            leftmax = max(leftmax, height[i-1])
            shortest = min(leftmax, rightmax[i])
            if height[i] < shortest:
                water += shortest - height[i]
        return water
```

#### 解法1: 实现4: 双指针空间优化

上面成功地去掉了 `leftmax` 数组，但是 `rightmax` 数组没法去掉，因为 `rightmax` 数组和 `leftmax` 数组的更新方向是反的；

我们用两个指针 leftIdx 和 rightIdx 分别表示两个方向。 [0, leftIdx) 表示左侧遍历过的数字，并在遍历的过程中维护其最大值 leftmax，(rightIdx, n-1] 表示右侧遍历过的数字，并在遍历的过程中维护其最大值 rightmax。

如果 `leftmax < rightmax`，那么我们就移动 `leftIdx`，在移动的过程中做两件事情：

1. 如果 `height[leftIdx] < leftmax`，说明 `leftIdx` 指针所在的柱子可以和 `leftmax` 还有 `rightmax` 形成水坑，因此

```
ret += leftmax - height[leftIdx]
leftIdx += 1
```

2. 如果 `height[leftIdx] >= leftmax` 此时说明 `leftIdx` 指针所指的柱子左侧没有比它更高的柱子，因此不会形成水坑。此时 ret 不会累加，但是会更新 `leftmax`

综上，当 `leftmax < rightmax` 时，我们的更新策略为


```
if height[leftIdx] < leftmax:
    ret += leftmax - height[leftIdx]
else:
    leftmax = height[leftIdx]
leftIdx += 1
```

`leftmax >= rightmax` 时同理。

##### 一点点思考

我们先想清楚为什么有优化的空间。

我们在上面的过程中，维护了 leftmax 和 rightmax。

而我们想要计算的是，对于所有的 i，如果 height[i] < min(max(height[:i]), max(height[i+1:]))，
我们就累加

```
ret += min(max(height[:i]), max(height[i+1:])) - height[i]
```

这在这个过程中，假设 `leftmax = height[:i]`，而 `rightmax = max(height[j:])` 且 j >= i+1。

如果 j = i + 1，那么 ret += min(max(leftmax, rightmax)) 是没有问题的，因为

```
min(max(height[:i]), max(height[i+1:])) = min(max(leftmax, rightmax)
```

但是，j 不一定等于 i + 1，j 可能比 i + 1 要大。这样 

```
min(max(height[:i]), max(height[i+1:])) = min(max(leftmax, rightmax)
```

就不一定成立。

但是，如果加上某个条件，上式仍然成立。我们加上  `rightmax >= leftmax` 这个条件后，上式仍然成立。

因为

```
leftmax <= rightmax = max(height[j:]) # 定义
        <= max(height[i+1:]) # 因为 j >= i+1
因此 min(leftmax, rightmax) = leftmax = min(left, max(height[i+1:])) = min(max(height[:i]), max(height[i+1:]))
```

##### 解法1: 实现4: python  

```
class Solution:
    def trap(self, height: List[int]) -> int:
        n = len(height)
        if n < 3: return 0
        leftmax, rightmax = height[0], height[n-1]
        ret = 0
        leftIdx, rightIdx = 1, n-2
        while leftIdx <= rightIdx:
            if leftmax < rightmax:
                if height[leftIdx] < leftmax:
                    ret += leftmax - height[leftIdx]
                else:
                    leftmax = height[leftIdx]
                leftIdx += 1
            else:
                if height[rightIdx] < rightmax:
                    ret += rightmax - height[rightIdx]
                else:
                    rightmax = height[rightIdx]
                rightIdx -= 1
        return ret
```

### 解法2：单调栈法


这种计算方法和解法1不同，解法1相当于是竖着算。解法2相当于横着算

这里需要求柱子左右两侧第一个大于它本身的值，因此需要使用单调递减栈；

当 栈顶元素 <= height[i] 时，说明此时 height[i] 和次栈元素形成一水坑。

![18a5ed98b8428e481b04c15a04b38433.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p12627)


#### 解法2：实现

##### 解法2：实现：python

```
class Solution:
    def trap(self, height: List[int]) -> int:
        n = len(height)
        water = 0
        stack = []
        for i in range(n):
            while (stack!=[] and height[stack[-1]] <= height[i]):
                top = stack.pop()
                if stack != []:
                    water =  water + (min(height[i], height[stack[-1]]) - height[top]) * (i - stack[-1] - 1);
            stack.append(i)
        return water
```