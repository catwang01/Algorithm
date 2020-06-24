[toc]

# Leetcode 234. 回文链表

## 问题描述

[234. 回文链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/palindrome-linked-list/)

[面试题 02.06. 回文链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/palindrome-linked-list-lcci/)

## 算法

### 解法1: 寻找中点 + 反转

#### 解法1: 实现1: 直接 reverse 链表

##### 解法1.1: c++


```
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;
        ListNode* mid = midNode(head);
        ListNode *newHead = mid->next;
        mid->next = NULL;
        newHead = reverse(newHead);
        while (newHead) {
            if (newHead->val == head->val) {
                newHead = newHead->next;
                head= head->next;
            } else {
                return false;
            }
        }
        return true;     
    }

    ListNode* midNode(ListNode* head) {
        ListNode *slow = head, *fast = head->next;
        while (fast && fast->next) {
            slow = slow -> next;
            fast = fast->next->next;
        }
        return slow;
    }

    ListNode* reverse(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode* newHead = reverse(head->next);
        head->next->next = head;
        head->next = NULL; // 断链
        return newHead;
    }
};
```

#### 解法1: 实现2: 利用栈reverse

##### 解法1.2: c++

```
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;
        
        // 找到中点
        ListNode *slow=head, *fast = head;
        while (!(fast==nullptr || fast->next==nullptr)) {
            fast = fast->next->next;
            slow = slow->next;
        }
        
        // 将中点之后的节点压入栈中
        stack<ListNode*> s;
        while (slow) {
            s.push(slow);
            slow = slow->next;
        }
        
        ListNode* p = head;
        // 从头开始遍历，每遍历一个结点就从栈中弹出一个元素，比较是否相同
        while (!s.empty()) {
            if (s.top()->val != p->val) return false;
            s.pop();
            p = p->next;
        }
        return true;
    }
};
```
### 解法2: 递归

这个解法其实不好。因为每次找到最后一个元素都需要 $O(n)$  的时间。

时间复杂度：$O(n^2)$ 

#### 解法2: 实现

##### 解法2: c++

```
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        return helper(head, NULL);
    }

    bool helper(ListNode* head, ListNode* end) {
        if (head==end || head->next==end) return true;
        ListNode* tail = head;
        while (tail->next != end) {
            tail = tail->next;
        }
        if (tail->val != head->val) return false;
        return helper(head->next, tail);
    }
};
```

### 解法3: 转化为list

#### 解法3: 实现

##### 解法3: c++

```
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        vector<int> list;
        while (head) {
            list.push_back(head->val);
            head = head->next;
        }
        int n = list.size();
        for (int i=0; i < n; i++) {
            if (list[i] != list[n-i-1]) {
                return false;
            }
        }
        return true;
    }
};
```