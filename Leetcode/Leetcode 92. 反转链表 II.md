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
        i = 0
        while i + 1 < m:
            cur = cur.next 
            i += 1
        newNext = self.reverse(cur.next, m, n)
        cur.next.next = self.nextNode
        cur.next = newNext
        return virtualHead.next

    def reverse(self, head, m, n):
        if m == n:
            self.nextNode = head.next
            head.next = None
            return head
        newhead = self.reverse(head.next, m+1, n)
        head.next.next = head
        return newhead
```

### 解法2: 迭代

#### 解法2: 实现：

##### 解法2: 实现： python

```
class Solution:
    def reverseBetween(self, head: ListNode, m: int, n: int) -> ListNode:
        if m == n: return head
        virtualHead = ListNode(-1)
        virtualHead.next = head
        node = virtualHead
        i = 0 # 表示当前 node 的编号
        while i + 1 < m:
            node = node.next
            i += 1
        nodeMm1 = node # 编号为 m - 1 的节点
        # 指针前移，此时node是
        node = node.next
        i += 1
        nodeM = node 

        cur = None
        
        while i < n:
            nextNode = node.next
            node.next = cur
            cur = node
            node = nextNode
            i += 1
        # 此时 node 是编号为n的节点
        nodeNp1 = node.next # node n+1
        node.next = cur
        cur = node
        nodeMm1.next = cur
        nodeM.next = nodeNp1
        return virtualHead.next
```