
[toc]

# Leetcode 2. 两数相加

## 问题描述

[2. 两数相加 - 力扣（LeetCode）](https://leetcode-cn.com/problems/add-two-numbers/)

## 算法

### 解法1: 递归（不符合条件，不推荐）

分成两步，第一步不管进位，直接加就好。第二步依次遍历并进位。

这种解法比较简单。但是不符合条件。因为题目要求每个结点只能存储一位。

#### 解法1: 实现

##### 解法1: c++

```
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* head1, ListNode* head2) {
        ListNode* head = add(head1, head2);
        jingwei(head1);
        return head;
    }

    ListNode* add(ListNode* head1, ListNode* head2) {
        if (head1 == NULL) return head2;
        if (head2 == NULL) return head1;
        head1->val += head2->val;
        head1->next = add(head1->next, head2->next);
        return head1;
    }
    
    void jingwei(ListNode* head) {
        ListNode* node = head;
        while (node != NULL) {
            if (node->val >= 10) {
                // 注意这种情况需要新加一个结点。
                if (node->next == NULL) {   
                    node->next = new ListNode(0);
                }
                node->next->val += node->val / 10;
                node->val %= 10;
            }
            node = node->next;
        }
    }
};
```

### 解法2: 递归

添加一个参数 carry 来实现进位。

由于每个结点只能存储一位。因此需要在外部进行加法，之后将进位后的数字存到结点中。

#### 解法2: 实现

##### 解法2: c++

```
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        return add(l1, l2, 0);
    }

    // carry 是之前加法进上来的
    ListNode* add(ListNode* head1, ListNode* head2, int carry) {
        if (head1 == NULL) {
            if (carry==0) return head2;
            else return add(new ListNode(carry), head2, 0);
        }
        if (head2 == NULL) return add(head2, head1, carry);
        int val = head1->val + head2->val + carry;
        head1->val = val % 10;
        head1->next = add(head1->next, head2->next, val / 10);
        return head1;
    }
};
```

### 解法3：迭代

#### 解法3:实现

##### 解法3: python

```
class Solution:
    def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
        if not l1: return l2
        if not l2: return l1
        carry = 0
        virtualHead = ListNode(-1)
        p = virtualHead
        while l1 or l2 or carry:
            val = carry
            if l1: 
                val += l1.val
                l1 = l1.next
            if l2:
                val += l2.val
                l2 = l2.next
            carry = val // 10
            val %= 10
            p.next = ListNode(val)
            p = p.next
        return virtualHead.next
```