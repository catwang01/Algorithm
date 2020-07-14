[toc]

# Leetcode 371. 两整数之和

## 问题描述

[371. 两整数之和 - 力扣（LeetCode）](https://leetcode-cn.com/problems/sum-of-two-integers/)

## 算法

### 解法1：递归

```
class Solution {
public:
    int getSum(int a, int b) {
        if (a==0) return b;
        if (b==0) return a;
        return getSum(a ^ b, (unsigned int)(a & b) << 1);
    }
};
```

### 解法2：迭代

```
class Solution {
public:
    int getSum(int a, int b) {
        int c;
        do 
        {
            c = (unsigned int)(a & b) << 1;
            a = a ^ b;
            b = c;
        } while (c);
        return a;
    }
};
```