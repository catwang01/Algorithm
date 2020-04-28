[toc]

# Leetcode 面试题52. 两个链表的第一个公共节点

## 问题描述

[面试题52. 两个链表的第一个公共节点 - 力扣（LeetCode）](https://leetcode-cn.com/problems/liang-ge-lian-biao-de-di-yi-ge-gong-gong-jie-dian-lcof/)

## 算法

### 解法1: 计算长度

#### 解法1:实现

##### 解法1: python

```
class Solution:
    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> ListNode:
        if not headA or not headB: return None
        lenA, lenB = self.getLen(headA), self.getLen(headB)
        print(lenA, lenB)
        if lenA >= lenB:
            for i in range(lenA-lenB):
                headA = headA.next

            while headA is not None:
                if headA == headB:
                    break
                headA = headA.next
                headB = headB.next
            return headA
        else:
            return self.getIntersectionNode(headB, headA)

    def getLen(self, head):
        ret = 0
        while head is not None:
            ret += 1
            head = head.next
        return ret
```

### 解法2: 

参考了 [1]

#### 解法2:实现

##### 解法2: 

```
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *p1 = headA, *p2 = headB;
        while (p1 != p2) {
            p1 = p1 ?p1->next: headB;
            p2 = p2 ?p2->next: headA;
        }
        return p1;
    }
};
```

# References
1. [面试题52. 两个链表的第一个公共节点 - 力扣（LeetCode）](https://leetcode-cn.com/problems/liang-ge-lian-biao-de-di-yi-ge-gong-gong-jie-dian-lcof/comments/) 
