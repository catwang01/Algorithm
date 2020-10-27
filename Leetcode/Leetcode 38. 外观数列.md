[toc]

# Leetcode 38. 外观数列

## 问题描述

[38. 外观数列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/count-and-say/)

## 算法

### 解法1：滑动窗口

不是太难，递推就可以。注意 next 的参数改成 string& 可以大大加速。

#### 解法1: 实现1

##### 解法1: 实现1: c++

```
class Solution {
public:
    string countAndSay(int n) {
        string ret = "1";
        if (n==1) return ret;
        for(int i=2; i<=n; i++)
        {
            ret = next(ret);
        }
        return ret;
    }
    string next(const string& s)
    {
        int i = 0, j;
        string ret;
        while (i < s.size())
        {
            // [i, j) is the window
            j = i;
            while (j < s.size() && s[j]==s[i])
            {
                j++;
            }
            // j == s.size() || s[j] != ch
            ret += to_string(j - i) + s[i];
            i = j;
        }
        return ret;
    }
};
```