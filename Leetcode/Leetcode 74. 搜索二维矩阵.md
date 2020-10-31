[toc]

# Leetcode 74. 搜索二维矩阵 

## 问题描述

[74. 搜索二维矩阵 - 力扣（LeetCode）](https://leetcode-cn.com/problems/search-a-2d-matrix/submissions/)


## 算法
### 法一：bruteforce

遍历行、列；

### 法二：对行二分查找

遍历行，找到target所在的行，然后在行中二分查找

#### 法二c++

```
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;
        int m = matrix.size(), n = matrix[0].size();      
        int i;
        for (i=0; i<m; i++) {
            if (matrix[i][0] <= target && matrix[i][n-1] >= target) {
                return bisearch(matrix[i], 0, n-1, target);
            }
        }
        return false;
    }
    bool bisearch(vector<int> &A, int low, int high, int x) {
        while(low<=high) {
            int mid = (low + high) >> 1;
            if (A[mid] == x) {
                return true;
            } else {
                if (x < A[mid]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
        }
        return false;
    }
};
```

### 法三：法二改——对列二分查找

注意要法二中是通过遍历来找到 target 可能在的行的。可以利用二分法代替遍历的过程。

#### 法三c++

```
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;
        int m = matrix.size(), n = matrix[0].size(); 
        vector<int> tmp;
        for(int i=0;i<m;i++)
            tmp.push_back(matrix[i][0]);
        int i = bisearch_row(tmp, 0, m-1, target);
        if (i==-1) {
            return false;
        } else {
            return bisearch_col(matrix[i], 0, n-1, target);
        } 
    }

    bool bisearch_col(vector<int> &A, int low, int high, int x) {
        while(low<=high) {
            int mid = (low + high) >> 1;
            if (A[mid] == x) {
                return true;
            } else {
                if (x < A[mid]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
        }
        return false;
    }

    int  bisearch_row(vector<int> &A, int low, int high, int x) {
        if (x < A[0]) return -1;
        while (low < high) {
            int mid = (low + high + 1) >> 1;
            if (A[mid] > x) {
                high = mid - 1;
            } else {
                low = mid;
            }
        }
        return low;
    }
};
```

### 法四：双指针

从右上角开始。向左或向下走。向左往小里调，向下往大里调，有点像双指针。

时间复杂度 $O(n+m)$ 因为最坏情况是 i从0到m-1，j从n-1到0；

#### 法四：双指针c++

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty())
            return false;
        int m = matrix.size(), n = matrix[0].size();
        int i = 0, j = n-1;
        while(i<m && j>=0) {
            if (matrix[i][j] == target) {
                return true;
            } else {
                if (matrix[i][j] < target) {
                    i++;
                } else {
                    j--;
                }
            } 
        }
        return false;
    }
};
```

### 解法五：分治

#### 解法五：实现

具体思路类似于 [ 1 ]，懒得写就直接看人家的就好了

#### 解法五：复杂度分析

这个可以用 master 定理来解决。递推式满足

$$
\begin{aligned}
T(nm) &= 3 T( \frac{n}{2} \frac{m}{2}) + O(1) \\
    &= 3 T(\frac{nm}{4}) + O(1)
\end{aligned}
$$

又 master 定理， 时间复杂度为 $O((nm)^{log_43})$。

这个复杂度应该是高估了。因为三个子问题，不是全部都需要解的。运气好的情况下第一个子问题返回 true 之后其他子问题就不需要计算了。


##### 解法五：实现：c++

```
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;
        return searchMatrix(0, matrix.size(), 0, matrix[0].size(), target, matrix);
        
    }
    bool searchMatrix(int x1, int x2, int y1, int y2, int target, const vector<vector<int>>& matrix)
    // [x1, x2) [y1, y2)
    {
        // printf("%d %d %d %d\n", x1, x2, y1, y2);
        if (x1 >= x2 || y1 >= y2 || target < matrix[x1][y1] || target > matrix[x2-1][y2-1]) return false;
        int x_mid = x1 + x2 >> 1;
        int y_mid = y1 + y2 >> 1;
        if (matrix[x_mid][y_mid]==target) return true;
        if (matrix[x_mid][y_mid] < target)
        {
            return searchMatrix(x_mid+1, x2, y1, y2, target, matrix) || 
                searchMatrix(x1, x_mid+1, y_mid+1, y2, target, matrix);
        }
        else
        {
            return searchMatrix(x1, x_mid, y1, y2, target, matrix) ||
                searchMatrix(x_mid, x2, y1, y_mid, target, matrix);
        }
        
    }
};
```

# References
1.  [(2条消息)二维数组中的查找(LeetCode: 74. Search a 2D Matrix)_杨领well的专栏-CSDN博客_杨辉矩阵查找](https://blog.csdn.net/yanglingwell/article/details/69943479)
