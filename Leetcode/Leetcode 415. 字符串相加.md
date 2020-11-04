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
        stack<char> st;
        int carry = 0;
        int i = num1.size()-1, j = num2.size()-1;
        while (carry || i >=0 || j >= 0)
        {
            int s = carry;
            if (i>=0) s += (num1[i--] - '0');
            if (j>=0) s += (num2[j--] - '0');
            carry = s / 10;
            s %= 10;
            st.push(s + '0');
        }
        string ret;
        while (st.size())
        {
            ret += st.top(); st.pop();
        }
        return ret;
    }
};
```