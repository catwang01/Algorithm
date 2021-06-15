[toc]

# Leetcode 24. 两两交换链表中的节点

## 问题描述

[24. 两两交换链表中的节点 - 力扣（LeetCode）](https://leetcode-cn.com/problems/swap-nodes-in-pairs/)

给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。

**你不能只是单纯的改变节点内部的值**，而是需要实际的进行节点交换。

**示例:**

给定 `1->2->3->4`, 你应该返回 `2->1->4->3`.


## 算法


### 解法1：递归

![f88791b4912792dbb5a7885855b1dda9.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p10769)

#### 解法1：实现

##### 解法1：实现：python

```
class Solution:
    def swapPairs(self, head: ListNode) -> ListNode:
        if not head or not head.next: return head
        p = head.next
        head.next = self.swapPairs(p.next)
        p.next = head
        return p
```

##### 解法1：实现：C++

```
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head==NULL||head->next==NULL)
            return head;
        ListNode* p = head->next;
        head->next = swapPairs(p->next);
        p->next = head;
        return p;
    }
};
```

### 解法二：三指针

![](https://gitee.com/EdwardElric_1683260718/picture_bed/raw/master/img/20201209174606.png)

#### 解法2：实现

##### 解法2：实现：c++

```
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head==NULL||head->next==NULL)
            return head;
        ListNode* first = head, *second, *third;
        head = head->next;
        while (first!=NULL && first->next!=NULL) {
            second = first->next;
            third = second -> next;
            if (third == NULL || third->next==NULL) first->next = third;
            else first->next = third->next;
            second->next = first;
            first = third;
        }
        return head;
    }
};
```

### 解法3: 虚拟头节点重建链表

#### 解法3: 实现


##### 解法3: 实现：python

```
class Solution:
    def swapPairs(self, head: ListNode) -> ListNode:
        virtualHead=  ListNode(-1) 
        cur = virtualHead
        while head:
            if head.next: # Node -> Node -> None
                nextNode = head.next.next
                head.next.next = None
                cur.next = head.next
                head.next.next = head
                head.next = None
                cur = head
            else: # Node -> None
                nextNode = head.next
                cur.next = head
                cur = head
            head = nextNode
        return virtualHead.next
```