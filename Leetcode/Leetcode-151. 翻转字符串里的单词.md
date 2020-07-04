
[toc]

# Leetcode 151. 翻转字符串里的单词

## 问题描述

[151. 翻转字符串里的单词 - 力扣（LeetCode）](https://leetcode-cn.com/problems/reverse-words-in-a-string/)

## 算法

### 解法一：split+join

#### 解法一：实现

##### 解法一：Java

```
import java.util.Collections;
import java.util.List;

class Solution {
    public String reverseWords(String s) {
        List<String> strList = Arrays.asList(s.trim().split(" +"));
        Collections.reverse(strList);
        return String.join(" ", strList);
    }
}
```

### 解法二：滑动窗口 + stack

这个用到了滑动窗口的思想

#### 解法二：实现

##### 解法二：c++

``` 
class Solution {
public:
    string reverseWords(string s) {
        int n = s.size();
        int i = 0; 
        stack<string> st;
        string ret;
        // 去掉头部的空格
        while (i < n && s[i] == ' ') i++;
        // 此时 i == n || s[i] != ' '
        if (i == n) return ret;
        // 此时 s[i] != ' '
        int j;
        while (i < n) {
            j = i;
            while (j<n && s[j] != ' ') j++;
            // 此时 j == n || s[j] == ' '
            st.push(s.substr(i, j-i));
            // 去掉中间和尾部的空格
            while (j < n && s[j] == ' ') j++;
            i = j;
        }
        while (!st.empty()) {
            ret += st.top() + " ";
            st.pop();
        }
        return ret.substr(0, ret.size()-1);
    }
};
```

### 解法3:stack

#### 解法3:实现

##### 解法3:c++

```
class Solution {
public:
    string reverseWords(string str) {
        stack<string> s;
        string word, ret;
        stringstream ss(str);
        while(ss >> word) {
            s.push(word);
        }
        while (!s.empty()) {
            ret += s.top() + “ “;
            s.pop();
        }
        return ret.substr(0, ret.size()-1_;
    }
};
```
