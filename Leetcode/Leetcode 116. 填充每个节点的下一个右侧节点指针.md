[toc]

# Leetcode 116. 填充每个节点的下一个右侧节点指针

## 问题描述

[116. 填充每个节点的下一个右侧节点指针 - 力扣（LeetCode）](https://leetcode-cn.com/problems/populating-next-right-pointers-in-each-node/)

## 算法

### 解法1:  层次遍历

```
class Solution {
public:
    Node* connect(Node* root) {
        if (!root) return root;
        queue<Node*> q;
        q.push(root);

        while (q.size())
        {
            int levelsize = q.size();
            for (int i=0; i<levelsize; i++)
            {
                Node* node = q.front(); q.pop();
                if (i!=levelsize-1) node->next = q.front();
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return root;   
    }
};
```
