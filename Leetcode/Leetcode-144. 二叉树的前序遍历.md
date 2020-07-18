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
        ret = []
        def preorder(node):
            if not node: return
            ret.append(node.val)
            preorder(node.left)
            preorder(node.right)
        preorder(root)
        return ret
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

### 解法2：非递归实现 

#### 解法2：实现1

##### 解法2：python

```
class Solution:
    def preorderTraversal(self, root: TreeNode) -> List[int]:
        result = []
        stack = [root]
        while stack: # while stack != []
            node = stack.pop()
            result.append(node.val)
            if node.right: stack.append(node.right)
            if node.left: stack.append(node.left)
        return result
```

#### 解法2:实现2 常规解法

##### 解法2:python

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

##### 解法2:java

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

#### 解法2: 实现3 颜色标记法

##### 解法2:实现3 python

```
class Solution:
    def preorderTraversal(self, root: TreeNode) -> List[int]:
        ret = []
        if not root: return ret
        black, white = 0, 1
        st = [(root, white)]
        while st:
            node, color = st.pop()
            if color == white:
                if node.right: 
                    st.append((node.right,  white))
                if node.left: 
                    st.append((node.left, white))
                st.append((node, black))
            else:
                ret.append(node.val)
        return ret
```