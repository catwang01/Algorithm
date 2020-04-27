[toc]

# Leetcode 83. 删除排序链表中的重复元素

## 问题描述

[83. 删除排序链表中的重复元素 - 力扣（LeetCode）](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/)

## 算法

### 解法1: 

#### 解法1:实现

##### 解法1: c++

```
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode *prev = head, *next = head->next;
        while (next) {
            if (prev->val == next->val) {
                prev->next = next ? next->next : NULL;
            } else {
                prev = prev->next;
            }
            next = prev->next;
        }
        return head;    
    }
};
```

