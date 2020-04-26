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

参考了 [1]

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

### 解法3: 分治

转化为两个两个合并。

# Todo - 2020-04-26 23:28 -- by ed 这个复杂度分析不会！

时间复杂度：$O( )$ 
空间复杂度：$$ 

#### 解法3:实现

##### 解法3: 

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

# References
1. [C++ 二次遍历(超时)/分治思想/优先队列 - 合并K个排序链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/merge-k-sorted-lists/solution/c-er-ci-bian-li-chao-shi-fen-zhi-si-xiang-by-yizhe/)
