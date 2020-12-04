[toc]

# Leetcode 142. 环形链表 II

## 问题描述

[142. 环形链表 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/linked-list-cycle-ii/)

给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 `null`。

为了表示给定链表中的环，我们使用整数 `pos` 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 `pos` 是 `-1`，则在该链表中没有环。

**说明：**不允许修改给定的链表。

**示例 1：**
**输入：**head = \[3,2,0,\-4\], pos = 1
**输出：**tail connects to node index 1
**解释：**链表中有一个环，其尾部连接到第二个节点。

![0ac1c374da73504066d5990dc7ea7cbb.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p13950)

**示例 2：**
**输入：**head = \[1,2\], pos = 0
**输出：**tail connects to node index 0
**解释：**链表中有一个环，其尾部连接到第一个节点。

![80070274b753fb6017362bc5b5bb1195.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p13949)

**示例 3：**
**输入：**head = \[1\], pos = \-1
**输出：**no cycle
**解释：**链表中没有环。

![faeeb9031a07904b5fb959efd28ee031.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p13948)

**进阶：**
你是否可以不用额外空间解决此题？

### 解法1:hashtab

#### 解法1: 实现

##### 解法1: 实现：python

```
class Solution:
    def detectCycle(self, head: ListNode) -> ListNode:
        seen = set()
        while head is not None:
            if head in seen:
                return head
            seen.add(head)
            head = head.next
        return None
```

### 解法2: 快慢指针

分为两步：

1. 设置两个指针 fast 和 slow，均从链表的头部开始向前走， fast  的速度为2，slow 的速度为1，那么如果有环，两个指针一定在环的某点相遇.

2. 当 fast 和 slow 机遇时，再设置一个新的指针 p，速度为 1， slow 和 p 同时走，当 slow 和 p 相遇时，相遇点便是环的入口点。

#### 证明

![](https://gitee.com/EdwardElric_1683260718/picture_bed/raw/master/img/20201204233349.png) 

慢指针的路程   x + s
快指针的路程 x + s + al。其中 a 是快指针走的环数。

根据快慢指针的速度关系，有

```
2 ( x + s) = x + s + al 
--> x + s = al 
--> x = (a-1)l + l - s
```

这个说明，如果我们在第一次相遇后，再设置一个 p 指针为头节点，然后 p 和 slow 同时速度为 1 走，
1. 当 p 走 x 步后，停在了环的入口处
2. 此时 slow 走了 `(a-1) l + l - s` 步，如果将入口节点看作起点 0 的话，slow 的起始位置为 s, 走了 `(a-1) l + l -s` 步，停在 `(a-1) l + l - s + s = al`，相当于停在了环的入口处。

因此此时 p 和 slow 会在环的入口处相遇。


#### 解法2: 实现

##### 解法2: 实现：c++

```
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head==nullptr) return nullptr;
        ListNode *fast = head, *slow = head;
        while (true) {
            fast = fast -> next;
            if (fast == nullptr) return nullptr;
            fast = fast -> next;
            if (fast ,== nullptr) return nullptr;
            slow = slow -> next;
            if (fast == slow) break;
        }
        
        ListNode *p = head;
        while (p != slow) {
            p = p->next;
            slow = slow->next;
        }
        return p;
    }
};
```

##### 解法2: 实现：python

```
class Solution:
    def detectCycle(self, head: ListNode) -> ListNode:
        if not head or not head.next: return None
        slow = fast = head
        while True:
            if not fast.next or not fast.next.next:
                return None
            fast = fast.next.next
            slow = slow.next
            if slow == fast:
                break
        
        slow = head
        while slow != fast:
            fast = fast.next
            slow = slow.next
        return slow
```