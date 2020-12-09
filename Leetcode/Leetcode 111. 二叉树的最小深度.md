[toc]

# Leetcode 111. 二叉树的最小深度

## 问题描述 

[111. 二叉树的最小深度 题解 - 力扣（LeetCode）](https://leetcode-cn.com/problems/minimum-depth-of-binary-tree/)

给定一个二叉树，找出其最小深度。

最小深度是从根节点到最近叶子节点的最短路径上的节点数量。

**说明:** 叶子节点是指没有子节点的节点。

**示例:**

给定二叉树 `[3,9,20,null,null,15,7]`,

```
    3
   / \
  9  20
    /  \
   15   7
```

返回它的最小深度  2.

## 算法

一个最简单的想法是最小深度是所有叶子结点的深度的最小值，因此只需要遍历一次，在**遇到叶子结点**的时候去记录其深度，对所有的深度求最小值即可。

### 解法1：bfs

当遇到叶子结点的时候记录下其深度，求所有叶子结点的深度

用 dfs 和 bfs 均可，但是 dfs 需要遍历所有的结点才能知道最小值，而 bfs 需要第一个叶子结点就可以直接返回，因为根据bfs的性质，从根结点到这个叶子结点的路径长度是从根结点到所有叶子结点的路径长度中最短的；

时间复杂度： $O(n)$
空间复杂度： $O(n)$

#### 解法1: 实现
##### 解法1: python

*   时间复杂度：最坏情况下，这是一棵平衡树，我们需要按照树的层次一层一层的访问完所有节点，除去最后一层的节点。这样访问了 $N/2$ 个节点，因此复杂度是 $O(N)$ 。
*   空间复杂度：和时间复杂度相同，也是 $O(N)$ 。

```
from collections import deque
class Solution:
    def minDepth(self, root: TreeNode) -> int:
        # root == nil
        if not root: return 0
        q = deque([root])
        depth = 0

        while q:
            nodeNum = len(q)
            depth += 1
            for _ in range(nodeNum):
                node = q.popleft()
                if node:
                    if not node.left and not node.right:
                        return depth
                    q.append(node.left)
                    q.append(node.right)
```

##### 解法1: c++

```
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root==NULL) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int depth = 0, size;
        TreeNode* node;
        
        while (!q.empty()) {
            depth++;
            size = q.size();
            while( size --) {
                node = q.front(); q.pop();
                if (node->left==NULL && node->right==NULL) 
                    return depth;
                    
                if (node->left != NULL) q.push(node->left);
                if (node -> right != NULL) q.push(node->right);
            }
        }
        return depth;
    }
};
```
### 解法2: dfs

#### 解法2： 实现

##### 解法2: python preorder 颜色标记

```
class Solution:
    def minDepth(self, root: TreeNode) -> int:
        if not root: return 0
        BLACK, WHITE = 0, 1
        stack = [(root, WHITE, 1)]
        ret = float("inf")
        while stack:
            node, color, depth = stack.pop()
            if color == WHITE:
                if node.right:
                    stack.append((node.right, WHITE, depth+1))
                if node.left:
                    stack.append((node.left, WHITE, depth+1))
                stack.append((node, BLACK, depth))
            else:
                # 判断是否是叶节点
                if not node.left and not node.right:
                    ret = min(ret, depth)
        return ret
```

##### python inorder 非递归

```
```

### 解法3： postorder

#### 解法3： 非递归

##### 解法3: 实现： python

```
class Solution:
    def minDepth(self, root: TreeNode) -> int:
        if not root: return 0
        
        stack, depth= [], 1 # depth 表示当前结点的深度
        minDepth = float('inf')

        while stack or root:
            while root:
                stack.append(root)
                root = root.left if root.left else root.right
                depth += 1
            root = stack.pop()
            depth -= 1
            # proc(root.val) 记录下叶子结点的深度
            if root and not root.left and not root.right: # root != nil && root.left == nil && root.right ==nil
                minDepth = min(minDepth, depth)
            if stack and stack[-1].left == root:
                root = stack[-1].right
            else:
                root = None
        return minDepth
```

#### 解法3： 实现：c++

```
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        stack<pair<TreeNode*, int>> st;
        TreeNode* lastprocessed = nullptr;
        int depth = 1;
        int ret = INT_MAX;
        while (root || st.size())
        {
            while (root)
            {
                st.push({root, depth});
                root = root->left;  depth++;
            }
            root = st.top().first;
            depth = st.top().second;
            if (!root->right || root->right == lastprocessed)
            {
                // postorder processing
                if (!root->left && !root->right)  {
                    ret = min(ret, depth);
                }
                st.pop();
                lastprocessed = root;
                root = nullptr;
            }
            else
            {
                root = root->right;
                depth++;
            }
        }
        return ret;
    }
};
```

#### 解法3： 实现： 递归

##### 解法3： 实现：python

递归的逻辑如下： 

![9fb23faeb67d4de44f6f01c48489aa99.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p13957)

这个先计算出左右子结点点的值，根据左右子结点的值计算出当前结点的值，实际上是postorder

```
from collections import deque

class Solution:
    def minDepth(self, root: TreeNode) -> int:
        # root == nil
        if not root: return 0
        if not root.left and not root.right: # left == nil && right == nil
            return 1
        if root.left and root.right:    # left != nil && right != nil
            return 1 + min(self.minDepth(root.left), self.minDepth(root.right))
        if not root.left and root.right: # left != nil && right == nil
            return 1 + self.minDepth(root.right)
        if not root.right and root.left: # left!=nil && right==nil
            return 1 + self.minDepth(root.left)
```

将上面的逻辑改造改造，抽象出一个safemin函数，当两个数同为 0 时才会返回0，当两个数只有一个为0时返回非0，当两个数均不为0时返回最小值；

```
from collections import deque

class Solution:

    def minDepth(self, root: TreeNode) -> int:
        def safemin(x, y):
            if x==0: return y
            if y==0: return x
            return min(x, y)

        # root == nil
        if not root: return 0
        return 1 + safemin(self.minDepth(root.left), self.minDepth(root.right))
```