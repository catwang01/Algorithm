[toc]

# Leetcode 297. 二叉树的序列化与反序列化


## 问题描述

[297. 二叉树的序列化与反序列化 - 力扣（LeetCode）](https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/)

## 算法

### 解法1: bfs 

#### 解法1: 实现

##### 解法1: c++

```
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string ret = "";
        queue<TreeNode*> q;
        q.push(root);
        TreeNode* node;
        while (q.size())
        {
            node = q.front(); q.pop();
            if (node)
            {   
                ret += to_string(node->val) + ",";
                q.push(node->left);
                q.push(node->right);
            }
            else 
            {
                ret += "null,";
            }
        }
        return "[" + ret.substr(0, ret.size()-1) + "]";
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int n = data.size();
        if (n <= 6) return nullptr;
        int i = 1, j;
        
        vector<TreeNode*> preorder;
        stringstream ss;
        while (i <= n - 2)  // 利用滑动窗口来实现split操作
        {
            j = i;
            while (j <= n - 2 && data[j] != ',')
            {
                j++;
            }
            string val = data.substr(i, j-i);
            if (val=="null") {
                preorder.push_back(nullptr);
            } else {
                ss.clear(); ss << val;
                int val_; 
                ss >> val_;
                preorder.push_back(new TreeNode(val_));
            }
            i = j + 1;
        }
        return helper(preorder);
    }

    TreeNode* helper(const vector<TreeNode*>& preorder)
    {
        if (preorder.empty()) return nullptr;
        queue<TreeNode*> level;
        level.push(preorder[0]);
        int i = 1;
        while (i < preorder.size())
        {
            TreeNode* node = level.front(); level.pop();
            if (!node) continue;
            node->left = preorder[i];
            level.push(preorder[i]);
            i++;
            node->right = preorder[i];
            level.push(preorder[i]);
            i++;
        }
        return preorder[0];
    }
};
```

### 解法2: preorder

#### 解法2:实现1:递归

##### 解法2:实现1: c++

```
class Codec {
public:
    void serialize_preorder(TreeNode* root, vector<string>& strs)
    {
        if (!root) {
            strs.push_back("null");
            return;
        }
        strs.push_back(to_string(root->val));
        serialize_preorder(root->left, strs);
        serialize_preorder(root->right, strs);
    }
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        vector<string> strs;
        serialize_preorder(root, strs);
        string ret = "[";
        for (auto &s: strs) ret += s + ",";
        cout << ret.substr(0, ret.size()-1) + "]" << endl;
        return ret.substr(0, ret.size()-1) + "]";
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize_preorder(deque<TreeNode*>& nodes)
    {
        if (nodes.empty()) return nullptr;
        TreeNode* node = nodes.front();
        nodes.pop_front();
        if (!node) return nullptr;
        node->left = deserialize_preorder(nodes);
        node->right = deserialize_preorder(nodes);
        return node;
    }

    TreeNode* deserialize(string data) {
        deque<TreeNode*> nodes;
        stringstream ss(data.substr(1, data.size()-2));
        string s;
        while (getline(ss, s, ','))
        { 
           if (s=="null") nodes.push_back(nullptr);
           else nodes.push_back(new TreeNode(stoi(s)));
        }
        return deserialize_preorder(nodes);
    }
};
```