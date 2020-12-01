[toc]

# Leetcode 1669. 合并两个链表

## 问题描述

[1669. 合并两个链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/merge-in-between-linked-lists/)

给你两个链表 `list1` 和 `list2` ，它们包含的元素分别为 `n` 个和 `m` 个。

请你将 `list1` 中第 `a` 个节点到第 `b` 个节点删除，并将`list2` 接在被删除节点的位置。

下图中蓝色边和节点展示了操作后的结果：

![](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/11/28/fig1.png)

请你返回结果链表的头指针。

**示例 1：**

![](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/11/28/merge_linked_list_ex1.png)

**输入：**list1 = \[0,1,2,3,4,5\], a = 3, b = 4, list2 = \[1000000,1000001,1000002\]
**输出：**\[0,1,2,1000000,1000001,1000002,5\]
**解释：**我们删除 list1 中第三和第四个节点，并将 list2 接在该位置。上图中蓝色的边和节点为答案链表。

**示例 2：**

![](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/11/28/merge_linked_list_ex2.png)

**输入：**list1 = \[0,1,2,3,4,5,6\], a = 2, b = 5, list2 = \[1000000,1000001,1000002,1000003,1000004\]
**输出：**\[0,1,1000000,1000001,1000002,1000003,1000004,6\]
**解释：**上图中蓝色的边和节点为答案链表。

**提示：**

*   `3 <= list1.length <= 104`
*   `1 <= a <= b < list1.length - 1`
*   `1 <= list2.length <= 104`

## 算法

### 解法1：模拟法

题目比较良心，输入没有什么特殊情况。直接模拟就好

时间复杂度：$O(n + m)$

#### 解法1: 实现


##### 解法1: 实现: python

```
class Solution:
    def mergeInBetween(self, list1: ListNode, a: int, b: int, list2: ListNode) -> ListNode:
   
        cur = list2
        while cur.next:
            cur = cur.next
        list2_tail = cur # 获得 list2 的尾节点
        
        cur = list1   
        i = 0 # i 表示当前 cur 是 list1 的第 i 个节点
        while i - 1 < b: # i - 1 == b 时退出
            nextNode = cur.next
            if i + 1 == a: # i + 1 == a 说明 nextNode == 是要删除的第一个元素
                cur.next = list2
            # cur向前移动 同时 i+=1
            cur = nextNode
            i += 1
        # 此时 i - 1 == b，即 cur 的前一个元素是要删除的最后一个元素
        list2_tail.next = cur
        return list1
```
                
            
            
        