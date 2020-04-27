[toc]

# Leetcode 61. 旋转链表

## 问题描述

[61. 旋转链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/rotate-list/)

## 算法

### 解法1: 

注意 k 有可能超过链表的长度。因此需要 k = k % len; 其中 len 是链表的长度

#### 解法1:实现

##### 解法1: c++

```
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (head==NULL || head->next==NULL) return head;
        k = k % getLen(head);
        if (k==0) return head;
        ListNode *slow=head, *fast= head;
        for (int i=0; i<k; i++) fast = fast->next;
        while (fast->next != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
        ListNode* newHead = slow->next;
        slow->next = NULL;
        fast->next = head;
        return newHead;
    }

    int getLen(ListNode* head) {
        int ret = 0;
        while (head) {
            ret ++;
            head = head->next;
        }
        return ret;
    }
};
```

