[toc]

# Leetcode 147. 对链表进行插入排序

## 问题描述

[147. 对链表进行插入排序 - 力扣（LeetCode）](https://leetcode-cn.com/problems/insertion-sort-list/)

```
class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        ListNode node;
        ListNode* virtualHead = &node;
        ListNode *cur = head, *next;
        while (cur != NULL) {
            next = cur->next;
            cur->next = NULL;
            insert(virtualHead, cur);
            cur = next;
        }
        return virtualHead->next;
    }

    void insert(ListNode* head, ListNode* node) {
        if (head->next == NULL) {
            head->next = node;
            return;
        }
        while (head->next != NULL) {
            if (head->next->val < node->val) {
                head = head->next;
            } else {
                node->next = head->next;
                head->next = node;
                return;
            }
        }
        head->next = node;
        return;
    }
};
```

# References

1. [147. 对链表进行插入排序 - 力扣（LeetCode）](https://leetcode-cn.com/problems/insertion-sort-list/)
