[toc]

# Leetcode 394. 字符串解码

## 问题描述

[394. 字符串解码 - 力扣（LeetCode）](https://leetcode-cn.com/problems/decode-string/)

## 算法

### 解法1

#### 解法1: 实现：

##### 解法1: 实现：

```
class Solution:
    def decodeString(self, s: str) -> str:
        return self.decodeRange(s, 0, len(s))

    def decodeRange(self, s, start, end):
        ret = ""
        i = start
        st = []
        while i < end:
            num = ""
            while '0' <= s[i] <= '9':
                num += s[i]
                i += 1
            if num != "": # 此时 s[i] == "["
                j = i
                while j < len(s):
                    if s[j] == '[':
                        st.append(s[j])
                    elif s[j] == ']':
                        st.pop()
                        if not st:
                            break
                    j += 1
                ret += self.decodeRange(s, i+1, j) * int(num)
                i = j + 1
            else:
                ret += s[i]
                i += 1
        return ret
```
