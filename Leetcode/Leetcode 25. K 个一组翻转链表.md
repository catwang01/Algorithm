[toc]

[toc]

# Leetcode  25. K 个一组翻转链表

## 问题描述

[25. K 个一组翻转链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/reverse-nodes-in-k-group/)

## 算法

### 解法1: 递归

# Todo - 2020-04-26 17:17 -- by ed 明天再说吧。今天这个脑壳疼。

#### 解法1:实现

##### 解法1: python

```
class Solution:
    def reverseKGroup(self, head: ListNode, k: int) -> ListNode:
        if head is None or head.next is None:
            return head
        node = head
        flag = True
        for i in range(k):
            if node is None:
                flag = False
                break
            node = node.next
        if not flag: return head
        newHead = self.reverse(head, node)
        head.next = self.reverseKGroup(node, k)
        return newHead

    # 反转链表
    def reverse(self, head, end):
        if head is None or head.next is None or head.next == end:
            return head
        newHead = self.reverse(head.next, end)
        head.next.next = head
        return newHead
```
