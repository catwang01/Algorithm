[toc]

# Leetcode 105. 从前序与中序遍历序列构造二叉树

## 问题描述

[105. 从前序与中序遍历序列构造二叉树 - 力扣（LeetCode）](https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)

[面试题07. 重建二叉树 - 力扣（LeetCode）](https://leetcode-cn.com/problems/zhong-jian-er-cha-shu-lcof/)

根据一棵树的前序遍历与中序遍历构造二叉树。

**注意:**
你可以假设树中没有重复的元素。

例如，给出

前序遍历 preorder = [3,9,20,15,7]
中序遍历 inorder = [9,3,15,20,7]

返回如下的二叉树：
 
```
    3
   / \
  9  20
    /  \
   15   7   
```
## 算法

### 解法一：分治法

时间复杂度： $O(nlogn)$
其中，合并用时 $O(n)$，由 master 定理 
T(n) = 2T(n/2) + O(n) => T(n) = O(nlogn)
空间复杂度： $O(1)$ 除了存储整个树之外只用了常数空间

#### 解法1: 实现1:

##### 解法1: 实现1: python

```
class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:
        if not inorder:
            return None
        head_val = preorder[0]
        head = TreeNode(head_val)
        idx = inorder.index(head_val) # O(n) 的复杂度
        head.left = self.buildTree(preorder[1:idx+1], inorder[:idx])
        head.right = self.buildTree(preorder[idx+1:], inorder[idx+1:])
        return head
```

#### 解法1: 实现2

不需要真的传入列表，而是传入index
##### 解法1: 实现2: c++

```
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return builder(0, preorder.size(), 0, inorder.size(), preorder, inorder);
    }

    TreeNode* builder(int prelow, int prehigh, int inlow, int inhigh, const vector<int>& preorder, const vector<int>& inorder) {
        if (prelow == prehigh) return NULL;
        TreeNode* head = new TreeNode(preorder[prelow]);

        int i;
        for (i=inlow; i<inhigh; i++) {
            if (preorder[prelow]==inorder[i]) {
                break;
            }
        }

        head->left = builder(
            prelow+1, i - inlow + prelow + 1, 
            inlow, i, 
            preorder, inorder
        );

        head->right = builder(
            i - inlow + prelow + 1, prehigh,
            i+1, inhigh,
            preorder, inorder
        );
        return head;
    }
};
```

#### 解法1: 实现3: python

inorder.index 这句的时间复杂度为 $O(n)$，利用 hash表可以降低为 $O(1)$

时间复杂度： $O(n)$
其中，合并用时 $O(n)$，由 master 定理 
T(n) = 2T(n/2) + O(1) => T(n) = O(n)
空间复杂度： $O(n)$ 除了存储整个树之外，

##### 解法1: 实现3: python

```
class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:
        n = len(preorder)
        hashmap = {inorder[i]:i for i in range(n)}
        
        # preorder[prelow:prehigh+1] 是先序遍历
        # inorder[inlow:inhigh+1] 是中序列遍历
        
        def _buildTree(prelow, prehigh, inlow, inhigh):
            if prelow > prehigh:
                return None
            node = TreeNode(preorder[prelow])
            idx = hashmap[preorder[prelow]]
            node.left = _buildTree(prelow+1, idx-inlow+prelow, inlow, idx-1)
            node.right = _buildTree(prehigh-inhigh+idx+1, prehigh, idx+1, inhigh)
            return node

        return _buildTree(0, n-1, 0, n-1)
```

##### 解法1: 实现3: c++

```
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> val2idx;
        for (int i=0; i<inorder.size(); i++) 
            val2idx[inorder[i]] = i;
        return builder(0, preorder.size(), 0, inorder.size(), preorder, inorder, val2idx);
    }

    TreeNode* builder(int prelow, int prehigh, int inlow, int inhigh, const vector<int>& preorder, const vector<int>& inorder, unordered_map<int, int>& val2idx) {
        if (prelow == prehigh) return NULL;
        TreeNode* head = new TreeNode(preorder[prelow]);

        int i = val2idx[preorder[prelow]];

        head->left = builder(
            prelow+1, i - inlow + prelow + 1, 
            inlow, i, 
            preorder, inorder,
            val2idx
        );

        head->right = builder(
            i - inlow + prelow + 1, prehigh,
            i+1, inhigh,
            preorder, inorder,
            val2idx
        );
        return head;
    }
};
```
