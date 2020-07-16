[toc]

# Leetcode 95. 不同的二叉搜索树 II

## 问题描述

[95. 不同的二叉搜索树 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/unique-binary-search-trees-ii/)

给定一个整数 n，生成所有由 1 ... n 为节点所组成的 二叉搜索树 。

示例：

输入：3
输出：
[
  [1,null,3,2],
  [3,2,null,1],
  [3,1,null,null,2],
  [2,1,3],
  [1,null,2,null,3]
]
解释：
以上的输出对应以下 5 种不同结构的二叉搜索树：

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
 

提示：

0 <= n <= 8

## 算法

### 解法1: 递归

#### 解法1: 实现1

##### 解法1: 实现1: c++

```cpp
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        vector<TreeNode*> ret;
        if (n==0) return ret;
        return helper(1, n);
    }

    vector<TreeNode*> helper(int i, int j)
    {
        vector<TreeNode*> ret;
        if (i > j) return ret;
        if (i==j) 
        {
            TreeNode* node = new TreeNode(j);
            ret.push_back(node);
            return ret;
        }
        TreeNode *node;
        vector<TreeNode*> left_ret, right_ret;
        for (int k=i; k<=j; k++)
        {
            left_ret = helper(i, k-1);
            right_ret = helper(k+1, j);
            if (left_ret.size()==0)
            {
                for (TreeNode* rightnode: right_ret)
                {
                    node = new TreeNode(k);
                    node->right = rightnode;
                    ret.push_back(node);
                }
            }
            else 
            {
                if (right_ret.size()==0)
                {
                    for (TreeNode* leftnode: left_ret)
                    {
                        node = new TreeNode(k);
                        node->left = leftnode;
                        ret.push_back(node);
                    }
                }
                else
                {
                    for (TreeNode* rightnode: right_ret)
                    {
                        for (TreeNode* leftnode: left_ret)
                        {
                            node = new TreeNode(k);
                            node->right = rightnode;
                            node->left = leftnode;
                            ret.push_back(node);
                        }
                    }
                }
            }
        }
        return ret;
    }
};
```

#### 解法1: 实现2

上面的这段代码为了处理 left_ret 和 right_ret 为空的情况，重复写了许多代码，使代码变得臃肿。

下面的代码在 left_ret 和 right_ret 为空时 push_back 了 nullptr，简化了判断。

##### 解法1: 实现2：c++

```cpp
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        vector<TreeNode*> ret;
        if (n==0) return ret;
        return helper(1, n);
    }
    
    vector<TreeNode*> helper(int i, int j)
    {
        vector<TreeNode*> ret;
        if (i > j) return ret;
        TreeNode *node;
        vector<TreeNode*> left_ret, right_ret;
        for (int k=i; k<=j; k++)
        {
            left_ret = helper(i, k-1);
            right_ret = helper(k+1, j);
            if (left_ret.size()==0) left_ret.push_back(nullptr);
            if (right_ret.size()==0) right_ret.push_back(nullptr);
            for (TreeNode* rightnode: right_ret)
            {
                for (TreeNode* leftnode: left_ret)
                {
                    node = new TreeNode(k);
                    node->right = rightnode;
                    node->left = leftnode;
                    ret.push_back(node);
                }
            }
        }
        return ret;
    }
};
```