[toc]

# Leetcode 面试题 02.01. 移除重复节点 

## 问题描述

[面试题 02.01. 移除重复节点 - 力扣（LeetCode）](https://leetcode-cn.com/problems/remove-duplicate-node-lcci/)


## 算法

### 解法1: hast表

#### 解法1： c++

```cpp
class Solution {
public:
    ListNode* removeDuplicateNodes(ListNode* head) {
        if (!head || !head->next) return head;
        
        ListNode virtualHead(-1);
        virtualHead.next = head;
        
        ListNode *cur = &virtualHead, *prev;

        unordered_set<int> seen;
        while (cur) {
            seen.insert(cur->val);
            prev = cur;
            while (cur && seen.find(cur->val)!=seen.end()) {
                cur = cur->next;
            }
            prev->next = cur;
        }
        return virtualHead.next;
    }
};
```