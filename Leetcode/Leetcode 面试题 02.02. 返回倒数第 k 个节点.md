[toc]

# Leetcode 面试题 02.02. 返回倒数第 k 个节点

## 问题描述

[面试题 02.02. 返回倒数第 k 个节点 - 力扣（LeetCode）](https://leetcode-cn.com/problems/kth-node-from-end-of-list-lcci/)

## 算法

### 解法1: 计算长度

```cpp
class Solution {
public:
    int kthToLast(ListNode* head, int k) {
        int len = getLen(head);
        if (len < k) return -1;
        for (int i=0; i<len-k; i++)
        {
            head = head->next;
        }
        return head->val;
    }

    int getLen(ListNode* head) 
    {
        int ret = 0;
        for (ListNode* p = head; p!=NULL; p=p->next)
        {
            ret ++;
        }
        return ret;
    }
};
```

### 解法2: 快慢指针

#### 解法2:实现

##### 解法2: c++

```cpp
class Solution {
public:
    int kthToLast(ListNode* head, int k) {
        ListNode* slow=head, *fast=head;
        for (int i=0; i<k; i++)
        {
            if (!fast) return -1; // 长度小于 k
            fast = fast->next;
        }
        while (fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
        return slow->val;
    }
};
```
