[toc]

# Leetcode 450. 删除二叉搜索树中的节点

## 问题描述

[450. 删除二叉搜索树中的节点 - 力扣（LeetCode）](https://leetcode-cn.com/problems/delete-node-in-a-bst/)

## 算法

### 解法1: 递归

有两点需要注意：
1. 如何找到要删除的结点 
2. 找到之后如何删除结点

对于 1 来说，只需要进行遍历就可以找到。但是需要注意用到二叉搜索树的性质，判断 key 是否大于 root->val 来确定是否在左右子树。


对于 2 来说，可以分为3种情况：
1. 如果 root 没有左结点，则直接返回 root->right
2. 如果 root 没有右结点，则直接返回 root->left
3. 如果 root 有左右结点。当删除 root 之后，得到了两个子树 root->left, root->right，问题转换为如何将这两个子树连接起来。

有两种思路

a. 一种是找到右子树最左边的结点（称为successor），或左子树最右边的结点(称为predecessor)，作为新的头。(下面以找到 successor 为例。)

![picture goes here](https://gitee.com/EdwardElric_1683260718/picture_bed/raw/master/img/20200430111156.png)

找到之后将其从原来的树上取下，然后将 root->left 和 root->right 连接到上面。

![picture goes here](https://gitee.com/EdwardElric_1683260718/picture_bed/raw/master/img/20200430112351.png)

这会导致遍历时需要保存父结点。因为只是找到 successor 还不够，还要将其从原来的树上取下来，因此需要保存其 parent，然后令 parent->left = NULL。这样会比较麻烦。

b. 另一种思路是参考 [1] 中的思路，将root->left 直接连接到 successor 上。

![盗一张人家的图](https://gitee.com/EdwardElric_1683260718/picture_bed/raw/master/img/20200430113136.png)

#### 解法1:实现

##### 解法1: 实现： c++

参考了 [1]

```
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return NULL;
        int flag = root->val == key ? 0: (root->val > key ? 1: -1);
        switch (flag) {
            case -1:
                // 当前结点值小于k,说明在右边的结点
                root->right = deleteNode(root->right, key);
                return root;
            case 1:
                // 当前结点值大于k,说明在左边的结点
                root->left = deleteNode(root->left, key);
                return root;
            case 0:
                // 如果左右结点至多只有一个，返回那个结点
                if (!root->left || !root->right)
                    return root->left ? root->left: root->right;
                // 左右结点都存在，找到root的右子树最左边的结点，将root的左子树链接到上面
                TreeNode* node = root->right;
                while (node->left) {
                    node = node->left;
                }
                node->left = root->left;
                return root->right;
        }
        return NULL;
    }
};
```

##### 解法1: 实现： python

```
class Solution:
    def deleteNode(self, root: TreeNode, key: int) -> TreeNode:
        if not root: return root
        if root.val == key:
            leftmost = self.leftmost(root.right)
            if not leftmost: return root.left
            leftmost.left = root.left
            return root.right
        elif root.val > key:  
            root.left = self.deleteNode(root.left, key)
        else:
            root.right = self.deleteNode(root.right, key)
        return root

    def leftmost(self, root):
        if not root: return root
        while root.left:
            root = root.left
        return root
```

### 解法2：

##### 解法2：实现： c++

```
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return root;
        if (root->val == key)
        {
            if (root->right)
            {
                leftmost(root->right)->left = root->left;
                return root->right;
            }
            else 
            {
                return root->left;
            }
        } 
        else
        {
            if (root->val < key)
            {
                root->right = deleteNode(root->right, key);
            }
            else 
            {
                root->left = deleteNode(root->left, key);
            }
            return root;
        }
    }

    TreeNode* leftmost(TreeNode* root)
    {
        if (!root->left) return root;
        return leftmost(root->left);
    }
};
```

# References
1. [450. 删除二叉搜索树中的节点 - 删除二叉搜索树中的节点 - 力扣（LeetCode）](https://leetcode-cn.com/problems/delete-node-in-a-bst/solution/450-shan-chu-er-cha-sou-suo-shu-zhong-de-jie-dia-6/)
