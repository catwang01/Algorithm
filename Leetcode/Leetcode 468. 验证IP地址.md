[toc]

# Leetcode 468. 验证IP地址

## 问题描述

[468. 验证IP地址 - 力扣（LeetCode）](https://leetcode-cn.com/problems/validate-ip-address/)

## 算法

### 解法1

```
class Solution:
    def validIPAddress(self, IP: str) -> str:
        if IP.count(".") == 3 and IP.count(":") == 0:
            return self.validIPV4(IP)
        if IP.count(".") == 0 and IP.count(":") == 7:
            return self.validIPV6(IP)
        return "Neither"

    def validIPV4(self, IP):
        i = 0
        ngroup = 0
        while i < len(IP):
            j = i
            while j < len(IP) and IP[j] != '.':
                j += 1
            if j - i == 0 or j - i > 3:
                return "Neither"
            if j - i > 1 and IP[i] == '0':
                return "Neither"
            elif not (IP[i:j].isdigit() and 0 <= int(IP[i:j]) <= 255):
                return "Neither"
            ngroup += 1
            i = j + 1
        if ngroup == 4:
            return "IPv4"
        else:
            return "Neither"

    def validIPV6(self, IP):
        i = j = 0
        ngroup = 0
        while i < len(IP):
            j = i
            while j < len(IP) and IP[j] != ":":
                j += 1
            if j - i > 4 or j - i == 0:
                return "Neither"
            for k in range(i, j):
                if not ('0' <= IP[k] <= '9' or 'a' <=IP[k] <= 'f' or 'A' <= IP[k] <= 'F'):
                    return "Neither"
            ngroup += 1
            i = j + 1
        if ngroup == 8:
            return "IPv6"
        else:
            return "Neither"
```
