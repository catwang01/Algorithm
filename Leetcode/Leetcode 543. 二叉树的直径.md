[toc]

# Leetcode 543. 二叉树的直径

## 问题描述

[543. 二叉树的直径 - 力扣（LeetCode）](https://leetcode-cn.com/problems/diameter-of-binary-tree/)

给定一棵二叉树，你需要计算它的直径长度。一棵二叉树的直径长度是任意两个结点路径长度中的最大值。这条路径可能穿过根结点。

**示例 :**
给定二叉树

          1
         / \
        2   3
       / \
      4   5

返回 **3**, 它的长度是路径 \[4,2,1,3\] 或者 \[5,2,1,3\]。

**注意：**两结点之间的路径长度是以它们之间边的数目表示。

注意，下面两种情况直接dfs返回时结果是相同的，都返回 0 ，但是作为子结果返回时，结果不相同。

```
# 情况1
None 

# 情况2
    1
   /
 None
```

因此需要特殊判断

## 算法

### 解法一：dfs——postorder 递归

##### 解法1: 实现：python

```
class Solution:
    def diameterOfBinaryTree(self, root: TreeNode) -> int:
        if not root: return 0
        ret = 0
        def dfs(root):
            nonlocal ret
            if not root:
                return -1 # root == None 返回 -1
                            # 因为想要达到 root 为叶节点时返回 0 的效果

            left = dfs(root.left) + 1
            right = dfs(root.right) + 1
            ret = max(ret, left + right)
            return max(left, right)

        dfs(root)
        return ret
```

### 解法一：dfs——postorder 非递归

#### 解法一python

```
class Solution:
    def diameterOfBinaryTree(self, root: TreeNode) -> int:
        if not root: return 0

        stack = []
        left_map, right_map = {}, {}
        maxPath = -1
        while stack or root:
            while root:
                stack.append(root)
                root = root.left if root.left else root.right
            root = stack.pop() 
            if root:
                left_map[root] = 1 + max(left_map[root.left], right_map[root.left]) if root.left else 0 
                right_map[root] = 1 + max(left_map[root.right], right_map[root.right]) if root.right else 0
                maxPath = max(maxPath, left_map[root]+right_map[root])
            if stack and stack[-1].left == root:
                root = stack[-1].right
            else:
                root = None
        return maxPath
```

### 解法3: dfs postorder 非递归

#### 解法3: 实现

##### 解法3: 实现： python

```
class Solution:
    def diameterOfBinaryTree(self, root: TreeNode) -> int:
        
        st = []
        result_stack = [] # 用来保存左右节点的结果
        diameter = 0
        lastprocessed = 0

        def process(node):
            nonlocal diameter
            if not node: return 0
            right = 1 + result_stack.pop() if root.right else 0
            left = 1 + result_stack.pop() if root.left else 0

            diameter = max(diameter, right + left)
            result_stack.append(max(left, right))
            

        while root or st:
            while root:
                st.append(root)
                root = root.left
            root = st[-1]
            if root.right is None or root.right == lastprocessed:
                process(root)
                st.pop()
                lastprocessed = root
                root = None
            else:
                root = root.right
        return diameter
```