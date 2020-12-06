[toc]

# Leetcode 103. 二叉树的锯齿形层次遍历

## 问题描述

[103. 二叉树的锯齿形层次遍历 - 力扣（LeetCode）](https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal/)

给定一个二叉树，返回其节点值的锯齿形层次遍历。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。

例如：
给定二叉树  `[3,9,20,null,null,15,7]`,

```
    3
   / \
  9  20
    /  \
   15   7
```

返回锯齿形层次遍历如下：

```
[
  [3],
  [20,9],
  [15,7]
]
```

## 算法

### 解法1: reverse

#### 解法1:

##### 解法1: python

```
from collections import deque
class Solution:
    def zigzagLevelOrder(self, root: TreeNode) -> List[List[int]]:
        if not root: return []
        ret = []
        q = deque([root])
        level = 0
        while q:
            nodeNum = len(q)
            level += 1
            subret = []
            for _ in range(nodeNum):
                node = q.popleft()
                subret.append(node.val)
                if node.left: q.append(node.left)
                if node.right: q.append(node.right)
            if level & 1:
                ret.append(subret)
            else:
                ret.append(subret[::-1])

        return ret   
```

### 解法2: levelorder

#### 解法2:实现

##### 解法2: python

```
class Solution:
    def zigzagLevelOrder(self, root: TreeNode) -> List[List[int]]:
        ret = []
        if not root: return ret
        st = []
        q = deque([root])
        level = -1
        while q:
            level += 1
            ret.append(deque())
            levelsize = len(q)
            for _ in range(levelsize):
                node = q.popleft()
                if level & 1:
                    ret[level].appendleft(node.val)
                else:
                    ret[level].append(node.val)
                if node.left: 
                    q.append(node.left)
                if node.right: 
                    q.append(node.right)
        return [list(l) for l in ret]
```

### 解法3: preorder

对于奇数层，从头部插入，对于偶数层从尾部插入。为了提升速度，ret 中先存 deque，输出时转换为 list

#### 解法3: 实现：非递归

##### 解法3： 实现：python

```
class Solution:
    def zigzagLevelOrder(self, root: TreeNode) -> List[List[int]]:
        ret = []
        level = 0
        st = []
        while st or root:
            while root:
                if len(ret) == level:
                    ret.append(deque([]))
                if level & 1:
                    ret[level].appendleft(root.val)
                else:
                    ret[level].append(root.val)
                st.append((root.right, level + 1))
                root = root.left
                level += 1
            root, level = st.pop()
        return [list(l) for l in ret]
```