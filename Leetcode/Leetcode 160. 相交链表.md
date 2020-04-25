[toc]

# Leetcode 160. 相交链表

## 问题描述

[160. 相交链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/intersection-of-two-linked-lists/)

## 算法

### 解法1：hash

时间复杂度： $O(n)$
空间复杂度： $O(n)$

遍历其中一个链表，将结点保存在 hashtab 中。然后遍历另一个链表，并逐个检查结点是否在 hashtab中，如果在hashtab中，就返回。如果所有的结点都不在 hashtab 中，则返回 null

#### 解法1:实现

##### 解法1:java

```
public class Solution {
    public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
        Set<ListNode> seen = new HashSet();
        while (headA != null) {
            seen.add(headA);
            headA = headA.next;
        }
        while (headB != null) {
            if (seen.contains(headB)) {
                return headB;
            } 
            headB = headB.next;
        }
        return null;
    }
}
```

##### 解法1:python

```
class Solution:
    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> ListNode:
        if not headA or not headB: 
            return None
        s = set()
        while headA is not None:
            s.add(headA)
            headA = headA.next
        while headB is not None:
            if headB in s: 
                return headB
            headB = headB.next
        return None
```

### 解法2：双指针1

时间复杂度： $O(n)$
空间复杂度： $O(1)$

如果list1 和 list2 长度相同的话，则同时只需要每个链表同时遍历。第一个相同的结点即是交点。

但是当 list1 和 list2 的长度不同时，先分别遍历两个链表，得到两个链表的长度分别为 m、n。假设 m > n，则将 list1 的指针向前移动 m - n 步。然后再相同移动两个指针即可。


#### 解法2:实现

##### 解法2:java

```
public class Solution {
    public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
        int nNodeA=0, nNodeB=0;
        ListNode pA = headA, pB = headB;
        while (pA!=null) {
            nNodeA++;
            pA = pA.next;
        }
        while (pB != null) {
            nNodeB++;
            pB = pB.next;
        }
        pA = headA;
        pB = headB;
        if (nNodeA > nNodeB) {
            for (int i=0; i<nNodeA-nNodeB; i++) {
                pA = pA.next;
            }
        } else {
            for (int i=0; i<nNodeB-nNodeA; i++) {
                pB = pB.next;
            }
        }
        while (pA != pB) { 
            pA = pA.next;
            pB = pB.next;
        }
        return pA;
    }
}
```

##### 解法2:python

```
class Solution:
    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> ListNode:
        if not headA or not headB: 
            return None
        lenA, lenB = self.getLen(headA), self.getLen(headB)
        if lenA >= lenB:
            for i in range(lenA - lenB):
                headA = headA.next
            while headA is not None:
                if headA == headB:
                    return headA
                headA = headA.next
                headB = headB.next
            return None
        else:
            return self.getIntersectionNode(headB, headA)


    def getLen(self, headA):
        ret = 0
        while headA is not None:
            ret += 1
            headA = headA.next
        return ret
```

### 解法2:双指针

错的人迟早会走散，而对的人迟早会相逢！

#### 解法2: 实现

##### 解法2: python

```
class Solution:
   def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> ListNode:
       if not headA or not headB: 
           return None
       nodeA, nodeB = headA, headB
       while nodeA is not None or nodeB is not None:
           if nodeA == nodeB:
               return nodeA
           nodeA = nodeA.next if nodeA else headB
           nodeB = nodeB.next if nodeB else headA
       return None
```
