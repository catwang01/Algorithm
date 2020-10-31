
[toc]


# Leetcoce 43. 字符串相乘 

## 问题描述

[43. 字符串相乘 - 力扣（LeetCode）](https://leetcode-cn.com/problems/multiply-strings/)

## 问题描述

### 解法一：利用加法

#### 解法一：实现

```
class Solution:
    def multiply(self, num1: str, num2: str) -> str:
        if len(num1) < len(num2):
            return self.multiply(num2, num1)
        if len(num2) == 1:
            return self.multiply_with_one_bit(num1, num2)
        return self.add(
            self.multiply(num1, num2[:-1]) + "0", 
            self.multiply_with_one_bit(num1, num2[-1])
        )
    
        
    def add(self, num1, num2):
        i = len(num1) - 1
        j = len(num2) - 1
        carry = 0
        ret = ""
        while i >= 0 or j >= 0 or carry > 0:
            val = carry
            if i >=0:
                val += int(num1[i])
                i -= 1
            if j >= 0:
                val += int(num2[j])
                j -= 1
            carry = val // 10
            ret = str(val % 10) + ret
        return ret
        
    # 多位数 x 1 位数
    def multiply_with_one_bit(self, num1, num2):
        if num2=="0": return "0"
        if num2=="1": return num1
        ret = ""
        y = int(num2)
        i = len(num1) - 1
        carry = 0
        while i >= 0 or carry > 0:
            val = carry
            if i>=0:
                val += int(num1[i]) * y
                i -= 1
            carry = val // 10
            ret = str(val % 10) + ret
        return ret
```