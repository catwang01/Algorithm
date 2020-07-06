[toc]

# Leetcode 148. 排序链表

## 问题描述

[148. 排序链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/sort-list/)

## 算法

### 解法1: 归并排序

使用对于链表的归并排序

1. 分成两个子链需要找中点，这个相当于  [876. 链表的中间结点 - 力扣（LeetCode）](https://leetcode-cn.com/problems/middle-of-the-linked-list/)

2. 其中合并的逻辑类型于下面的题目 [21. 合并两个有序链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/merge-two-sorted-lists/)

#### 解法1:实现

这里使用断链的方法来解决部分遍历操作的问题。

##### 解法1: c++

```
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        return mergeSort(head, getLen(head));
    }

    ListNode* mergeSort(ListNode* head, int len) {
        if (len<=1) return head;
        ListNode *cur = head, *next;
        int mid = len >> 1;
        for (int i=0; i<mid-1; i++) cur = cur->next;
        next = cur->next;
        cur->next = NULL; // 断链
        return merge(mergeSort(head, mid), mergeSort(next, len-mid));
    }

    ListNode* merge(ListNode* head1, ListNode* head2) {
        if (!head1 || !head2) return head1? head1: head2;
        if (head1->val <= head2->val) {
            head1->next = merge(head1->next, head2);
            return head1;
        }
        return merge(head2, head1);
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


##### 解法1: python

```
class Solution:
    def sortList(self, head: ListNode) -> ListNode:
        if not head or not head.next: return head
        
        mid = self.findMid(head)
        left, right = head, mid.next
        mid.next = None
        left = self.sortList(left)
        right = self.sortList(right)
        return self.mergeTwo(left, right)
        
    def mergeTwo(self, head1, head2):
        virtualHead = ListNode(-1)
        p = virtualHead
        while head1 and head2:
            if head1.val <= head2.val:
                p.next = head1
                p = p.next
                head1 = head1.next
            else:
                p.next = head2
                p = p.next
                head2 = head2.next
        if head1:
            p.next = head1
        else:
            p.next = head2
        return virtualHead.next
                
    def findMid(self, head):
        slow, fast = head, head.next
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
        return slow
```
