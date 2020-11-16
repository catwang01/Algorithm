

[toc]

# Leetcode 98. 验证二叉搜索树

[98. 验证二叉搜索树 - 力扣（LeetCode）](https://leetcode-cn.com/problems/validate-binary-search-tree/)

## 算法

### 解法一：中根遍历

根据二叉搜索树的性质，其中根遍历序列是递增序列。因此可以将其中根遍历后的结果保存在 list 中，之后判断 list 中的元素是否严格递增的；

这个方法可以优化： 我们并不需要用一个list来保存结果，因为每次比较只涉及到两个值，因此可以用一个变量 prev 来保存之前的值，如果当前结点的值小于 prev，则但新 prev，否则直接返回 False

```
if prev < node.val:
    prev = node.val
else:
    return False
```

时间复杂度： $O(n)$ 最坏情况下遍历整个二叉树
空间复杂度： $O(n)$ 最坏情况下栈的大小为 $O(n)$

#### 解法1: 实现1: 非递归（颜色标记法）

##### 解法1: 实现1: python

```
class Solution:
    def isValidBST(self, root: TreeNode) -> bool:
        # inorder traverse
        cur = -float('inf')
        WHITE, GRAY = 0, 1
        stack = [(root, WHITE)]
        
        while stack: # stack != []
            node, color = stack.pop()
            if node: # node is not None
                if color == WHITE:
                    stack.append((node.right, WHITE))
                    stack.append((node, GRAY))
                    stack.append((node.left, WHITE))
                else:
                    if node.val > cur:
                        cur = node.val
                    else:
                        return False
        return True
```

#### 解法1: 实现2: 常规递归

##### 解法1: 实现2: c++

```
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        auto inorder_process = [&](TreeNode* node) {};
        if (!root) return true;
        stack<TreeNode*> st;
        long long last = LONG_MIN;
        while (root || st.size())
        {
            while (root)
            {
                st.push(root);
                root = root->left;
            }
            root = st.top(); st.pop();
            if (last < root->val)  { last = root->val;}
            else return false;
            root = root->right;
        }
        return true;
    }
};
```

##### 解法1: 实现2: python

```
class Solution:
    def isValidBST(self, root: TreeNode) -> bool:
        lastval = -float("inf")
        st = []
        while root or st:
            while root:
                st.append(root)
                root = root.left
            root = st.pop()
            if lastval >= root.val:
                return False
            else:
                lastval = root.val
            root = root.right
        return True
```

#### 解法1: 实现3: 递归

##### 解法1: 实现3: c++

```
class Solution {
public:
    long long pre = LONG_MIN;
    bool isValidBST(TreeNode* root) {
        if (!root) return true;
        // 左节点
        if (!isValidBST(root->left))
            return false;
        // 处理当前节点
        if (pre < root->val) pre = root->val;
        else return false;
        // 右节点
        return isValidBST(root->right);
    }
};
```

### 解法二：递归

相当于 preorder traversal

![3f80d46f01de8565e21b5a1e568da466.png](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p10567)@w=500

#### 解法二python

```
class Solution:
    def isValidBST(self, root: TreeNode) -> bool:

        def aux(node, minval, maxval):
            if not node: return True
            if minval < node.val < maxval:
                return aux(node.left, minval, node.val) and aux(node.right, node.val, maxval)
            else:
                return False

        return aux(root, -float('inf'), float('inf'))
```