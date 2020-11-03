[toc]

# Leetcode 199. 二叉树的右视图

## 問題描述

[199. 二叉树的右视图 - 力扣（LeetCode）](https://leetcode-cn.com/problems/binary-tree-right-side-view/)

## 算法

### 解法1： 層次遍歷

实际上只需要获取层次遍历每层最后一个值即可。

##### 解法1： 实现： c++

```
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ret;
        if (!root) return ret;
        queue<TreeNode*> q;
        q.push(root);
        while (q.size())
        {
            int levelsize = q.size();
            for (int i=0; i<levelsize; i++)
            {
                TreeNode* node = q.front(); q.pop();
                if (i==levelsize-1) ret.push_back(node->val);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return ret;
    }
};
```

### 解法2： 先序遍历变种

如果这题是左视图的话，那么可以使用先序遍历来解决。因为先序遍历是每一层第一个访问的肯定是左视图的第一个节点。

但知道题是右视图，很简单，只需要改变普通先序遍历的节点访问顺序即可。普通的先序遍历一般是先访问左节点后访问右节点，但是我们这里可以先访问右节点后访问左节点。

#### 解法2： 实现

##### 解法2： 实现：c++

```
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ret;
        if (!root) return ret;
        stack<pair<TreeNode*, int>> st;
        st.push({root, 0});
        int depth = 0;
        ret.push_back(root->val);
        while (st.size() || root)
        {
            while (root)
            {
                if (ret.size() == depth) ret.push_back(root->val);
                st.push({root->left, depth+1});
                root = root->right;
                depth++;
            }
            root = st.top().first;
            depth = st.top().second;
            st.pop();
        }
        return ret;
    }
};
```