
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
