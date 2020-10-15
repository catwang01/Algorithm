[toc]

# Leetcode 977. 有序数组的平方

## 问题描述

## 算法

### 解法1：双指针

普通解法就不说了。这里注意可以双指针。时间复杂度是 $O(n)$

#### 

```
class Solution {
public:
    vector<int> sortedSquares(vector<int>& A) {
        vector<int> ret(A.size());
        // [left, right] 没有遍历的 (left>right)
        int left = 0, right = A.size() - 1;
        int i = A.size(); // [i, n) 表示已经填充的值
        int left_square, right_square;
        while (left <= right)
        {
            left_square = A[left] * A[left];
            right_square = A[right] * A[right];
            if (left_square > right_square) 
            {
                ret[--i] = left_square;
                left++;
            }
            else
            {
                ret[--i] = right_square;
                right--;
            }
        }
        return ret;
    }
};
```