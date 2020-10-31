[toc]

# Leetcode 8. 字符串转换整数 (atoi)

## 问题描述

[8. 字符串转换整数 (atoi) - 力扣（LeetCode）](https://leetcode-cn.com/problems/string-to-integer-atoi/submissions/)

这个问题没有用到什么算法，只需要将所有情况考虑情况就可以了。

## 算法


### 解法1: 防溢出

主要是防止溢出。这里有两点需要注意：
1. signed int32 的数据类型的范围是 $[-2^{31}, 2^{31}-1]$，所以  abs(INT_MIN) > INT_MAX。因此，如果要用一个 signed int32 直接

#### 解法1: 实现1: 用 unsigned int32


##### 解法1: 实现： c++

```
class Solution {
public:
    int myAtoi(string s) {
       int i = 0, n = s.size();
       while (i < n && s[i]==' ') i++; // 去掉前导空格
       if (i==n) return 0; // 全为空
       int sign = 1;
       if (s[i] == '-') { sign = -1; i++;}
       else if (s[i]=='+') {i++;}
       if (i==n) return 0; 
       int num = 0; // -num 表示数字的绝对值
                    // 这样表示有一个好处。 可以表示绝对值为 INT_MAX+1
       while (i < n && is_number(s[i]))
       {
           int digit = s[i] - '0';
            if (num >= (INT_MIN + digit) / 10.0)
            {
                num = num * 10 - digit;
                i++;
            }
            else
            {
                return sign==1 ? INT_MAX: INT_MIN;
            }
       }
       if (num==INT_MIN) return sign==1 ? INT_MAX: INT_MIN;
       return sign * abs(num);
    }

    bool is_number(char ch)
    {
        return '0' <= ch && ch <= '9';
    }
};
```

#### 解法1: 实现1: 不用 unsigned int32

```
class Solution {
public:
    int myAtoi(string s) {
       int i = 0, n = s.size();
       while (i < n && s[i]==' ') i++; // 去掉前导空格
       if (i==n) return 0; // 全为空
       int sign = 1;
       if (s[i] == '-') { sign = -1; i++;}
       else if (s[i]=='+') {i++;}
       if (i==n) return 0; 
       unsigned int num = 0; 
       while (i < n && is_number(s[i]))
       {
           int digit = s[i] - '0';
            if (num <= (unsigned(INT_MAX) + 1 - digit) / 10.0)
            {
                num = num * 10 + digit;
                i++;
            }
            else
            {
                return sign==1 ? INT_MAX: INT_MIN;
            }
       }
       if (num==unsigned(INT_MAX)+ 1) return sign==1 ? INT_MAX: INT_MIN;
       return sign * num;
    }

    bool is_number(char ch)
    {
        return '0' <= ch && ch <= '9';
    }
};
``