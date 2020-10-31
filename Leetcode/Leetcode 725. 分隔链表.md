[toc]

# Leetcode 725. 分隔链表

## 问题描述

[725. 分隔链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/split-linked-list-in-parts/)

## 算法

### 解法1: 直接计算

1. 先计算出每个链表的长度，之后依次分配。
2. 注意有在链表尾部断链

#### 解法1: 实现

##### 解法1: c++

```cpp
class Solution {
public:
    // 计算结果的每个列表的节点数
    vector<int> splitLen(ListNode* root, int k) {
        int len = 0;
        while (root) {
            root = root->next;
            len++;
        }
        int min = len / k, left = len % k;
        vector<int> ret(k, min);
        for (int i=0; i<left; i++) {
            ret[i] += 1;
        }
        return ret;
    }
    
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        vector<int> lens = splitLen(root, k);
        
        vector<ListNode*> ret(k, nullptr);
        ListNode* tmp;
        
        for (int i=0; i<k; i++) {
            ret[i] = root;
            if (lens[i]) {
                // 注意这个是 lens[i] - 1
                for (int j=0; j<lens[i]-1; j++) {
                    root = root->next;
                }
                // 尾结点处断链
                tmp = root->next;
                root->next = nullptr;
                root = tmp;
            }
        }
        return ret;
    }
};
```