[toc]

# Leetcode 143. 重排链表

## 问题描述

[143. 重排链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/reorder-list/)

## 算法

### 解法1: 数组法

链表无法实现快速访问下标，因此可以使用数组来保存结点的指针。来实现快速访问下标

1. 循环不变式 

```
[0, i) 和 [j, n) 是处理过的结点
```

2. 
因此需要初始化为 i=0, j = n, 使用开始时两个集合中没有元素。

3. 停止条件

```
i==j 此时可以保证 [0, i) 和 [j,n) 两个区间不重不漏覆盖整个集合
```
因此循环条件为 `i<j` 


#### 解法1:实现

##### 解法1: c++

```
class Solution {
public:
    void reorderList(ListNode* head) {
        vector<ListNode*> nodes;
        while (head) {
            nodes.push_back(head);
            head = head->next;
            nodes.back()->next = NULL; // 如数组后断链,不进行这一步会报错
        }
        ListNode node(0), *virtualHead=&node, *cur=virtualHead;
        int i=0, j=nodes.size();
        while (i<j) {
            cur->next = nodes[i++];
            cur = cur->next;
            if (i<j) {
                cur->next = nodes[--j]; 
                cur = cur->next;
            }
        }
    }
};
```

### 解法2: 递归

每次都将头结点接到尾结点上。然后剩下的任务交给递归来完成。记得要断链。

#### 解法2:实现

##### 解法2: 

```
class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next || !head->next->next) return;
        // 尾结点之前的结点
        ListNode* tailprev = head;
        while (tailprev->next->next) tailprev = tailprev->next;
        ListNode *tail = tailprev->next;
        tailprev->next = NULL; // 断链
        reorderList(head->next);
        tail->next = head->next;
        head->next = tail;
    }
};
```

### 解法3: 划分为三个小问题

问题可以划分为下面三个问题

1. 找到链表的中点, 从中间将链表断开，设新得到链表头结点为 newHead。
这个实际上是 [876. 链表的中间结点 - 力扣（LeetCode）](https://leetcode-cn.com/problems/middle-of-the-linked-list/) 的变种。 876 题是快慢指针从相同的起点出发。本题需要快指针从慢指针的下一个指针开始出发。
2. 将 newHead 反转；
这个是[206. 反转链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/reverse-linked-list/) 的问题。其中反转这一步操作也可以使用栈
3. 将 head 和 newHead 合并;
这个类似于 [21. 合并两个有序链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/merge-two-sorted-lists/)

#### 解法3:实现

##### 解法3: 

```
class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next || !head->next->next) return;
        ListNode *mid = midNode(head);
        ListNode *newHead = reverse(mid->next);
        mid->next = NULL;
        merge(head, newHead);
    }

    ListNode* midNode(ListNode* head) {
        ListNode *slow= head, *fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next;
            if (fast) fast = fast->next;
        }
        return slow;
    }

    ListNode* reverse(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode* newHead = reverse(head->next);
        head->next->next = head;
        head->next = NULL;
        return newHead;
    }

    ListNode* merge(ListNode* head1, ListNode* head2) {
        ListNode node(0), *virtualHead=&node, *cur=virtualHead;
        while (head1) {
            cur->next = head1;
            cur = cur->next;
            head1 = head1->next;
            if (head2) {
                cur->next = head2;
                cur = cur->next;
                head2 = head2->next;
            }
        }
        return virtualHead->next;
    }
};
```

# References
1. [详细通俗的思路分析，多解法 - 重排链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/reorder-list/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-34/)
