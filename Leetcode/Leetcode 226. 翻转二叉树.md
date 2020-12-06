[toc] 

# Leetcode 226. 翻转二叉树

## 问题描述

[226. 翻转二叉树 - 力扣（LeetCode）](https://leetcode-cn.com/problems/invert-binary-tree/)

## 算法

只需要遍历每个结点，交换其左右结点即可。使用 preorder、inorder、postorder、levelorder均可

### 解法1: preorder dfs

#### 解法1: 实现：递归

##### 解法1: 实现:python

```
class Solution:
    def invertTree(self, root: TreeNode) -> TreeNode:
        
        def process(node):
            if not node: return 
            node.left, node.right = node.right, node.left

        def preorder(node, process):
            if not node: return
            process(node)
            preorder(node.right, process)
            preorder(node.left, process)

        preorder(root, process)
        return root
```

#### 解法1: 实现2: 非递归
##### 解法1: 实现2: python

```
class Solution:
    def invertTree(self, root: TreeNode) -> TreeNode:
        node = root
        stack = []
        while stack or node:
            while node:
                # preorder processing
                node.left, node.right = node.right, node.left  
                stack.append(node.right)
                node = node.left
            node = stack.pop()
        return root
```

### 解法2: postorder

##### 解法二python inorder 非递归

```
class Solution:
    def invertTree(self, root: TreeNode) -> TreeNode:
        if not root: return root
        node = root
        stack = []
        while stack or node:
            while node:
                stack.append(node)
                node = node.left
            node = stack.pop()
            # inorder processing
            node.left, node.right = node.right, node.left
            node = node.left # 这里需要将框架的 node = node.right
        return root
```


#### 解法2： 实现1: 递归

##### 解法2： 实现1: python

利用python的语言特性，可以省略保存 root.left 的步骤，直接交换

```
class Solution:
    def invertTree(self, root: TreeNode) -> TreeNode:
        if not root:
            return None
        root.left, root.right = self.invertTree(root.right), self.invertTree(root.left)
        return root
```

##### 解法2：实现1: java

```
class Solution {
    public TreeNode invertTree(TreeNode root) {
        aux(root);
        return root;
    }
    public void aux(TreeNode node) {
        if (node==null) return;
        TreeNode tmp = node.left;
        node.left = node.right;
        node.right = tmp;
        aux(node.left);
        aux(node.right);
    }
}
```

#### 解法2: 实现2: 非递归

##### 解法2: 实现2: python

```
class Solution:
    def invertTree(self, root: TreeNode) -> TreeNode:
        if not root: return root
        node = root
        stack = []
        while stack or node:
            while node:
                stack.append(node)
                node = node.left if node.left else node.right
            node = stack.pop()
            node.left, node.right = node.right, node.left
            if stack and stack[-1].left == node:
                node = stack[-1].right
            else:
                node = None
        return root
```

### 解法3：inorder dfs


```
```

### 解法4: level order

##### 解法一python bfs 非递归

bfs 只需要在每层都交换相邻两个结点即可。

![52afed5fe69ade7f5628dbd1a2b7e0ae.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p11228)

```
from collections import deque
class Solution:
    def invertTree(self, root: TreeNode) -> TreeNode:
        if not root: return None
        q = deque([root])
        while q:
            node = q.pop()
            if node:
                # 交换
                node.left, node.right = node.right, node.left
                q.append(node.left)
                q.append(node.right)
        return root
```