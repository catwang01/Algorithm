
[toc]

# Leetcode  145. 二叉树的后序遍历

## 问题描述

[145. 二叉树的后序遍历 - 力扣（LeetCode）](https://leetcode-cn.com/problems/binary-tree-postorder-traversal/)

## 算法

### 解法一：递归实现

```
class Solution:
    def postorderTraversal(self, root: TreeNode) -> List[int]:
        result = []

        def postorder(node):
            if node: # is not None
                postorder(node.left)
                postorder(node.right)
                result.append(node.val)
                
        postorder(root)
        return result  
```


### 解法2：非递归实现 颜色标记

#### 解法2: 实现

##### 解法2: c++

```
struct Elem {
     TreeNode* node;
     int color;
};
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ret;
        if (root==NULL) return ret;
        int white = 1, black = 0;
        stack<Elem> s;
        s.push({root, white});
        TreeNode* node; 
        int color;
        while (!s.empty()) {
            node = s.top().node;
            color = s.top().color;
            s.pop();
            if (color==white) {
                s.push({node, black});
                if (node->right!=NULL) s.push({node->right, white});
                if (node->left!=NULL) s.push({node->left, white});
            } else {
                // postorder processing
                ret.push_back(node->val);
            }
        }
        return ret;
    }
};
```
##### 解法2:python

```
class Solution:
    def postorderTraversal(self, root: TreeNode) -> List[int]:
        WHITE, GRAY = 0, 1
        result = []
        stack = [(root, WHITE)]
        while stack: # stack != []
            node, color = stack.pop()
            if node: # node is not None
                if color == WHITE:
                    stack.append((node, GRAY))
                    if node.right:
                        stack.append((node.right, WHITE))
                    if node.left:
                        stack.append((node.left, WHITE))
                else:
                    result.append(node.val)
        return result   
```

### 解法二：非递归实现 常规实现

#### 解法二：非递归实现 常规实现 python

```
class Solution:
    def postorderTraversal(self, root: TreeNode) -> List[int]:
        result = []
        stack = []
        while root or stack:
            while root:
                stack.append(root)
                root = root.left if root.left else root.right
            root = stack.pop()
            result.append(root.val) 
            if stack and stack[-1].left == root:
                root = stack[-1].right
            else:
                root = None
        return result
```

#### 解法二：非递归实现 常规实现 c++

```
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> s;
        while (!s.empty() || root!=NULL) {
            while (root!=NULL) {
                s.push(root);
                if (root->left != NULL) root = root -> left;
                else root = root->right;
            }
            root = s.top(); s.pop();
            result.push_back(root->val);
            if (!s.empty() && s.top()->left == root) {
                root = s.top()->right;
            } else {
                root = NULL;
            }
        }
        return result;
    }
};
```

### 解法三：非递归 保存最后处理的指针

#### 解法3: 实现

##### 解法3: python

```
class Solution:
    def postorderTraversal(self, root: TreeNode) -> List[int]:
        if root is None:
            return []
        ret = []
        st = []
        node = root
        lastfinished = None # 最后一个处理过的节点
        while node or st:
            while node:
                st.append(node)
                node = node.left
            # node is None when quit while loop
            node = st[-1]
            if not node.right or node.right == lastfinished: # 没有右节点，或者右节点处理过了
                                                             # 处理 node
                st.pop()
                ret.append(node.val)
                lastfinished = node
                node = None                                 # 赋值为 None，下个循环中会强制退栈
            else:                                           # 如果有右节点，并且还没有处理
                node = node.right
        return ret
```
