
[toc]

# Leetcode 23. 合并K个排序链表

## 问题描述

[23. 合并K个排序链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/merge-k-sorted-lists/)

## 算法

### 解法1.1: k路归并

就是 [21. 合并两个有序链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/merge-two-sorted-lists/) 的一个简单拓展

每次都取k个链表头最小的那个。

时间复杂度：$O(kn)$ 因为每选出一个元素都需要 k 次比较
空间复杂度：
- 递归实现：$O(logn)$ 
- 迭代实现：$O(1)$ 

#### 解法1.1:实现: 递归

##### 解法1.1: python

```
class Solution:
    def mergeKLists(self, lists: List[ListNode]) -> ListNode:
        
        def helper(lists):
            if lists == []:
                return None

            minVal = float('inf')
            minIdx = -1
            minNode = None

            for i, node in enumerate(lists):
                if node.val < minVal:
                    minVal = node.val
                    minIdx = i
                    minNode = node
            lists[minIdx] = lists[minIdx].next
            if lists[minIdx] is None:
                lists.pop(minIdx)
            minNode.next = helper(lists)
            return minNode
        
        newLists = [node for node in lists if node is not None]
        return helper(newLists)
```

#### 解法1.2:实现:迭代

##### 解法1.2: python

```
class Solution:
    def mergeKLists(self, lists: List[ListNode]) -> ListNode:
        virtualHead = ListNode(0)
        cur = virtualHead

        lists = [node for node in lists if node is not None]

        minVal = float('inf')
        minIdx = -1

        while lists != []:
            for i in range(len(lists)):
                if lists[i] is None: continue
                if lists[i].val < minVal:
                    minVal = lists[i].val
                    minIdx = i
                    cur.next = lists[i]

            cur = cur.next

            if lists[minIdx].next is None:
                lists.pop(minIdx)
            else:
                lists[minIdx] = lists[minIdx].next
            minVal = float('inf') # 注意这里需要将 minVal 还原成 minVal。否则会bug!

        return virtualHead.next
```

### 解法2: k路归并 + 堆

上面的实现中，每选择一个最小值就需要 k 次比较。这个可以用一个大小为 k 的小根堆来优化。

#### 解法2:实现

##### 解法2: c++

```
class Solution {
public:
    struct cmp {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, cmp> heap;
        int size = 0;
        for (auto node: lists) {
            if (node) heap.push(node);
        }
        
        ListNode virtualHead, *cur = &virtualHead;

        while (!heap.empty()) {
            cur->next = heap.top();
            cur = cur->next;
            heap.pop();
            if (cur->next) heap.push(cur->next);
        }
        return virtualHead.next;
    }
};
```

##### 解法2: python

```
import heapq
class Solution:
    def mergeKLists(self, lists: List[ListNode]) -> ListNode:
        k = len(lists)
        if k == 0: return None
        if k == 1: return lists[0]

        heap = []

        for i in range(k):
            if lists[i]:
                heapq.heappush(heap, (lists[i].val, i))

        virtualHead = ListNode(-1)
        p = virtualHead

        while heap:
            val, i = heap[0]
            p.next = lists[i]
            p = p.next
            heapq.heappop(heap)

            lists[i] = lists[i].next
            if lists[i]:
                heapq.heappush(heap, (lists[i].val, i))
        return virtualHead.next
```

##### 解法2: python 猴子补丁

```
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def mergeKLists(self, lists: List[ListNode]) -> ListNode:
        virtualHead = ListNode(-1)
        p = virtualHead
        h = []
        
        ListNode.__lt__ = lambda this, that: this.val < other.val
        
        for head in lists:
            if head: 
                heapq.heappush(h, head)
        while h:
            node = heapq.heappop(h)
            p.next = node
            if node.next: heapq.heappush(h, node.next)
            p = p.next
        return virtualHead.next
```


### 解法3: 分治

#### 复杂度分析

假设n 是 平均每个链表的长度，k 是链表的个数，下面进行复杂度分析

