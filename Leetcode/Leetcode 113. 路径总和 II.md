
[toc]

# Leetcode 113. 路径总和 II

## 问题描述

[113. 路径总和 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/path-sum-ii/)

## 算法

### 解法1: 后序遍历

#### 解法1: 实现1: 递归

##### 解法1: 实现：python

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

#### 解法2:实现2：非递归（利用后序遍历的特性来得到路径）

##### 解法2:实现2: python

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

#### 解法2:实现2：非递归

##### 解法2:实现2: python

```
class Solution:
    def pathSum(self, root: TreeNode, s: int) -> List[List[int]]:
        if not root: return []
        lastprocessed = None
        st = []
        retstack = []
        while root or st:
            while root:
                st.append((root, s))
                s -= root.val
                root = root.left
            root, s = st[-1]
            if not root.right or root.right == lastprocessed:
                # process root
                # print(root.val)
                # print(retstack)
                if not root.right and not root.left:
                    if root.val == s: # 叶节点
                        retstack.append([[root.val]])
                    else:
                        retstack.append([])
                else:
                    node_ret = []
                    if root.right: node_ret += retstack.pop()
                    if root.left:  node_ret += retstack.pop()
                    retstack.append([[root.val] + x for x in node_ret])
                lastprocessed = root
                st.pop()
                root = None
            else:
                s -= root.val
                root = root.right
        return retstack.pop()
```

### 解法二：回溯（实际上是先序遍历）

#### 解法二：实现

##### 解法二：实现：python

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