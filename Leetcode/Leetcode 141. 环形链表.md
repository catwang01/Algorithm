[toc]

# Leetcode 141. 环形链表

## 问题描述

[141. 环形链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/linked-list-cycle/)

## 算法

### 解法1：hash

#### 解法1：实现

##### 解法1：java

```
public boolean hasCycle(ListNode head) {
    Set<ListNode> nodesSeen = new HashSet<>();
    while (head != null) {
        if (nodesSeen.contains(head)) {
            return true;
        } else {
            nodesSeen.add(head);
        }
        head = head.next;
    }
    return false;
}
```

### 解法2:快慢指针

注意点：
1. slow = head, fast = head.next 这样设初始值是为了可以进入 while 循环，没有什么特殊的深意。实际上只要有环，两个指针一定会相遇，和初始值关系不大。
2. 速度设置为1:2可以保证不会出现快慢指针正好错过的情况。因为当进入环之后，慢指针走一步，快指针走两步，相当于它们之间的距离减1。

![9459700e523cd13354ad349723335de1.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p11283)

#### 解法2:实现

##### 解法2:java

```
public boolean hasCycle(ListNode head) {
    if (head == null || head.next == null) {
        return false;
    }
    ListNode slow = head, fast = head.next;
    while (slow != fast) {
        if (fast == null || fast.next == null) {
            return false;
        }
        slow = slow.next;
        fast = fast.next.next;
    }
    return true;
}
```

##### 解法2: 实现：python

```
class Solution:
    def hasCycle(self, head: ListNode) -> bool:
        if not head or not head.next: return False
        slow, fast = head, head.next
        while fast != slow:
            slow = slow.next
            if not fast.next or not fast.next.next:
                return False
            fast = fast.next.next
        return True
```

##### 解法2: c++

```
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == nullptr || head->next == nullptr)
            return false;
        ListNode *slow = head, *fast = head->next;
        while (fast != nullptr && slow != fast)
        {
            fast = fast -> next;
            if (fast == nullptr)
            {
                return false;
            }
            else
            {
                fast = fast->next;
                slow = slow->next;
            }
        }
        if (fast == nullptr)
            return false;
        else
            return true;
    }
};
```
