
[toc]

# Leetcode 102. 二叉树的层次遍历

## 问题描述

[102. 二叉树的层次遍历 - 力扣（LeetCode）](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/)

给定一个二叉树，返回其按层次遍历的节点值。 （即逐层地，从左到右访问所有节点）。

例如:
给定二叉树:  `[3,9,20,null,null,15,7]`,

```
   3
  / \
 9  20
 /  \
15   7
```

返回其层次遍历结果：

```
[
  [3],
  [9,20],
  [15,7]
]
```

## 算法

### 解法一：bfs

这里需要用到bfs遍历的一个性质：当第n层的最后一个结点出队列时，队列中剩下的结点恰好为第 n+1 层的所有结点

#### 解法1: 实现

##### 解法1: c++

```
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ret;
        if (!root) return ret;
        queue<TreeNode*> q({root});
        while (!q.empty())
        {
            vector<int> levelret;
            int levelsize = q.size();
            while (levelsize--)
            {
                TreeNode* node = q.front(); q.pop();
                levelret.push_back(node->val);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            ret.push_back(levelret);
        }
        return ret;
    }
};
```


##### 解法一:python

```
from collections import deque

class Solution:
    def levelOrder(self, root: TreeNode) -> List[List[int]]:
        if not root: # root = nil
            return []

        q, level = deque(), -1
        q.append(root)
        result = [] 
        while q: # while q is not empty
            levelsize = len(q) # 层中有多少个结点
            result.append([])
            level += 1
            for _ in range(levelsize):
                node = q.popleft()
                if node:
                    result[level].append(node.val)
                    if node.left:
                        q.append(node.left)
                    if node.right:
                        q.append(node.right)
        return result
```


### 解法二：dfs

#### 解法2: 实现

##### 解法2: python

这里用的是preorder

```
from collections import deque

class Solution:
    def levelOrder(self, root: TreeNode) -> List[List[int]]:

        result, stack, level = [], [], 0
        def proc(data):
            nonlocal level
            if len(result) == level:
                result.append([])
            result[level].append(data)

        while stack or root:
            while root:
                proc(root.val)
                stack.append((root.right, level+1))
                root = root.left
                level += 1
            root, level = stack.pop()
        return result
```

##### 解法2: c++

```
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ret;
        if (!root) return ret;
        dfs(1, root, ret);
        return ret;
    }

    void dfs(int i, TreeNode* node, vector<vector<int>>& ret)
    {
        if (ret.size() < i) ret.push_back({});
        ret[i-1].push_back(node->val);
        if (node->left) dfs(i+1, node->left, ret);
        if (node->right) dfs(i+1, node->right, ret);
    }
};
```