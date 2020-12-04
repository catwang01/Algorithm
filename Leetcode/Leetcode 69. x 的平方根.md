[toc]

# Leetcode 69. x 的平方根

[69. x 的平方根 - 力扣（LeetCode）](https://leetcode-cn.com/problems/sqrtx/submissions/)

## 算法 

### 法一：二分法

题目相当于求 $x = k^2$ 的解，输出 $[k]$，可以使用二分法。

#### 解法1: 实现1

##### 解法1：python

```
class Solution:
    def mySqrt(self, x: int) -> int:
        return self.bisearch(0, x, x)
    
    def bisearch(self, low, high, target):
        while low < high:
            mid = low + high + 1>> 1
            if (mid * mid == target):
                return mid
            elif mid * mid < target:
                low = mid
            else:
                high = mid - 1
        return low
```

##### 解法1:c++

需要注意的是：

1. 可能的解是 $1 \leq k \leq x$。这里相当于用 $x$ 来作为 $\sqrt{x}$ 的一个上界估计，实际上，当 $x \geq 4$ 时，有 $\sqrt{x} < \frac{x}{2} < x$，即此时可以用 $x/2$ 代替 $x$ 来作为 $\sqrt{x}$ 上界
这样做有两个目的：
    1. 减少循环次数。不过这个提升是蚊子腿提升。因为二分检索一次循环就可以排除一半的数字，相当于少循环了一次而已。
    2. 这样做的主要目的不是为了加速，而是为了防止溢出。因为当x较大时，计算 mid 时会使用到 low + high，这时可能溢出。而 high 如果从 x/2 开始取，则 low + high < x/2 + x/2 < x，不可能溢出。

2. 要防止溢出。如果使用 `x < mid * mid` 来判断，当 `mid` 较大时会溢出。应该使用 `x / mid < mid` 来判断。

 
```
class Solution {
public:
    int mySqrt(int x) {
        if (x==0 || x==1) return x;
        int low = 0, high = x/2;
        while (low < high) {
            int mid = low + 1 + (high - low >> 1);
            if (x / mid < mid)
                high = mid - 1;
            else
                low = mid;
        }
        return low;   
    }
}; 
```

#### 解法2: 二分法实现2 闭区间 2个元素时退出 while

##### 解法1: 实现2: python

```
class Solution:
    def mySqrt(self, x: int) -> int:
        if x <= 1: return x
        low, high = 0, x
        while low + 1 < high:
            mid = (low + high) // 2  
            val = mid * mid
            if val == x:
                return mid
            elif val < x:
                low = mid
            else:
                high = mid - 1
        if high * high <= x:
            return high
        return low
```

#### 解法2: 实现3 左闭右开区间 2个元素时退出 while

##### 解法2: 实现3: python

```
class Solution:
    def mySqrt(self, x: int) -> int:
        # max(i**2 <=x)
        if x <= 1: return x
        low, high = 0, x
        condition = lambda i: i ** 2 <= x
        while high - low > 2:
            mid = (low + high) // 2
            if condition(mid):
                low = mid
            else:
                high = mid
        if condition(high-1):
            return high - 1
        return low
```