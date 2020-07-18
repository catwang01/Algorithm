[toc]

# Leetcode 166. 分数到小数

## 问题描述

[166. 分数到小数 - 力扣（LeetCode）](https://leetcode-cn.com/problems/fraction-to-recurring-decimal/)

## 算法

### 解法1: 

需要注意的几个点：

1. 对于出现负数的情况，先确定符号，然后再转化为正数去做。
2. 有可能不存在小数位，如 2 / 1
3. 有可能存在小数位， 但能除尽。如 1/2
4. 如何确定什么时候出现循环？当小数部分的被除数重复出现时，就可以判断出现循环。为此，可以用一个 hashset 来保存小数部分出现过的被除数。同时，还应该保存这个被除数的结果存在那个位置，以此来确定循环节和起始位置。因此，将 hashset 换成 hashtab 。键为出现过的被除数，值为这个被除数的结果在小数部分的下标。

#### 解法1: 实现

##### 解法1: python

```
class Solution:
    def fractionToDecimal(self, numerator: int, denominator: int) -> str:

        if numerator==0: # 被除数为0
            return str(0)

        positive = numerator ^ denominator >= 0 # 记录符号
        numerator, denominator = abs(numerator), abs(denominator)
        interger =  str(numerator // denominator)
        if not positive:
            interger = "-" + interger

        numerator %= denominator

        decimal = ""
        i = 0

        seen = {}   # 用来记录除数及其结果对应的位置
                    # seen[x] = i 表示 x 作为被除数时，其结果保存在 decimal[i]
        while numerator != 0:
            numerator *= 10
            if numerator in seen:
                break
            seen[numerator] = i
            i += 1
            decimal += str(numerator // denominator)
            numerator %= denominator

        if decimal == "": # 没有小数部分
            return str(interger)
        elif numerator != 0: # 无限循环
            # decimal[:seen[numerator]] 是小数部分的非循环节部分
            # decimal[seen[numerator]:] 是小数部分的循环节部分
            return "{}.{}({})".format(interger, decimal[:seen[numerator]], decimal[seen[numerator]:])
        else:  # 除尽了
            return "{}.{}".format(interger, decimal)
```