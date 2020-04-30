[toc]

# Nowcoder 二叉搜索树与双向链表

## 问题描述

[二叉搜索树与双向链表_牛客网](https://www.nowcoder.com/practice/947f6eb80d944a84850b0538bf0ec3a5?tpId=13&tqId=11179&rp=1&ru=%2Fta%2Fcoding-interviews&qru=%2Fta%2Fcoding-interviews%2Fquestion-ranking&tPage=2)

## 算法

### 解法1: postorder

关键是得到一个树的最左边的子结点和最右边的子结点。

这里有很奇怪的一点还没有理解清楚。这个问题是中序遍历的问题。这里却用了 postorder 来解决了。

# Todo - 2020-04-29 11:44 -- by ed 

虽然有点奇怪。不过貌似可以解释通。用postorder 来解决 inorder的问题。所以这一个的代码量比直接用 inorder 的要大。

#### 解法1:实现1: 递归

##### 解法1: c++

```
class Solution {
public:
    struct Item {
        TreeNode *leftmost, *rightmost;
    };
    TreeNode* Convert(TreeNode* root)
    {
        if (!root || (!root->left && !root->right)) 
            return root;
        return helper(root).leftmost;
    }

    Item helper(TreeNode* root) {
        TreeNode *leftmost = root, *rightmost = root;
        if (root->left) {
            auto retleft = helper(root->left);
            retleft.rightmost -> right = root;
            root -> left = retleft.rightmost;
            leftmost = retleft.leftmost;
        }
        if (root->right) {
            auto retright = helper(root->right);
            retright.leftmost -> left = root;
            root ->right = retright.leftmost;
            rightmost = retright.rightmost;
        }
        return {leftmost, rightmost};
    }
};
```

### 解法2: inorder

这个从递归的角度可能比较复杂。但是从中序遍历的角度来开比较简单。就只是按照中序遍历的顺序将所有的结点连成一个双向链表。

#### 解法2:实现1: 非递归

##### 解法2: c++

下面是使用颜色标记法的中序遍历，入栈时检查是否为 null

```
class Solution {
public:
    TreeNode* Convert(TreeNode* root)
    {
        if (!root) return root;
        int white = 1, black = 0;
        stack<pair<TreeNode*, int>> s;
        s.push({root, white});
        TreeNode *curNode;

        // 使用头插法建立双向链表
        TreeNode node(0), *virtualHead = &node, *cur = virtualHead;

        int curColor;
        while (!s.empty()) {
            curNode = s.top().first;
            curColor = s.top().second;
            s.pop();
            if (curColor==white) {
                if (curNode->right) s.push({curNode->right, white});
                s.push({curNode, black});
                if (curNode->left) s.push({curNode->left, white}); 
            } else {
                // inorder processing
                cur->right = curNode;
                curNode->left = cur;
                cur = cur->right;
            }
        }

        TreeNode *ret = virtualHead->right;
        // 断开与虚拟头结点的链接
        ret->left = NULL;
        return ret;
    }
};
```

#### 解法2:实现2:递归

##### 解法2: 实现2: c++

```
class Solution {
public:
    TreeNode* Convert(TreeNode* root)
    {
        if (!root) return NULL;
        TreeNode *cur = NULL;
        // cur表示双向链表的尾结点。初始化为0，表示双向链表为空
        inorder(root, cur);
        // 双向链表的尾结点遍历到头结点
        while (cur->left)
            cur = cur->left;
        return cur;
    }

    void inorder(TreeNode* root, TreeNode*& cur) {
         if (!root) return;
         inorder(root->left, cur);
         if (cur) {
             cur->right = root;
             root->left = cur;
         }
         cur = root;
         inorder(root->right, cur);
    }
};
```

