
[toc]

# Leetcode 剑指 Offer 22. 链表中倒数第k个节点

## 问题描述
[剑指 Offer 22. 链表中倒数第k个节点 - 力扣（LeetCode）](https://leetcode-cn.com/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof/)

## 算法

### 解法1: 快慢指针

#### 解法1: 实现

##### 解法1: python

```
class Solution:
    def getKthFromEnd(self, head: ListNode, k: int) -> ListNode:
        p = head
        for i in range(k):
            if p is not None:
                p = p.next
                return None # 链表长度不足 k 
        q = head
        while p:
            p = p.next
            q = q.next
        return q
```
