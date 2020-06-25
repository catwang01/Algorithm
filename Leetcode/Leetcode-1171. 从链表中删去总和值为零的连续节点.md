[toc]

# Leetcode 1171. 从链表中删去总和值为零的连续节点

## 问题描述

[1171. 从链表中删去总和值为零的连续节点 - 力扣（LeetCode）](https://leetcode-cn.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/)

## 算法

### 解法1: 迭代

#### 解法1: 实现

##### 解法1: c++

```cpp
class Solution {
public:
    ListNode* removeZeroSumSublists(ListNode* head) {
        if (!head) return nullptr;
        if (!head->next) {
            return head->val == 0 ? nullptr: head;
        }
        
        int sum = 0; 
        ListNode *p = head;
        // 计算以第一个结点为首的链表是否存在连续的和为零的链表
        while (p) {
            sum += p->val;
            if (sum==0) { // 如果存在，向下递归
                return removeZeroSumSublists(p->next);
            } else {
                p = p->next;
            }
        }
        // 如果能出 while 循环，说明不存在以第一个结点为首，
        head->next = removeZeroSumSublists(head->next);
        return head;
    }
};
```

# todo  这个貌似有点复杂。

### 解法2: 前缀数组 + hashtab

#### 解法2: 实现

##### 解法2: c++

```cpp
```