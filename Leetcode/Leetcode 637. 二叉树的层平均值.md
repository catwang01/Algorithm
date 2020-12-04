[toc]

# Leetcode 637. 二叉树的层平均值

## 问题描述

[637. 二叉树的层平均值 - 力扣（LeetCode）](https://leetcode-cn.com/problems/average-of-levels-in-binary-tree/)

## 算法

### 解法1: 先序遍历

#### 解法1: 实现：

##### 解法1: 实现：python

```
class Solution:
    def averageOfLevels(self, root: TreeNode) -> List[float]:
        s = []
        count = []
        st = []
        level = 0
        while st or root:
            while root:
                if len(s) == level:
                    s.append(0)
                    count.append(0)
                s[level] += root.val
                count[level] += 1
                st.append((root.right, level + 1))
                root = root.left
                level += 1
            root, lev = st.pop()
        
        return [x / y for x, y in zip(s, count)]
```                
        
