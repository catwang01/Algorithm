[toc]

# Leetcode 7. 整数反转

## 问题描述

[7. 整数反转 - 力扣（LeetCode）](https://leetcode-cn.com/problems/reverse-integer/)

## 算法

### 解法1：利用 python 转化为 str 直接翻转

```
class Solution:
    def reverse(self, x: int) -> int:
        sign = 1 if x >= 0 else -1
        s = str(x).lstrip("-")
        new_x = sign * int(s[::-1])
        return new_x if (- (1 << 31)) <= new_x <= ((1 << 31) - 1) else 0
```

### 解法2:数学运算

主要是要处理溢出问题，有下面几点需要注意：

1. 如果是 INT_MIN 那么 abs(INT_MIN) 会溢出，因此需要单独处理
2. 判断 ret * 10 + x % 10 <= INT_MAX 不能直接处理，而得转化为 ret <= (INT_MAX - x % 10) / 10.0

#### 解法1:


```
class Solution {
public:
    int reverse(int x) {
        if (x == INT_MIN) return 0; // 先判断 x 是否是 INT_MIN
                                    // 如果是 INT_MIN 那么 abs(INT_MIN) 会溢出
        int sign = x >= 0 ? 1: -1;
        x = abs(x);
        int ret = 0;
        while (x)
        {
            if (ret <= (INT_MAX - x % 10) / 10.0)
            // ret * 10 + x % 10 <= INT_MAX
            {
                ret = ret * 10 + x % 10;
                x /= 10;
            }
            else return 0;
        }
        return sign * ret;
    }
};
```