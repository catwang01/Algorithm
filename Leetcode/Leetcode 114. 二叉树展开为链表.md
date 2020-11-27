[toc]

# Leetcode 114. 二叉树展开为链表 

## 问题描述

[114. 二叉树展开为链表 - 力扣（LeetCode）](https://leetcode-cn.com/problems/flatten-binary-tree-to-linked-list/)

## 算法

### 解法1: 后序遍历

#### 解法1: 实现1: 递归并返回链表头尾节点

##### 解法1: 实现1: python

```
class Solution {
public:
    void flatten(TreeNode* root) {
        helper(root);
    }

    pair<TreeNode*, TreeNode*> helper(TreeNode* root)
    {
        if (!root) return {nullptr, nullptr};
        TreeNode *head = root, *tail = root;
        auto leftret = helper(root->left);
        root->left = nullptr;
        auto rightret = helper(root->right);
        root->right = nullptr;
        if (leftret.first)
        {
            tail->right = leftret.first;
            tail = leftret.second;
        }
        if (rightret.first)
        {
            tail->right = rightret.first;
            tail = rightret.second;
        }
        return {head, tail};
    }
};
```

#### 解法1: 实现2: 递归，只返回尾节点

注意到，上面的 helper 函数中的 head 总是 root，可以简化。

##### 解法1: 实现2: C++

```
class Solution {
public:
    void flatten(TreeNode* root) {
        helper(root);
    }

    TreeNode* helper(TreeNode* root)
    {
        if (!root) return nullptr;
        TreeNode *tail = root;
        TreeNode* left = root->left, *right=root->right;
        root->left = root->right = nullptr;
        auto leftret = helper(left);
        auto rightret = helper(right);
        if (leftret)
        {
            tail->right = left;
            tail = leftret;
        }
        if (rightret)
        {
            tail->right = right;
            tail = rightret;
        }
        return tail;
    }
};
```

### 解法2: 前序遍历

注意，前序遍历的思想和后序遍历不同。后序遍历是将 root 和 root->left 和 root->right 的结果组合起来。

前序遍历是一步一步往结果中添加节点。每次对 root 进行的操作就是将 root 添加到结果中。

##### 解法2: 实现1: 递归

```
class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode virtualHead, *tail = &virtualHead;
        preorder(root, tail);
    }

    void preorder(TreeNode* root, TreeNode*& tail){
        if (!root) return;
        tail->right = root;
        TreeNode *left = root->left, *right = root->right; // 这里的断链很重要
                                                            // 因为在递归的过程中会修改 root->left 和 root->right
        root->left = root->right = nullptr;
        tail = root;
        preorder(left, tail);
        preorder(right, tail);
    }
};
```