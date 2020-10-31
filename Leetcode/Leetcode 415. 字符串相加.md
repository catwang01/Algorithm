[toc]

# Leetcode 415. 字符串相加

## 问题描述

[415. 字符串相加 - 力扣（LeetCode）](https://leetcode-cn.com/problems/add-strings/)

## 算法

### 解法1：

#### 解法1：实现

##### 解法1: c++

```cpp
class Solution {
public:
    string addStrings(string num1, string num2) {
        if (num1=="0") return num2;
        if (num2=="0") return num1;
        string ret;
        int i=num1.size()-1, j = num2.size() - 1;
        int carry = 0;
        int val;
        while ( i>=0 || j>=0 || carry)
        {
            val = carry;
            if (i>=0) 
            {
                val += num1[i] - '0';
                i -- ;
            }
            if (j>=0)
            {
                val += num2[j] - '0';
                j--;
            }
            carry = val / 10;
            ret = to_string(val % 10) + ret;
        }
        return ret;
    }
};
```