
[toc]

# Leetcode 113. 路径总和 II

## 问题描述

[113. 路径总和 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/path-sum-ii/)

## 算法

### 解法一python 递归

#### 解法一python 递归

```
class Solution:
    def pathSum(self, root: TreeNode, sum: int) -> List[List[int]]:
        # 如果 root 为空
        if not root: return []
        # 如果 root 是叶节点
        if root and not root.left and not root.right and root.val==sum:
            return [[root.val]]
        left = self.pathSum(root.left, sum-root.val)
        right = self.pathSum(root.right, sum - root.val)
        result = []
        result += [[root.val] + path for path in left]
        result += [[root.val] + path for path in right]
        return result
```


### 解法二：python dfs


#### 解法二：python

```
class Solution:
    def pathSum(self, root: TreeNode, sum: int) -> List[List[int]]:
        ret = []
        if root is None:
            return ret

        def dfs(node, path, cursum):
            if cursum == sum and node.left is None and node.right is None:
                ret.append(path[:])
            
            for nextnode in [node.left, node.right]:
                if nextnode is not None:
                    path.append(nextnode.val)
                    cursum += nextnode.val
                    dfs(nextnode, path, cursum)
                    cursum -= nextnode.val
                    path.pop()
        
        dfs(root, [root.val], root.val)
        return ret
```

### 解法3: 后序遍历 非递归

#### 解法3:实现1

##### 解法3:实现1: python

```
class Solution:
    def pathSum(self, root: TreeNode, sum: int) -> List[List[int]]:
        if root is None:
            return []
        
        ret = []
        st = []
        node = root
        cumsum = 0
        lastprocessed = None # 最后一个处理过的节点
        while node or st:
            while node:
                cumsum += node.val
                st.append(node)
                node = node.left
            node = st[-1]
            if not node.right or node.right == lastprocessed: # 没有右节点，或者右节点处理过了
                if node.left is None and node.right is None and cumsum == sum:
                    ret.append([x.val for x in st])                                         
                st.pop()
                cumsum -= node.val
                lastprocessed = node  # 修改 lastprocessed 的指针指向
                node = None                                 # 赋值为 None，下个循环中会强制退栈
            else:                                           # 如果有右节点，并且还没有处理
                node = node.right
        return ret
```
