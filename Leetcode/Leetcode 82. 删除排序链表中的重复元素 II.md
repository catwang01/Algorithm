[toc]

# Leetcode 82. 删除排序链表中的重复元素 II 

## 问题描述

[82. 删除排序链表中的重复元素 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/)

相似题目：[83. 删除排序链表中的重复元素 - 力扣（LeetCode）](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/)

## 算法

### 解法1: 虚拟头结点

这个和 [83. 删除排序链表中的重复元素 - 力扣（LeetCode）](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/) 的区别是 83 中重复元素需要保留一个，不会全部删除。

而本题重复元素需要全部删除。因此头结点可能变。所有需要使用虚拟头结点。

本题 while 循环的不变式为

prev 指向的是链表中第一个不重复的元素，起始时指向我们添加的虚拟头结点 virtualHead。

循环的停止条件当然是 prev == null，表示所有的元素都遍历完。不过，考虑到0个结点和1个结点不可能产生重复，因此不需要 prev == null 来判断是否重复。 prev->next == null 和 prev->next->next == null 就可以停止循环了！

#### 解法1:实现

##### 解法1: c++

```
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode node(0), *virtualHead = &node;
        virtualHead->next = head;
        ListNode *prev = virtualHead, *next;

        // 不变式： prev 下指向的是第一个没有重复的元素
        while (prev && prev->next && prev->next->next) {
            next = prev->next->next;
            bool isduplicate = false;
            while (next && prev->next->val == next->val) {
                isduplicate = true;
                next = next->next;
            } 
            if (isduplicate) prev->next = next;
            else prev = prev->next;
        }
        return virtualHead->next;
    }
};
```


