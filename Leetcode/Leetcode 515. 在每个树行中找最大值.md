[toc]

# Leetcode 515. 在每个树行中找最大值
## 问题描述

[515. 在每个树行中找最大值 - 力扣（LeetCode）](https://leetcode-cn.com/problems/find-largest-value-in-each-tree-row/)

## 算法

### 解法1

#### 解法1: 实现1: 非递归

##### 解法1: 实现1: python

```
class Solution:
    def largestValues(self, root: TreeNode) -> List[int]:
        
        st = []
        ret = []
        level = 0
        lastprocessed = None
        while root or st:
            while root:
                if len(ret) == level:
                    ret.append(root.val)
                else:
                    ret[level] = max(ret[level], root.val)
                st.append((root.right, level+1))
                root = root.left
                level += 1
            root, level = st.pop()
        return ret
```
