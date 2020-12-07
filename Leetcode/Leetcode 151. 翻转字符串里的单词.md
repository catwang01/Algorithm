
[toc]

# Leetcode 151. 翻转字符串里的单词

## 问题描述

[151. 翻转字符串里的单词 - 力扣（LeetCode）](https://leetcode-cn.com/problems/reverse-words-in-a-string/)

## 算法

### 解法一： 调用 api split+join

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

##### 解法1: c++

c++ 没有 split 函数，但是可以用 cin 来进行分割。c++ 没有 join 函数，可以用 for 循环来累加。

```
class Solution {
public:
    string reverseWords(string s) {
        stringstream ss(s);
        vector<string> words;
        string word;
        while(ss >> word)
        {
            words.push_back(word);
        }
        string ret;
        for_each(
            words.rbegin(), 
            words.rend(), 
            [&ret](const string& word){ret += word + " ";}
        );
        return ret.substr(0, ret.size()-1);
    }
};
```

### 解法二：滑动窗口 + stack

这个用到了滑动窗口的思想

#### 解法2：实现1: 滑动窗口 + stack

##### 解法2： 实现1： c++

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

##### 解法2: 实现1：python

```
class Solution:
    def reverseWords(self, s: str) -> str:
        # strip head
        start = 0
        while start < len(s) and s[start] == ' ':
            start += 1
        # s[start]!= ' '

        # strip tails
        end = len(s)
        while end - 1 >= 0 and s[end-1] == ' ':
            end -= 1

        # [start, end) 这里有效
        i = start
        st = []
        while i < end:
            j = i
            while j < end and s[j] != ' ':
                j += 1
            st.append(s[i:j])
            while j < end and s[j] == ' ':
                j += 1
            i = j

        ret = ""
        while st:
            ret += st.pop() + " "

        return ret[:len(ret)-1]
```

#### 解法2:实现: 滑动窗口 + 2次reverse

##### 解法2：实现: python

```
class Solution:
    def reverseWords(self, s: str) -> str:
        list_s = list(s)
        end = self.removeSpace(list_s, 0, len(list_s))
        self.reverse(list_s, 0, end)
        i = 0
        while i < end:
            j = i
            while j < end and list_s[j] != ' ':
                j += 1
            self.reverse(list_s, i, j)
            i = j + 1
        return "".join(list_s[:end])

    def reverse(self, s, low, high):
        while high - low >= 2:
            s[low], s[high-1] = s[high-1], s[low]
            low += 1
            high -= 1

    def removeSpace(self, s, low, high):
        i = j = low
        # [low, i) normal string
        # [i, j) repeated spaces
        while j < high:
            if s[j] != ' ' or (i - 1 >= 0 and s[i-1] != ' '):
                s[j], s[i] = s[i], s[j]
                i += 1
            j += 1
        if s[i-1] == ' ':
            return i - 1
        else:
            return i
```
