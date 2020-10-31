
[toc]

# Leetcode 110. 平衡二叉树

## 问题描述

[110. 平衡二叉树 - 力扣（LeetCode）](https://leetcode-cn.com/problems/balanced-binary-tree/)

## 算法

只需要遍历，并判断每个结点的左右子树的高度之差是否小于等于 1

### 解法一：递归 

直接看代码

这种方法的缺点是有大量重复计算；调用对于每个结点都独立地调用了 getHeight 函数，没有利用子结点的高度信息来计算父结点的高度

```
class Solution:
    def isBalanced(self, root: TreeNode) -> bool:
        if not root: return True
        if abs(self.getHeight(root.left) - self.getHeight(root.right))> 1:
            return False
        else:
            return self.isBalanced(root.left) and self.isBalanced(root.right)
        
    def getHeight(self, node):
        return 1 + max(self.getHeight(node.left), self.getHeight(node.right)) if node else 0
```


### 解法2： postorder 

#### 解法2: 实现2: 递归

在求二叉树的高度[104. 二叉树的最大深度 - 力扣（LeetCode）](https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/) 基础上，使用 -1 来标记不平衡的情况。

```cpp
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return getHeight(root) != -1;
    }
    int getHeight(TreeNode* root) {
        if (!root) return 0;
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);
        // 在二叉树高度基础上添加了一个判断
        if (leftHeight==-1 || rightHeight==-1 || abs(leftHeight - rightHeight) > 1) 
            return -1;
        else 
            return max(leftHeight, rightHeight) + 1;
    }
};
```

### 解法3: postorder 非递归

#### 解法3:实现

使用 postorder 来进行遍历。因为某个节点要在它的左右子节点处理完成之后进行处理。

而且为了保存中间结果，还需要使用一个 hash 表。

##### 解法3：实现: python

```
from collections import deque

class Solution:
    def isBalanced(self, root: TreeNode) -> bool:      
        stack = []
        node = root
        leftDepth, rightDepth = {}, {}
        while stack or node:
            while node:
                stack.append(node)
                node = node.left if node.left else node.right
            node = stack.pop() # 回溯时处理数据
            if node:
                leftDepth[node] = 1 + max(leftDepth[node.left], rightDepth[node.left]) if node.left else 0
                rightDepth[node] = 1 + max(leftDepth[node.right], rightDepth[node.right]) if node.right else 0
                if abs(leftDepth[node] - rightDepth[node]) > 1:
                    return False
            if stack and stack[-1].left == node:
                node = stack[-1].right
            else:
                node = None # 强制退栈
        return True
```

#### 解法2: 实现2: 非递归 颜色标记法 + hash 表保存中间结果

##### 解法2: c++

```
class Solution {
public:
    enum Color {white, black};

    struct Item
    {
        TreeNode* node;
        Color color;
    };

    bool isBalanced(TreeNode* root) {
        if (root==nullptr) return true;
        unordered_map<TreeNode*, int> height;

        stack<Item> st;
        st.push({root, white});
        while (!st.empty())
        {
            Item item = st.top(); st.pop();
            TreeNode* node = item.node;
            Color color = item.color;

            if (color == white)
            {
                st.push({node, black});
                if (node->right) st.push({node->right, white});
                if (node->left) st.push({node->left, white});
            }
            else
            {
                // postorder
                if (abs(height[node->left] - height[node->right]) > 1)
                    return false;
                else
                    height[node] = max(height[node->left], height[node->right]) + 1;
            }
        }
        return true; 
    }
};
```