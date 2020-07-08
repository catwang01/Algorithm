
[toc]

# Leetcode 21. 合并两个有序链表 

## 问题描述

[21. 合并两个有序链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/merge-two-sorted-lists/)

将两个有序链表合并为一个新的有序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

示例：

输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4

### 解法一：递归

#### 解法一: 实现

##### 解法一: python

```
class Solution:
    def mergeTwoLists(self, l1: ListNode, l2: ListNode) -> ListNode:
        if l1 is None: return l2
        if l2 is None: return l1
        if l1.val <= l2.val:
            l1.next = self.mergeTwoLists(l1.next, l2)
            return l1
        else:
            return self.mergeTwoLists(l2, l1)
```

时间复杂度：$O(n+m)$ 。 因为每次调用递归都会去掉 `l1` 或者 `l2` 的头元素（直到至少有一个链表为空），函数 `mergeTwoList` 中只会遍历每个元素一次。所以，时间复杂度与合并后的链表长度为线性关系。

空间复杂度：$O(n+m)$ 。调用 `mergeTwoLists` 退出时 `l1` 和 `l2` 中每个元素都一定已经被遍历过了，所以 n+m 个栈帧会消耗 $O(n+m)$ 的空间。

### 解法二：迭代

时间复杂度： $O(n+m)$ 最坏情况下遍历两条链
空间复杂度： $O(1)$ 只需要几个指针，是常数大小

![8f70f3124384ca0196a7a4537765ef8c.jpeg](evernotecid://7E3AE0DC-DC71-4DDC-9CC8-0C832D6C11C2/appyinxiangcom/22483756/ENResource/p10713)

#### 解法二: 实现

##### 解法二: python

```
class Solution:
    def mergeTwoLists(self, l1: ListNode, l2: ListNode) -> ListNode:
        virtualHead = ListNode(0) # 虚拟结点
        cur = virtualHead           # 工作指针
        while l1 is not None and l2 is not None:
            if l1.val <= l2.val:
                cur.next = l1
                l1 = l1.next
            else:
                cur.next = l2
                l2 = l2.next
            cur = cur.next
        if l1 is None:
            cur.next = l2
        else:
            cur.next = l1
        return virtualHead.next
```

# References
- [漫画图解：绝对一眼就能看懂的强力解法！ - 合并两个有序链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/merge-two-sorted-lists/solution/man-hua-ti-jie-by-ivan1-2/)
