[toc]


# Leetcode 面试题 02.04. 分割链表

## 题目描述

[面试题 02.04. 分割链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/partition-list-lcci/)

## 算法

### 解法1: 快慢指针？

这个类似快速排序或者快速选择算法，只不过是链表版本。

#### 解法1: 实现

##### 解法1: c++

```cpp
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        if (!head || !head->next) return head;

        // 虚拟头结点
        ListNode virtualHead(0), *p = &virtualHead;
        p->next = head;

        ListNode *slow = p, *fast_prev = p, *fast = head;
        while (fast) {
            if (fast->val < x) {
                if (slow != fast_prev) {
                    fast_prev -> next = fast -> next;
                    fast -> next = slow -> next;
                    slow -> next = fast;

                    fast = fast_prev -> next;
                    slow = slow -> next;
                } else {
                    slow = slow -> next;
                    fast_prev = fast;
                    fast = fast->next;
                }
            } else {
                fast_prev = fast;
                fast = fast->next;
            }
        }
        return virtualHead.next;
    }
};
```
