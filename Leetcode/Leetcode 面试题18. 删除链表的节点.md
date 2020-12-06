[toc]

# Leetcode 剑指 Offer 18. 删除链表的节点

## 问题描述

[剑指 Offer 18. 删除链表的节点 - 力扣（LeetCode）](https://leetcode-cn.com/problems/shan-chu-lian-biao-de-jie-dian-lcof/)

## 算法

### 解法1: 迭代

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


##### 解法1: python

```
class Solution:
    def deleteNode(self, head: ListNode, val: int) -> ListNode:
        virtualHead = ListNode(-1)
        virtualHead.next = head
        curNode = virtualHead
        while curNode and curNode.next:
            nextNode = curNode.next
            while nextNode and nextNode.val == val:
                nextNode = nextNode.next
            curNode.next = nextNode
            curNode = nextNode
        return virtualHead.next
```

### 解法2: 递归

递归就不需要虚拟节点了。

#### 解法2: 实现：递归

##### 解法2: 实现：python

```
class Solution:
    def deleteNode(self, head: ListNode, val: int) -> ListNode:
        if not head: return head
        if head.val == val:
            return self.deleteNode(head.next, val)
        else:
            head.next = self.deleteNode(head.next, val)
            return head
```