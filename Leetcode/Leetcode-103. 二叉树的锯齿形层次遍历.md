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

### 解法2: 使用deque

#### 解法2:实现

##### 解法2: python

```
class Solution:
    def zigzagLevelOrder(self, root: TreeNode) -> List[List[int]]:
        ret = []
        if not root: return ret
        dq = deque([root])
        is_pop_left = True
        while dq:
            levelsize = len(dq)
            levelret = []
            for i in range(levelsize):
                if is_pop_left:
                    node = dq.popleft()
                    levelret.append(node.val)
                    if node.left:
                        dq.append(node.left)
                    if node.right:
                        dq.append(node.right)
                else:
                    node = dq.pop()
                    levelret.append(node.val)
                    if node.right:
                        dq.appendleft(node.right)
                    if node.left:
                        dq.appendleft(node.left)
            is_pop_left = not is_pop_left
            ret.append(levelret)
        return ret
```