[toc]

# Leetcode 817. 链表组件

## 问题描述

[817. 链表组件 - 力扣（LeetCode）](https://leetcode-cn.com/problems/linked-list-components/)

## 算法

### 解法1: 滑动窗口

实际上是滑动窗口的思想。

##### 解法1: 实现：c++

```
class Solution {
public:
    int numComponents(ListNode* head, vector<int>& G) {
        unordered_set<int> hashset(G.begin(), G.end());
        if (!head) return 0;
        ListNode* cur = head, *nextNode = NULL;
        int ret = 0;
        while (cur)
        {
            if (hashset.count(cur->val)) // 判断 cur 是否在 G 中
            {
                nextNode = cur->next;
                while (nextNode && hashset.count(nextNode->val))
                {
                    nextNode = nextNode->next;
                }
                cur = nextNode;
                ret++;
            }
            else
            {
                cur = cur->next;
            }
        }
        return ret;
    }
};
```