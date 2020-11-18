[toc]


# Leetcode 137. 只出现一次的数字 II

## 问题描述

[137. 只出现一次的数字 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/single-number-ii/)

## 算法

### 解法1：状态转移

解法就是状态转移。

#### 对于某一位

我们需要达到 mod 3 的目的，假如我们用两个位来表示状态，00, 01, 10 分别代表这 3 个状态的话，我们需要达到这样的效果：

| # | Two One | x | Two_new One_new​ | 
| --- | --- | --- | --- | 
| 1 | 00 | 0 | 00 |
| 2 | 01 | 0 | 01 |
| 3 | 10 | 0 | 10 |
| 4 | 00 | 1 | 01 |
| 5 | 01 | 1 | 10 |
| 6 | 10 | 1 | 00 |

我们分开一个状态一个状态来看。

1. one

对于 one 状态来说，我们需要达到这样一个效果

```
x = 0 
    two = 0 one = 0 --> one_new = 0
    two = 0 one = 1 --> one_new = 1
    two = 1 one = 0 --> one_new = 0
这相当于 x = 0 时，one_new = one
x = 1
    two = 0 one = 0 --> one_new = 1
    two = 0 one = 1 --> one_new = 0
    two = 1 one = 0 --> one_new = 0
这相当于 x = 1 时，one_new = ~(two ^ one)
```

因此，合起来有

```
one_new = (x & (~(two ^ one))) | (~x & one)
```

2. two

对于状态 two 来说，我们希望得到这样的一个效果：

```
x = 0 
    two = 0 one = 0 --> two_new = 0
    two = 0 one = 1 --> two_new = 0
    two = 1 one = 0 --> two_new = 1
这相当于 x = 0 时，two_new = two
x = 1
    two = 0 one = 0 --> two_new = 0
    two = 0 one = 1 --> two_new = 1
    two = 1 one = 0 --> two_new = 0
这相当于 x = 1 时，two_new = one
```

```
two_new = (x & one)) | (~x & two)
```

注意这种改写方式，

```
# 注意下面 y 只能取 0 或 1
if x == 1:
    y = 表达式1
else:
    y = 表达式2
```

可以改写做：

```
y = (x & (表达式1)) | (~x & 表达式2)
```

这个可以由 & 运算的性质

```
1 & x = x 
0 & x = 0
```
来得出。

当 x == 1 时， 由上面的性质 

```
x & (表达式1) = 表达式1
~x & 表达式2 = 0
```
因此，有

```
y = (x & (表达式1)) | (~x & 表达式2) = 表达式1 | 0 = 表达式1
```

同理，x == 0 时，可以得到

```
y = (x & (表达式1)) | (~x & 表达式2) = 表达式2
```

#### 如何代表所有的位

注意，上面只是讨论了 32 位数字中的某 1 位，可以用 两个状态 two 和 one 来表示。

我们要将这个拓展到 32 位数字。two 和 one 分别变成了 32 位的数字。其中

two[i] 和 one[i] 和起来分别表示 32 位数字中的第 i 位数字的状态。

##### 解法1: 实现1: python

```
class Solution:
def singleNumber(self, nums: List[int]) -> int:
    two = one = 0
    for x in nums:
        one_new = (x & ~(two ^ one)) | (~x & one)
        two = (x & one) | (~x & two)
        one = one_new
    return one
```
