
[toc]

# Leetcode 236. 二叉树的最近公共祖先

## 问题描述 

[236. 二叉树的最近公共祖先 - 力扣（LeetCode）](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/)


给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（**一个节点也可以是它自己的祖先**）。”

例如，给定如下二叉树:  root = \[3,5,1,6,2,0,8,null,null,7,4\]

![f2660bc712bf0a802e26ae97e1677ed6.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p10519)

**示例 1:**

**输入:** root = \[3,5,1,6,2,0,8,null,null,7,4\], p = 5, q = 1
**输出:** 3
**解释:** 节点 `5` 和节点 `1` 的最近公共祖先是节点 `3。`

**示例 2:**

**输入:** root = \[3,5,1,6,2,0,8,null,null,7,4\], p = 5, q = 4
**输出:** 5
**解释:** 节点 `5` 和节点 `4` 的最近公共祖先是节点 `5。`因为根据定义最近公共祖先节点可以为节点本身。

**说明:**

*   所有节点的值都是唯一的。
*   p、q 为不同节点且均存在于给定的二叉树中。


## 算法

### 解法一：利用父结点的指针


关键是如果记录每个结点的父结点；

可以利用先遍历一次，对每个结点添加父结点的指针来得到每个结点的父结点；

时间复杂度： $O(n)$
空间复杂度： $O(n)$ 添加了 parent 

#### 解法一python

利用python可以直接给TreeNode对象添加parent属性，用来指向其父结点；
这里利用了 bfs 来进行一次遍历（也可以用dfs），从而给所有的结点添加 parent属性，为了之后找公共父结点的方便，还添加了 level 属性；

```
from collections import deque
class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        if not p or not q: return None
        self.bfs(root)
        leftLeve, rightLevel = p.level, q.level
        while p != q:
            if p.level > q.level:
                p = p.parent
            else:
                q = q.parent
        return p
 
    def bfs(self, root):
        queue = deque()
        queue.append(root)
        level = -1
        while queue: # q is not None
            levelsize = len(queue)
            level += 1
            for _ in range(levelsize):
                node = queue.popleft()
                node.level = level
                if node.left:
                    node.left.parent = node
                    queue.append(node.left)
                if node.right:
                    node.right.parent = node
                    queue.append(node.right)
```

也可以直接用一个字典来贮存父结点的信息。

### 解法2: 利用父节点的指针 + 两个链表在第一个公共节点

如果将hash表看做是从子节点到父结点的一个链接的话，那么这个hash表实际上定义了一个链表。链表有两个头 p 和 q。现在想找到 p 和 q 的相遇的节点，实际上是下面的这问题 [剑指 Offer 52. 两个链表的第一个公共节点](https://leetcode-cn.com/problems/liang-ge-lian-biao-de-di-yi-ge-gong-gong-jie-dian-lcof/)

#### 解法2: python

```
from collections import deque
class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        # 这里使用 bfs 来建立指向父节点的指针
        parentDict = {root: None}
        queue = deque([root])
        while queue:
            node = queue.popleft()
            if node.left:
                parentDict[node.left] = node
                queue.append(node.left)
            if node.right:
                parentDict[node.right] = node
                queue.append(node.right)
        # 这里使用了 剑指 Offer 52. 两个链表的第一个公共节点 的思路
        curp, curq = p, q
        while curp != curq:
            print("val: %d, val: %d" %(curp.val, curq.val))
            curp = parentDict[curp] if curp else q
            curq = parentDict[curq] if curq else p
        return curp
```

### 解法3: 递归（这个比较好，但是难理解）

首先进行特判：

1. root 为 None，说明整个树为空，返回 None
2. root == p，说明整个树以 p 为根结点，当然会返回 p
3. root == q，说明整个树以 q 为根结点，当然会返回 q

上面三种情况在python中可以合并为一句

```
if not root or root == p or root == q: return root
```

不满足特判条件时，考虑向下递归。分两种情况：
1. p、q 同时在 root.left 的子树中，那么直接返回 lowestCommonAncestor(root.left, p, q)；root.right 的情况类似

2. p、q 一个在 root.left 的子树中，一个在 root.right 的子树中。此时返回 root。

而我们目前可以计算的值是 

```
left = lowestCommonAncestor(root.left, p, q)
right = lowestCommonAncestor(root.right, p, q)
```

因此我们要做的是从 left 和 right 的返回值中来区别上面两种情况。

1. 如果 p 和 q 都在 root.left  的子树中，那么 left 的值是 p和q 的LCA，而 right 的值为 None（这个可以从特判条件中推出来）

2. 如果 p 和 q 都在 root.right  的子树中，那么 right 的值是 p和q 的LCA，而 left 的值为 None（这个可以从特判条件中推出来）

3. 如果 p 在 root.left 的子树中，q 在 root.right 的子树中，则 left 的值为 p，right 的值为 q。

4. 如果 p 在 root.right 的子树中，q 在 root.left 的子树中，则 right 的值为 p，right 的值为 q。


可以看到，当 left 和 right 中有一个为 None 时，直接返回另一个即可（对应上面的1、2）；当 left 和 right 中两个同时不为 None 时，对应上面的第3、4，因此返回 root 即.

时间复杂度：$O(n)$，最坏情况下遍历所有节点
空间复杂度： $O(n)$，最坏情况下栈深为 N

#### 解法3: 实现
##### 解法3: python

```
class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        if not root or root == p or root == q: return None
        left = self.lowestCommonAncestor(root.left, p, q)
        right = self.lowestCommonAncestor(root.right, p, q)
        if not left: return right
        if not right: return left
        return root
```

# References
1. [236. 二叉树的最近公共祖先（后序遍历 DFS ，清晰图解） - 二叉树的最近公共祖先 - 力扣（LeetCode）](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/solution/236-er-cha-shu-de-zui-jin-gong-gong-zu-xian-hou-xu/)