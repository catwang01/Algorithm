[toc]

# Leetcode 124. 二叉树中的最大路径和

## 问题描述

[124. 二叉树中的最大路径和 - 力扣（LeetCode）](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/)


## 算法

### 解法一：递归

这个题和 [687. 最长同值路径 - 力扣（LeetCode）](https://leetcode-cn.com/problems/longest-univalue-path/) 的思路一样

都分左边的最大路径和右边的最大路径两部分。需要注意的是，由于这里的路径不需要通到叶节点，因此在一个节点处可能的返回值有三种可能：

1. node.val + left
2. node.val + right
3. node.val

![](https://gitee.com/EdwardElric_1683260718/picture_bed/raw/master/img/20200803140550.png)

#### 解法一: 实现

##### 解法1: 实现： python

```
class Solution:
    def maxPathSum(self, root: TreeNode) -> int:
        curMax = -float("inf")
        def dfs(node):
            nonlocal curMax
            if not node: return 0
            left = dfs(node.left)
            right = dfs(node.right)
            ret = max(left + node.val, right + node.val, node.val)
            curMax = max(curMax, ret , left + right + node.val)
            return ret
        dfs(root)
        return curMax
```



#### 解法一：实现：c++

```
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int ret = root->val;
        dfs(root, ret);
        return ret;
    }

    int dfs(TreeNode* root, int& ret)
    {
        if (!root) return 0;
        int left = dfs(root->left, ret);
        int right = dfs(root->right, ret);
        int path = root->val;
        if (left > 0) path += left;
        if (right > 0) path += right;
        ret = max(ret, path);
        return root->val + max(0, max(left, right));
    }
};
```

### 解法2: postorder 非递归

#### 解法2: postorder 实现

##### 解法2: postorder：c++

```
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        unordered_map<TreeNode*, int> path;
        stack<TreeNode*> st;
        int ret = root->val;
        TreeNode* lastprocessed = nullptr;
        while (!st.empty() || root)
        {
            while (root)
            {
                st.push(root);
                root = root->left;
            }
            root = st.top();
            if (root->right == nullptr || root->right == lastprocessed)
            {
                // postorder process
                path[root] = root->val + max(0, max(path[root->left], path[root->right]));
                ret = max(ret, max(path[root], root->val + path[root->left] + path[root->right]));
                lastprocessed = root;
                
                st.pop();
                root = nullptr;
            }
            else
            {
                root = root->right;
            }
        }
        return ret;
    }
};
```