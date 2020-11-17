
[toc]

# Leetcode 547. 朋友圈 

## 问题描述

[547. 朋友圈 - 力扣（LeetCode）](https://leetcode-cn.com/problems/friend-circles/)


## 算法

### 解法1: 并查集


#### 解法1: c++

```cpp
class UF {
    int n;
    vector<int> parent;
    vector<int> weight;
    int size;
    public:

        UF(int n=0) {
            this->n = n;
            parent.resize(n);
            weight.resize(n);
            for(int i=0; i<n; i++)
            {
                parent[i] = i;  
                weight[i] = 1;
            }
            size = n;
        }
        
        int find(int i) {
            while (i != parent[i]) {
                i = (parent[i] = parent[parent[i]]);
            }
            return i;
        }
    
        void connect(int i, int j) {
            int parent_i = find(i);
            int parent_j = find(j);
            if (parent_i==parent_j) return;
            if (weight[parent_i] > weight[parent_j]) 
            {
                parent[parent_j] = parent_i;
                weight[parent_i] += weight[parent_j];
            } 
            else
            {
                parent[parent_i] = parent_j;
                weight[parent_j] += weight[parent_i];
            }
            size --;
        }
        
        int getSize() {return size;}
};
class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        int n = M.size();
        if (n==0) return 0;
        UF uf(n);
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (M[i][j]) uf.connect(i, j);
            }
        }
        return uf.getSize();
    }
};
```

### 解法2: dfs

##### 解法2: 实现：python

```
class Node:
    def __init__(self):
        self.children = []
        self.seen = 0

class Solution:
    def findCircleNum(self, M: List[List[int]]) -> int:
        
        n = len(M)
        if n <= 1: return n
        nodes = [Node() for i in range(n)]
        for i in range(n):
            for j in range(n):
                if M[i][j] == 1:
                    nodes[i].children.append(nodes[j])
                    nodes[j].children.append(nodes[i])
            
        ret = 0
        for node in nodes:
            if node.seen == 0:
                self.dfs(node)
                ret += 1
        return ret

    def dfs(self, node):
        node.seen = 1
        for child in node.children:
            if child.seen == 0: self.dfs(child)
```