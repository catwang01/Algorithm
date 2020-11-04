[toc]

# Leetcode 104. 二叉树的最大深度

## 问题描述

[104. 二叉树的最大深度 - 力扣（LeetCode）](https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/)

## 算法


### 解法一：dfs postorder

postorder 的思想比较自然：

如果知道一个结点左子树的深度 left_depth 和右子树的深度 right_depth，则这个结点的深度为 1 + max(left_depth, right_depth)；

这个实际上是计算出左右子树的数据之后计算结点的数据，实际上是 dfs 的 postorder
#### 解法1: python preorder 颜色标记法

```
class Solution:
    def maxDepth(self, root: TreeNode) -> int:
        if not root: return 0
        WHITE, BLACK = 0, 1
        ret = 0
        stack = [(root, WHITE, 1)]
        while stack:
            node, color, depth = stack.pop()
            if color == WHITE:
                if node.right:
                    stack.append((node.right, WHITE, depth+1))
                if node.left:
                    stack.append((node.left, WHITE, depth+1))
                stack.append((node, BLACK, depth))
            else:
                if not node.left and not node.right:
                    ret = max(ret, depth)
        return ret
```
        
#### 解法一python 递归写法

```
class Solution:
    def maxDepth(self, root: TreeNode) -> int:
        if not root: return 0
        return 1 + max(self.maxDepth(root.left), self.maxDepth(root.right))
```

框架2

```
class Solution:
    def maxDepth(self, root: TreeNode) -> int:
        maxLevel = 0

        def _maxDepth(node, level):
            nonlocal maxLevel
            # if not root: do nothing
            if node:
                level += 1
                maxLevel = max(maxLevel, level)
                _maxDepth(node.left, level)
                _maxDepth(node.right, level)
    
        _maxDepth(root, 0)
        return maxLevel
```

#### 解法一c++ 递归写法

```
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == NULL) {
           return 0;
        }
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
};
```

#### 解法一c++ 非递归写法

```
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root==NULL) return 0;
        stack<TreeNode*> s;
        int maxDepth = INT_MIN, depth = 1;
        while (root != NULL || !s.empty()) {
            while (root!=NULL) {
                s.push(root);
                if (root -> left != NULL) root = root -> left;
                else root = root -> right;
                depth++;
            }
            root = s.top(); s.pop();
            depth--;
            cout << depth;
            // postorder processing
            maxDepth = max(maxDepth, depth);
            if (!s.empty() && s.top() -> left == root) {
                root = s.top() -> right;
            } else {
                root = NULL;
            }
        }
        return maxDepth;
    }
};
```

#### 解法一c++ 非递归 利用hashmap

```
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root==NULL) return 0;
        stack<TreeNode*> s;
        unordered_map<TreeNode*, int> height;
        int maxDepth = INT_MIN;
        while (root != NULL || !s.empty()) {
            while (root!=NULL) {
                s.push(root);
                if (root -> left != NULL) root = root -> left;
                else root = root -> right;
            }
            root = s.top(); s.pop();
            // postorder processing
            if (root!=NULL) {
                if (root->left== NULL && root->right==NULL) height[root] = 1;
                if (root->left!= NULL && root->right==NULL) height[root] = height[root->left] + 1;
                if (root->left==NULL && root->right!=NULL) height[root] = height[root->right] + 1;
                if (root->left!=NULL && root->right!=NULL) height[root] = 1 + max(height[root->left], height[root->right]);
            }
                maxDepth = max(maxDepth, height[root]);
            if (!s.empty() && s.top() -> left == root) {
                root = s.top() -> right;
            } else {
                root = NULL;
            }
        }
        return maxDepth;
    }
};
```

### 解法二：dfs preorder 非递归


#### 解法二：实现

##### 解法2：实现：python

```
class Solution:
    def maxDepth(self, root: TreeNode) -> int:
        if not root: return 0
        maxDepth = depth = 1
        stack = []
        
        while stack or root:
            while root:
                maxDepth = max(depth, maxDepth)
                stack.append((root.right, depth+1))
                root = root.left # 结点下行 
                depth += 1      # 深度加1
            root, depth = stack.pop()

        return maxDepth
```

##### 解法2：实现：c++

```
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        stack<pair<TreeNode*, int>> st;
        int depth = 1;
        st.push({root, depth});
        int ret = 1;
        while (root || st.size())
        {
            while (root)
            {
                // preorder process
                ret = max(ret, depth);    
                depth++;
                st.push({root->right, depth});
                root = root->left; 
            }
            root = st.top().first;
            depth = st.top().second;
            st.pop();
        }
        return ret;
    }
};
```


### 解法3: bfs——层次遍历

#### 解法3: 实现

##### 解法3: c++

```
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        
        deque<TreeNode*> queue;
        queue.push_back(root);
        int depth = 0;
        while (!queue.empty()) {
            depth++;
            int nNodes = queue.size();
            while (nNodes--) {
                TreeNode* node = queue.front(); queue.pop_front();
                if (node->left) queue.push_back(node->left);
                if (node->right) queue.push_back(node->right);
            }
        }
        return depth;
    }
};
```