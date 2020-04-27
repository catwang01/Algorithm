[toc]

# Leetcode 面试题18. 删除链表的节点

## 问题描述

[面试题18. 删除链表的节点 - 力扣（LeetCode）](https://leetcode-cn.com/problems/shan-chu-lian-biao-de-jie-dian-lcof/)

## 算法

### 解法1: 虚拟结点

由于被删除的结点可能是头结点，所以需要设置虚拟结点。

#### 解法1:实现

##### 解法1: c++

```
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        if (!head) return head;
        ListNode node(0), *virtualHead = &node;
        virtualHead->next = head;
        ListNode *cur = virtualHead;
        while (cur && cur->next) {
            if (cur->next->val == val) {
                cur->next = cur->next->next;
            } else {
                cur = cur->next;
            }
        }
        return virtualHead->next;
    }
};
```

