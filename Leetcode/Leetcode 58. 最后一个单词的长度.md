

[toc]

# Leetcode 58. 最后一个单词的长度

## 问题描述

[58. 最后一个单词的长度 - 力扣（LeetCode）](https://leetcode-cn.com/problems/length-of-last-word/)

## 算法

### 解法1: 从后向前遍历

#### 解法1: 实现1

##### 解法1: 实现1: c++

```
class Solution {
public:
    int lengthOfLastWord(string s) {
        int n = s.size();
        if (n == 0) return 0;
        int i = n;
        // [i, n) 表示空格
        while (i > 0 && s[i-1] == ' ') { i--; }
        if (i == 0) return 0;
        int j = i;
        // [j, i) 表示最大子字符串
        while (j>0 && s[j-1] != ' ') {j--;}
        return i - j;
    }
};
```