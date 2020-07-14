[toc]

# Nowcoder 不用算术运算符实现整数的加减乘除运算

## 问题描述

[不用算术运算符实现整数的加减乘除运算_牛客网](https://www.nowcoder.com/practice/7c478cdfbacb4fd38ca063aa2ac35b6f?tpId=101&tags=&title=&diffculty=0&judgeStatus=0&rp=1&ru=/activity/oj&qru=/ta/programmer-code-interview-guide/question-ranking)

## 算法

### 加法

a ^ b 表示无进位加法，而 (a & b) << 1 表示进位。

但是有一点很让人困惑。正数加正数是可以理解的，但是正数加负数和负数加负数不太能理解。

这个要看了补码相关的内容才能明白。大概就是补码 + 溢出可以保证负数和正数的运算统一起来。


#### 递归

```
int add(int a, int b)
{
    if (a==0) return b;
    if (b==0) return a;
    return add(a ^ b, (a & b) << 1);
}
```

#### 迭代

```
int add(int a, int b)
{
    int c;
    while (b) 
    {
        c = (a & b) << 1;
        a = a ^ b;
        b = c;
    }
    return a;
}
```

### 减法

由于用补码表示负数，因此减法可以转化为加法。减去 x 可以转化为加上 -x，而一个数的相反数相当于对这个数取反 + 1，即 ~x + 1，因此可以得到减法的代码

```
int substract(int a, int b)
{
    return add(a, add(~b, 1));
}
```

### 乘法

#### 修改成加法

```cpp
int multiply(int a, int b) 
{
    if (a==0 || b==0) return 0;
    int sign = a ^ b > 0;
    a = a >= 0 ? a : add(~a, 1);
    b = b >= 0? b : add(~b, 1);
    int ret = 0;
    while (b) 
    {
        if (b & 1) {
            ret = add(ret, a);
        }
        b >>= 1;
        a <<= 1;
    }
    return sign ? ret : add(~ret, 1);
}
```

#### 其它


```
```

### 除法

#### $O(n)$ 算法

#### $O(log n)$ 算法

```cpp
int divide(int a, int b) 
{
    if (a == 0 && b!=0) return 0;
    int sign = ( a ^ b ) > 0;
    a = a >= 0 ? a : add(~a, 1);
    b = b >= 0? b : add(~b, 1);
    int i = 31;
    int ret = 0;
    while (i >= 0 && a >= b) 
    {
        if ((a >> i) >= b)
        {
            ret = add(ret, 1 << i);
            a = substract(a, b << i);
        }
       substract(i, 1);
    }
    return sign ? ret : add(~ret, 1);
}
```

### 解法1: 实现

```cpp
#include <iostream>
using namespace std;

int add(int a, int b) 
{
    int c;
    do {
        c = (a & b) << 1;
        a = a ^ b;
        b = c;
    } while (c);
    return a;
}

int substract(int a, int b)
{
    return add(a, add(~b, 1));
}

int multiply(int a, int b) 
{
    if (a==0 || b==0) return 0;
    int sign = (a ^ b) > 0;
    a = a >= 0 ? a : add(~a, 1);
    b = b >= 0? b : add(~b, 1);
    int ret = 0;
    while (b) 
    {
        if (b & 1) {
            ret = add(ret, a);
        }
        b >>= 1;
        a <<= 1;
    }
    return sign ? ret : add(~ret, 1);
}

int divide(int a, int b) 
{
    if (a == 0 && b!=0) return 0;
    int sign = (a ^ b) > 0;
    a = a >= 0 ? a : add(~a, 1);
    b = b >= 0? b : add(~b, 1);
    int i = 31;
    int ret = 0;
    while (i >= 0 && a >= b) 
    {
        if ((a >> i) >= b)
        {
            ret = add(ret, 1 << i);
            a = substract(a, b << i);
        }
       substract(i, 1);
    }
    return sign ? ret : add(~ret, 1);
}

int main() 
{
    int a, b;
    char op;
    cin >> a >> op >> b;
    int ret;
    switch(op)
    {
            case '+': 
                ret = add(a, b); break;
            case '-':
                ret = substract(a, b); break;
            case '*':
                ret = multiply(a, b); break;
            case '\\':
                ret = divide(a, b); break;
    };
    printf("%d\n", ret);
    return 0;
}
```




# References
1. [只用位运算来实现整数的加减乘除四则运算_LUCKYOJ-CSDN博客_位运算实现四则运算](https://blog.csdn.net/ojshilu/article/details/11179911#commentBox)