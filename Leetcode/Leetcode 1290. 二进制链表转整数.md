[toc]

# Leetcode 1290. 二进制链表转整数

## 问题描述

[1290. 二进制链表转整数 - 力扣（LeetCode）](https://leetcode-cn.com/problems/convert-binary-number-in-a-linked-list-to-integer/)

## 算法

### 解法1

这个题比较简单，没有啥太难的。

##### 解法1: 

```
class Solution {
public:
    int getDecimalValue(ListNode* head) {
        int ret = 0;
        while (head)
        {
            ret = ret * 2 + head->val;
            head = head->next;
        }
        return ret;
    }
};
```
