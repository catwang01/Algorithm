[toc]

# Leetcode 222. 完全二叉树的节点个数

## 问题描述

[222. 完全二叉树的节点个数 - 力扣（LeetCode）](https://leetcode-cn.com/problems/count-complete-tree-nodes/)

## 算法

注意，完全二叉树最后一层是从左边开始填充的。

### 解法1

参考 [ 1 ]

如何判断第 k 个节点是否存在呢？如果第 k 个节点位于第 h 层，则 k 的二进制表示包含 h+1 位，其中最高位是 1，其余各位从高到低表示从根节点到第 k 个节点的路径，0 表示移动到左子节点，1 表示移动到右子节点。通过位运算得到第 k 个节点对应的路径，判断该路径对应的节点是否存在，即可判断第 k 个节点是否存在。

##### 解法1：实现：python

```
class Solution:
    def countNodes(self, root: TreeNode) -> int:
        if not root: return 0
        k = 0
        node = root
        while node:
            node = node.left
            k += 1
        # 一共有 k 层 （k从 1 开始）
        # 最后一层有 k 位数字。第一位数字不考虑

        def isexist(x):
            nonlocal root, k
            node = root
            i = k - 1
            while i > 0:
                if x & (1 << (i - 1)): # 第 i 位为 1
                    node = node.right
                else: # 第 i 位为 0
                    node = node.left
                i -= 1
            return node is not None

        low, high = 1 << (k-1),  (1 << k)
        
        while high - low > 2:
            mid = (low + high) // 2
            if isexist(mid):
                low = mid
            else:
                high = mid
        if isexist(high-1): 
            return high-1
        return low
```


# References

1. [完全二叉树的节点个数 - 完全二叉树的节点个数 - 力扣（LeetCode）](https://leetcode-cn.com/problems/count-complete-tree-nodes/solution/wan-quan-er-cha-shu-de-jie-dian-ge-shu-by-leetco-2/)