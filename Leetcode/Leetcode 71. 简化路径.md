[toc]

# Leetcode 71. 简化路径

## 问题描述

[71. 简化路径 - 力扣（LeetCode）](https://leetcode-cn.com/problems/simplify-path/)

## 算法

### 解法1: 滑动窗口 + 栈

#### 解法1: c++

```
class Solution {
public:
    string simplifyPath(string path) {
        deque<string> dq;
        int i = 0, n = path.size(), j;
        string word;
        while (i < n) {
            j = i;
            // 去掉连续的 /
            while (j < n && path[j] == '/') j++;
            
            // 此时 j==n || path[j] != '/'
            i = j;
            
            while (j < n && path[j] != '/') j++;
            // 此时 j == n || path[j] == '/'
            word = path.substr(i, j-i);
            
            if(word=="." || word == "") 
            {
            } 
            else 
            {
                if (word=="..")
                {
                    if (!dq.empty()) dq.pop_back();
                }
                else 
                {
                    dq.push_back(word);
                }
            }
            i = j;
        }

        if (dq.empty()) return "/";
        string ret;
        while (!dq.empty()) {
            ret += "/" + dq.front();
            dq.pop_front();
        }
        return ret;
    }
};
```

### 解法2: split + 栈

直接使用 split 来分割。python 中的 split 会去掉多个重复的分割符。因此可以直接使用。

#### 解法2: python

```
class Solution:
    def simplifyPath(self, path: str) -> str:
        tokens = path.split('/')
        stack = []
        for token in tokens:
            if token == '..':
                if stack: stack.pop()
            elif token == '.' or token == "":
                pass
            else:
                stack.append(token)
        return "/" + '/'.join(stack)
```