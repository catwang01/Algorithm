[toc]

# Leetcode  25. K 个一组翻转链表

## 问题描述

[25. K 个一组翻转链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/reverse-nodes-in-k-group/)

## 算法

### 解法1: 递归

#### 解法1:实现1: 断链

##### 解法1: python

```
class Solution:
    def reverseKGroup(self, head: ListNode, k: int) -> ListNode:
        i = 1
        p = head
        while p and i < k:
            p = p.next
            i += 1
        if p is None: return head
        newhead = self.reverseKGroup(p.next, k)
        p.next = None
        self.reverse(head)
        head.next = newhead
        return p

    def reverse(self, head):
        if head is None or head.next is None:
            return head
        newhead = self.reverse(head.next)
        head.next.next = head
        head.next = None
        return newhead
```

##### 解法1: c++

```
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == NULL) return head;
        ListNode* cur = head;
        int i = 0;
        while (i < k-1 && cur->next != NULL) {
            cur = cur->next;
            i++;
        }
        if (i==k-1) {
            ListNode* newhead = reverseKGroup(cur->next, k);
            cur->next = NULL;
            reverse(head);
            head->next = newhead;
            return cur;
        }
        return head;  
    }

    ListNode* reverse(ListNode* head) {
        if (head==NULL || head->next == NULL) {
            return head;
        }
        ListNode* newhead = reverse(head->next);
        head->next->next = head;
        head->next = NULL;
        return newhead;
    }
};
```

#### 解法1:实现2: 使用end

上面的实现中使用断链的方法，来避免链表遍历不知道末尾的问题。还可以使用一个end结点。如果链表指向 end 结点时，说明可以停止遍历了。可以看到，一般的链表遍历实际上是 end 为 NULL 时的一种特殊情况。

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