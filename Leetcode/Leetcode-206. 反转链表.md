[toc]

# Leetcode 206. 反转链表

## 问题描述

[206. 反转链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/reverse-linked-list/)

## 算法

### 解法1：递归

![9b31c463368a48b1c0f1409be8da6295.png](evernotecid://7E3AE0DC-DC71-4DDC-9CC8-0C832D6C11C2/appyinxiangcom/22483756/ENResource/p10972)

#### 解法1: 实现

##### 解法1： python

```
class Solution:
    def reverseList(self, head: ListNode) -> ListNode:
        if not head or not head.next:
            return head

        newhead = self.reverseList(head.next)
        head.next.next = head
        head.next = None
        return newhead
```

##### 解法1： c++

```
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode* newHead = reverseList(head->next);
        head->next->next = head;
        head->next = NULL;
        return newHead;
    }
};
```

### 解法二：迭代

使用迭代进行操作，首先肯定是使用指针，问题是使用几个指针。

1. 使用3个指针

首先肯定需要一个工作指针 cur，用来遍历所有的指针。

由于需要反转链表，所以需要将 cur 指向 cur 之前的元素，因此需要用一个指针来保存 cur 之前的指针，记为 prev。

当 cur 的指向改变是，cur.next 已经丢失了原来的指向而是指向 prev。因此不能使用 cur = cur.next 来向前移动 cur 指针，所以还需要一个 _next 指针来保存 cur 的下一个位置。


![90564076fbdf7b069d1260024982ca00.png](evernotecid://7E3AE0DC-DC71-4DDC-9CC8-0C832D6C11C2/appyinxiangcom/22483756/ENResource/p10971)

2. while 循环的停止条件是工作指针 cur 指向 None，说明链表遍历完成

3. 有一个细节： _next 指针不是在一开始就初始化好的，而是在while循环中初始化的，而且是在 while 的开始，而不是最后。即 

下面的代码是不对的

```
prev, cur, _next = None, head, head.next
while cur:
    cur.next = prev
    prev = cur 
    cur = _next 
    _next = cur.next
```

上面的写法是有bug的，因为当_next 指向 None 时，cur = _next 将 cur 变成了 None，此时再运行 _next = cur.next 即会报错！

因此需要修改为下面的形式，这样可以确保 while 条件判断 cur 不为 None 时再对 _next 赋值，即

```
prev, cur = None, head
while cur:
    _next = cur.next
    cur.next = prev
    prev = cur
    cur = _next
return prev
```

#### 解法二python

```
class Solution:
    def reverseList(self, head: ListNode) -> ListNode:
        if not head: return head

        prev, cur = None, head
        while cur:
            _next = cur.next
            cur.next = prev
            prev = cur
            cur = _next
        return prev
```

### 解法3: 头插法

#### 解法3: 实现

##### 解法3: c++

```
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *p = NULL, *next = NULL;
        while (head)
        {
            next = head->next;
            head->next = p;
            p = head;
            head = next;
        }
        return p;
    }
};
```
### 解法3: python

```
class Solution:
    def reverseList(self, head: ListNode) -> ListNode:
        virtualHead = ListNode(-1)
        p = virtualHead
        while head:
            nextNode = head.next
            head.next = p.next
            p.next = head
            head = nextNode
        return virtualHead.next
```