##### 时间复杂度： $O(nklogk)$

假设 k 个链表，每个链表的长度都是 n，则要求的时间复杂度为 $T(nk)$。将其分成两组链表，每组分别为 $k/2$ 个 长度为 n 的链表，因此，解决两个子问题的时间复杂度为 $2 T(nk/2)$。两个子问题解决后返回两个长度均为 $nk/2$ 的链表，将这两个链表合并的时间复杂度为 $O(nk/2)$，因此，有下面的公式：

$$
T(nk) = 2 T(nk/2) + O(nk/2)
$$

假设 $2^l = k$，并继续向下推导，有

$$
\begin{aligned}
T(nk) &= 2T(nk/2) + O(nk/2) \\
    &= 2(2T(nk/4) + O(nk/4)) + O(nk/2) \\
    &=  4T(nk/4) + 2O(nk/4) + O(nk/2) \\
    &= 4T(nk/4) + 2O(nk/2) \\
    &= 2^2T(nk/2^2) + 2O(nk/2) \\
    &= \cdots \\
    &= 2^l T(nk/2^l) + l O(nk/2) \\
    &= k T(n) + O(nkl/2)
\end{aligned}
$$

$T(n)$ 表示有一个长度为 n 的链表对其合并，时间复杂度为 $O(1)$（因为只有一个，不需要任何操作直接返回就好）。

因此，有

$$
\begin{aligned}
T(nk) &= 2T(nk/2) + O(nk/2) \\
    &= k T(n) + O(nkl/2) \\
    &=  k O(1) + O(nkl/2) \\
    &= O(k) + O(nk log k /2)  (2^l=k => l=log k)\\ 
    &= O(nklogk)
\end{aligned}
$$ 

最后一步是因为（$O(k)$ 和 $O(nklogk/2)$ 相比可以忽略，同时 $O(nk logk/ 2）$中的常数 2 也可以忽略）

##### 空间复杂度

递归需要用到栈，深度为 $O(log k)$


#### 解法3: 实现

##### 解法3:c++

```
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return helper(0, lists.size()-1, lists);
    }

    ListNode* helper(int low, int high, const vector<ListNode*>& lists) {
        if (low > high) return NULL;
        if (low==high) return lists[low];
        int mid = low + ((high - low) >> 1);
        return mergeTwoLists(helper(low, mid, lists), helper(mid+1, high, lists));
    }

    ListNode* mergeTwoLists(ListNode* head1, ListNode* head2) {
        if (!head1 || !head2) return head1 ? head1: head2;
        if (head1->val <= head2->val) {
            head1->next = mergeTwoLists(head1->next, head2);
            return head1;
        } else {
            return mergeTwoLists(head2, head1);
        }
    }
};
```
##### 解法3: python

```
class Solution:
    def mergeKLists(self, lists: List[ListNode]) -> ListNode:
        n = len(lists)
        if n==0: return None
        if n==1: return lists[0]
        mid = n // 2
        left = self.mergeKLists(lists[:mid])
        right = self.mergeKLists(lists[mid:])
        return self.mergeTwoLists(left, right)
        
    def mergeTwoLists(self, head1, head2):
        if not head1: return head2
        if not head2: return head1
        
        virtualHead = ListNode(-1)
        p = virtualHead
        while head1 and head2:
            if head1.val < head2.val:
                p.next = head1
                head1 = head1.next
            else:
                p.next = head2
                head2 = head2.next
            p = p.next
        if head1:
            p.next = head1
        else:
            p.next = head2
        return virtualHead.next
```
# References
1. [C++ 二次遍历(超时)/分治思想/优先队列 - 合并K个排序链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/merge-k-sorted-lists/solution/c-er-ci-bian-li-chao-shi-fen-zhi-si-xiang-by-yizhe/)
2. [合并 K 个排序链表 - 合并K个排序链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/merge-k-sorted-lists/solution/leetcode-23-he-bing-kge-pai-xu-lian-biao-by-powcai/)

