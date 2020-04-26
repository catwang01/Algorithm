[toc]

# Leetcode 92. 反转链表 II 

## 问题描述

[92. 反转链表 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/reverse-linked-list-ii/)

## 算法

### 解法1: 递归

图示

![](https://gitee.com/EdwardElric_1683260718/picture_bed/raw/master/img/20200426182333.png)

#### 解法1:实现

##### 解法1: python

```
class Solution:
    def reverseBetween(self, head: ListNode, m: int, n: int) -> ListNode:
        if head is None or head.next is None: 
            return head

        virtualHead = ListNode(0)
        virtualHead.next = head

        cur = virtualHead
        for i in range(m-1):
            cur = cur.next
        start = cur
        
        for i in range(n-m+2):
            cur = cur.next
        end = cur
        newHead = self.reverse(start.next, end)
        start.next.next = end
        start.next = newHead
        return virtualHead.next
    
    def reverse(self, head, end):
        if head is None or head.next is None or head.next == end:
            return head
        newHead = self.reverse(head.next, end)
        head.next.next = head
        return newHead
```

