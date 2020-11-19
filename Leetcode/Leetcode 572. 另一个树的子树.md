[toc]


# Leetcode 572. 另一个树的子树

## 问题描述

[572. 另一个树的子树 - 力扣（LeetCode）](https://leetcode-cn.com/problems/subtree-of-another-tree/)

## 算法

### 解法1：递归


这个问题需要注意的是，下面的递归是错误的递归

```
if s.val == t.val and self.isSubtree(s.left, t.left) and self.isSubtree(s.right, t.right):
    return True
```

时间复杂度：$O(|s| * |t|)$，其中 |s| 表示 s 中节点的个数，|t| 表示 t 中节点的个数。

问题可以转化为 [100. 相同的树 - 力扣（LeetCode）](https://leetcode-cn.com/problems/same-tree/)。
注意 isSubtree 和 isSame 的特判有点像，但是不同。如果 s 不为 None 而 t 为 None，isSubtree 返回 True，但是 isSame 返回 False。

##### 解法1: 实现：python


```
class Solution:
def isSubtree(self, s: TreeNode, t: TreeNode) -> bool:
    if not s:
        return not t
    if not t: 
        return True

    return self.isSame(s, t) or self.isSubtree(s.left, t) or self.isSubtree(s.right, t)

def isSame(self, root1, root2):
    if not root1:
        return not root2
    if not root2:
        return False
    return root1.val == root2.val and \
                self.isSame(root1.left, root2.left) and \
                self.isSame(root1.right, root2.right)
```