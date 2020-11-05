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
            max_left = max(height[:i])
            max_right = max(height[i+1:])
            shortest = min(max_left, max_right)
            if height[i] < shortest:
                water += shortest - height[i]
        return water
```

#### 解法1:实现2：动态规划

在上面的计算中，我们没有必要每次都遍历所有小于i的数和大于i的数来分别计算max_left 和 max_right，注意要有递推关系

```
max_left[i] = max(max_left[i-1], height[i-1])
max_right[i] = max(max_right[i+1], height[i+1]
```

因此可以将 max_left 和 max_right 的值保存成列表以避免重复计算

时间复杂度：$O(n)$
空间复杂度：$O(n)$

##### 解法1：实现2：python

```
class Solution:
    def trap(self, height: List[int]) -> int:
        n = len(height)
        water = 0
        max_left = [0] * n
        max_right  = [0] * n

        for i in range(1, n-1): # O(n)
            max_left[i] = max(max_left[i-1], height[i-1])
        for i in range(n-2, 0, -1): # O(n)
            max_right[i] = max(max_right[i+1], height[i+1])
            
        for i in range(1, n-1): # O(n)
            shortest = min(max_left[i], max_right[i])
            if height[i] < shortest:
                water += shortest - height[i]
        return water
```

#### 解法1：实现3：利用双指针对法二进行空间优化

由于 max_left 和 max_right 只使用了一个，因此可考虑不使用数组来保存它们

先保持max_right不动，将max_left换成一个变量，而非一个数组

```
class Solution:
    def trap(self, height: List[int]) -> int:
        n = len(height)
        water = 0
        max_left = 0
        max_right  = [0] * n
        
        for i in range(n-2, 0, -1): # O(n)
            max_right[i] = max(max_right[i+1], height[i+1])
            
        for i in range(1, n-1): # O(n)
            max_left = max(max_left, height[i-1])
            shortest = min(max_left, max_right[i])
            if height[i] < shortest:
                water += shortest - height[i]
        return water
```

上面成功地去掉了 max_left数组，但是 max_right数组没法去掉，因为max_right数组和max_left数组的更新方向是反的；

因此要引用左右双指针i，j 分别表示遍历max_left和max_right的数组的下标，

注意到下面的更新规则

```
max_left = max(max_left, height[i - 1]);
```

因此，$max\_left \le height[i-1]$；同样地，有 $max\_right \le height[j+1]$

因此，如果 $height[i-1] \le height[j+1]$，则

# todo 这里我没有办法理解

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