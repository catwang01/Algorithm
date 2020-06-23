
[toc]

# Leetcode 445. 两数相加 II

## 问题描述

[445. 两数相加 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/add-two-numbers-ii/)

## 算法

### 解法1: reverse

将问题reverse之后，问题转化为 [Leetcode 2. 两数相加](https://app.yinxiang.com/shard/s54/nl/22483756/c44fd898-f294-4998-b935-fd6a76a61d0a/)。

而reverse是另一个问题 [Leetcode 206. 反转链表](https://app.yinxiang.com/shard/s54/nl/22483756/cbf4ae45-2524-4998-8b7c-f96d9870791b/)

#### 解法1: 实现

#### 解法1: c++

```
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        l1 = reverse(l1), l2 = reverse(l2);
        ListNode* head = add(l1, l2);
        jingwei(head);
        return reverse(head);
    }

    ListNode* add(ListNode* head1, ListNode* head2) {
        if (head1==NULL) return head2;
        if (head2==NULL) return head1;
        head1->val += head2->val;
        head1->next = add(head1->next, head2->next);
        return head1;
    }

    void jingwei(ListNode* head) {
        ListNode* node = head;
        while (node != NULL) {
            if (node->val >= 10) {
                if (node->next == NULL) {
                    node->next = new ListNode(0);
                }
                node->next->val += node->val / 10;
                node->val %= 10;
            }
            node = node->next;
        }
    }

    ListNode* reverse(ListNode* head) {
        if (head==NULL) return head;
        if (head->next==NULL) return head;
        ListNode* tmp = reverse(head->next);
        head->next->next = head;
        head->next = NULL;
        return tmp;
    }
};
```

### 解法2：使用栈

将遍历结点的同时分别压入栈中。之后栈顶元素相加并弹出即可。由于不能修改原来的结点，因此需要新建结点。

#### 解法2: 实现

##### 解法2: c++ 

###### version1
参考[1]

```
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // 特判
        if (l1==nullptr) return l2;
        if (l2==nullptr) return l1;
        
        // 入栈
        stack<ListNode*> s1, s2;
        while (l1) {
            s1.push(l1);
            l1 = l1 -> next;
        }
        while (l2) {
            s2.push(l2);
            l2 = l2->next;
        }
        
        
        int carry = 0, val;
        ListNode* tmpNode, *head = nullptr;
        // 不断从 s1 和 s2 取出对应位相加。直到某个栈空
        while (!s1.empty() && !s2.empty()) {
            val = s1.top()->val + s2.top()->val + carry;
            carry = val / 10;
            val %= 10;
            // 注意使用尾插法，如果使用头插法，还需要 reverse
            tmpNode = new ListNode(val);
            tmpNode->next = head;
            head = tmpNode;
            s1.pop(); s2.pop();
        }
        
        // 处理另一个栈中的元素
        if (!s1.empty()) {
            while (!s1.empty()) {
                val = s1.top() ->val + carry;
                carry = val / 10;
                val %= 10;
                tmpNode = new ListNode(val);
                tmpNode->next = head;
                head = tmpNode;
                s1.pop();
            }
        } else {
            while (!s2.empty()) {
                val = s2.top() -> val + carry; 
                carry = val / 10;
                val %= 10;
                tmpNode = new ListNode(val);
                tmpNode->next = head;
                head = tmpNode;
                s2.pop();
            }
        }
        // 处理进位
        if (carry) {
            tmpNode = new ListNode(carry);
            tmpNode ->next = head;
            head = tmpNode;
        }
        return head;
    }
};
```

###### version2

可以看到，上面的代码中有许多都是重复的，可以考虑合并。合并后的代码如下

```
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // 特判
        if (l1==nullptr) return l2;
        if (l2==nullptr) return l1;
        
        // 入栈
        stack<ListNode*> s1, s2;
        while (l1) {
            s1.push(l1);
            l1 = l1 -> next;
        }
        while (l2) {
            s2.push(l2);
            l2 = l2->next;
        }
        
        
        int carry = 0, val, val1, val2;
        ListNode* tmpNode, *head = nullptr;
        // 不断从 s1 和 s2 取出对应位相加。直到某个栈空
        while (!s1.empty() || !s2.empty() || carry != 0) {
            val1 = s1.empty() ? 0 : s1.top() -> val;
            val2 = s2.empty() ? 0 : s2.top() -> val;
            val = val1 + val2 + carry;
            carry = val / 10;
            val %= 10;
            tmpNode = new ListNode(val);
            tmpNode->next = head;
            head = tmpNode;
            if (!s1.empty()) s1.pop(); 
            if (!s2.empty()) s2.pop();
        }
        return head;
    }
};

```

# References
1. [栈 - 两数相加 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/add-two-numbers-ii/solution/zhan-by-powcai-7/)