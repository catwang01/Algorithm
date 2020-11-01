
[toc]

# Leetcode 94. 二叉树的中序遍历

[94. 二叉树的中序遍历 - 力扣（LeetCode）](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/submissions/)

## 算法

### 解法一：递归实现

#### 解法一：实现

##### 解法一：c++

```
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        inorder(root, result);
        return result;
    }

    void inorder(TreeNode* node, vector<int>& result){
        if (node==NULL) return;
        inorder(node->left, result);
        result.push_back(node->val);
        inorder(node->right, result);
    }
};
```

##### 解法一：python

```
class Solution:
    def inorderTraversal(self, root: TreeNode) -> List[int]:
        result = []        
        def traversal(node):
            if node is None:
                return 
            traversal(node.left)
            result.append(node.val)
            traversal(node.right)
        traversal(root)
        return result
```

### 解法2：非递归实现（颜色标记）

主要参考这个： [颜色标记法-一种通用且简明的树遍历方法 - 二叉树的中序遍历 - 力扣（LeetCode）](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/solution/yan-se-biao-ji-fa-yi-chong-tong-yong-qie-jian-ming/)

#### 解法2:实现

##### 解法2: python

```
class Solution:
    def inorderTraversal(self, root: TreeNode) -> List[int]:
        WHITE, GRAY = 0, 1
        result = []   
        stack = [(root, WHITE)]
        while stack: # stack != []
            node, color = stack.pop()
            if node: # node is not None:
                if color == WHITE:
                    if node.right:
                        stack.append((node.right, WHITE))
                    stack.append((node, GRAY))
                    if node.left:
                        stack.append((node.left, WHITE))
                else:
                    result.append(node.val)
        return result
```

##### 解法2:c++

```
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        if (root == NULL) return ret;

        int white = 1, black = -1;
        stack<pair<TreeNode*, int>> s;
        s.push({root, white});
        int color;
        TreeNode* node;
        while (!s.empty()) {
            node = s.top().first;
            color = s.top().second;
            s.pop();
            if (color==white) {
                if (node->right != NULL) s.push({node->right, white});
                s.push({node, black});
                if (node->left != NULL) s.push({node->left, white});
            } else {
                ret.push_back(node->val);
            }
        }
        return ret;
    }
};
```

### 解法二：非递归实现（常规方法）


##### 解法2: 实现： c++

```
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        stack<TreeNode*> st;
        while (root || st.size())
        {
            while (root)
            {
                st.push(root);
                root = root->left;
            }
            root = st.top(); st.pop();
            ret.push_back(root->val);
            root = root->right;
        }  
        return ret;
    }
};
```

##### 解法2: python

```
class Solution:
    def inorderTraversal(self, root: TreeNode) -> List[int]:
        stack = []
        result = []

        while stack or root: # stack != [] or root is not None
            while root:  
                stack.append(root) # 父节点入栈
                                 # 注意，栈中的元素一定非空
                root = root.left # 左枝下行
            root = stack.pop()   # 遇到空村回溯
            # inorder processing
            result.append(root.val)
            root = root.right
        return result
```


# References

- [颜色标记法-一种通用且简明的树遍历方法 - 二叉树的中序遍历 - 力扣（LeetCode）](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/solution/yan-se-biao-ji-fa-yi-chong-tong-yong-qie-jian-ming/)
