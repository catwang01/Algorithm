
[toc]

# Leetcode 328. 奇偶链表

## 问题描述

[328. 奇偶链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/odd-even-linked-list/)

## 算法

### 解法1

#### 解法1：实现

##### 解法1:java

```py
class Solution {
    public ListNode oddEvenList(ListNode head) {
        if (head == null || head.next == null || head.next.next == null) return head;
        ListNode odd = head, even = head.next, even_head = head.next;
        while (even != null && even.next != null) {
            odd.next = even.next;
            even.next = odd.next.next;
            odd.next.next = even_head;
            odd = odd.next;
            even = even.next;
        }
        return head;
    }
}
```

### 解法2: 尾插法

设置两个虚拟头部 virtualOdd 和 virtualEven，一个保存奇数节点，一个保存偶数节点，之后将两个链表拼接起来。

##### 解法2: c++

```py
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        ListNode virtualOdd, virtualEven, *next;
        ListNode *p1 = &virtualOdd, *p2 = &virtualEven;
        int i = 1;
        while (head)
        {
            next = head -> next;
            head->next = nullptr; // 断链
            if (i & 1) {
                p1 -> next = head;
                p1 = p1 -> next;
            } else {
                p2 -> next = head;
                p2 = p2->next;
            }
            i++;
            head = next;
        }
        p1 -> next = virtualEven.next;
        return virtualOdd.next;
    }
};
```