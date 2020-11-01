[toc]


# Leetcode 231. 2的幂

## 问题描述

[231. 2的幂 - 力扣（LeetCode）](https://leetcode-cn.com/problems/power-of-two/)

## 算法

### 解法1:

```
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if (n <= 0) return false;
        if (n == 1) return true;
        int i = 1;
        for (int j=1; j<32; j++)
        {  
            i <<= 1;
            if (n==i) return true;
        }
        return false;
    }
};
```


### 解法2:

将最右边的一位变成 0，如果 n 在操作之后变成0，说明 n 是 2 的幂。

```
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if (n<=0) return false;
        return (n & (n-1)) == 0;
    }
};
```