[toc]

# Leetcode 144. 二叉树的前序遍历


## 问题描述

[144. 二叉树的前序遍历 - 力扣（LeetCode）](https://leetcode-cn.com/problems/binary-tree-preorder-traversal/)

## 算法

### 解法1：递归

#### 解法1：实现

##### 解法1：python

```
class Solution:
    def preorderTraversal(self, root: TreeNode) -> List[int]:
        result = []
        def preorder(node):
            if node: # if node is not None
                result.append(node.val)
                preorder(node.left)
                preorder(node.right)
        preorder(root)
        return result
```

##### 解法1：c++


```
class Solution {
public:
    void preorder(vector<int>& result, TreeNode* node) {
        if (node != NULL) {
            result.push_back(node->val);
            preorder(result, node->left);
            preorder(result, node->right);
        }
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        preorder(result, root);
        return result;
    }
};
```

##### 解法1：java

```
class Solution {
    public List<Integer> preorderTraversal(TreeNode root) {
        List<Integer> result = new ArrayList<Integer>();
        preorder(root, result);
        return result;
    }
    public void preorder(TreeNode node, List<Integer> result) {
        if (node==null) return ;
        result.add(node.val);
        preorder(node.left, result);
        preorder(node.right, result);
    }
}
```

### 解法2.1：非递归实现 

#### 解法2.1：实现

##### 解法2.1：python

```
class Solution:
    def preorderTraversal(self, root: TreeNode) -> List[int]:
        result = []
        stack = [root]
        while stack: # while stack != []
            node = stack.pop()
            if node: # if node is not None
                result.append(node.val)
                stack.append(node.right)
                stack.append(node.left)
        return result
```

### 解法2.2：非递归实现（常规解法）

#### 解法2.2:实现

##### 解法2.2:python

```
class Solution:
    def preorderTraversal(self, root: TreeNode) -> List[int]:
        result = []
        stack = []
        while stack or root:
            while root:
                result.append(root.val)
                stack.append(root.right) # 保存右分支
                root = root.left # 沿左分支下行
            root = stack.pop()
        return result
```

#### 解法2.2：非递归实现

##### 解法2.2:java

```
class Solution {
    public List<Integer> preorderTraversal(TreeNode root) {
        List<Integer> result = new ArrayList<Integer>();
        Stack<TreeNode> s = new Stack<TreeNode>();
        while (!s.empty() || root != null) {
            while(root!=null) {
                result.add(root.val);
                s.push(root.right);
                root = root.left;
            }
            root = s.pop();
        }
        return result;
    }
}
```