
[toc]

# Leetcode 687. 最长同值路径

## 问题描述

[687. 最长同值路径 - 力扣（LeetCode）](https://leetcode-cn.com/problems/longest-univalue-path/)

## 算法

### 解法一：递归

![](https://gitee.com/EdwardElric_1683260718/picture_bed/raw/master/img/20200925174823.png)


#### 解法一python

```
class Solution:
    def longestUnivaluePath(self, root: TreeNode) -> int:
        num = 0

        def _longestUnivaluePath(node):
            nonlocal num
            if not node: return 0

            leftNum = _longestUnivaluePath(node.left)
            rightNum = _longestUnivaluePath(node.right)

            if node.left and node.right and node.val==node.left.val==node.right.val:
                num = max(num, leftNum+rightNum+2)
                return max(leftNum, rightNum)+1
            if node.left and node.left.val == node.val:
                num = max(num, leftNum+1)
                return leftNum+1
            if node.right and node.right.val == node.val:
                num = max(num, rightNum+1)
                return rightNum+1
            return 0

        _longestUnivaluePath(root)
        return num
```

### 解法2: 转化为非递归

##### 解法2: python

```
class Solution:
    def longestUnivaluePath(self, root: TreeNode) -> int:
        
        if not root: return 0
        
        maxlen = 0

        def process(node, ret_stack):
            nonlocal maxlen
            if node.right: right_ret = ret_stack.pop()
            if node.left: left_ret = ret_stack.pop()
            if node.left and node.right and node.left.val == node.right.val == node.val:
                maxlen = max(maxlen, left_ret + right_ret + 2)
                cur_ret = max(left_ret, right_ret) + 1
            elif node.left and node.left.val == node.val:
                maxlen = max(maxlen, 1 + left_ret)
                cur_ret  = 1 + left_ret
            elif node.right and node.right.val == node.val:
                maxlen = max(maxlen, 1 + right_ret)
                cur_ret = 1 + right_ret
            else:
                cur_ret = 0
            ret_stack.append(cur_ret)
                

        st = []
        ret_stack = [] # 结果栈
        lastprocessed = None
        while st or root:
            while root:
                st.append(root)
                root = root.left
            root = st[-1]
            if root.right is None or root.right == lastprocessed:
                # process root
                process(root, ret_stack)
                lastprocessed = root
                st.pop()
                root = None
            else:
                root = root.right

        return maxlen
```



