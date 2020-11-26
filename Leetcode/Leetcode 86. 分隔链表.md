[toc]

# Leetcode 86. 分隔链表

## 问题描述

[86. 分隔链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/partition-list/)
## 算法

### 解法1: 头插法

使用虚拟头结点。注意要断链！

#### 解法1:实现

##### 解法1: c++

```
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        if (!head || !head->next) return head;
        ListNode node1(0), node2(0);
        ListNode *bigHead=&node1, *smallHead=&node2;
        ListNode *cur1 = bigHead, *cur2 = smallHead;
        for (auto cur=head; cur != NULL; cur=cur->next) {
            cout << cur->val << endl;
            if (cur->val < x) {
                cur2->next = cur;
                cur2 = cur2->next;
            } else {
                cur1->next = cur;
                cur1 = cur1->next;
            }
        }
        cur2->next = bigHead->next;
        cur1->next = NULL; // 注意断链
        return smallHead->next;
    }
};
```


##### 解法1: 实现： python

```
class Solution:
    def partition(self, head: ListNode, x: int) -> ListNode:
        virtualHeadSmall = ListNode(-1)
        virtualHeadBig = ListNode(-1)
        curSmall, curBig = virtualHeadSmall, virtualHeadBig
        while head:
            if head.val < x:
                curSmall.next = head
                nextNode = head.next
                head.next = None
                head = nextNode
                curSmall = curSmall.next
            else:
                curBig.next = head
                nextNode = head.next
                head.next = None
                head = nextNode
                curBig = curBig.next
        curSmall.next = virtualHeadBig.next
        return virtualHeadSmall.next
```