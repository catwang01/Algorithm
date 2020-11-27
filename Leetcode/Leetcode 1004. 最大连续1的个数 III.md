[toc]

# Leetcode 1004. 最大连续1的个数 III

## 问题描述

[1004. 最大连续1的个数 III - 力扣（LeetCode）](https://leetcode-cn.com/problems/max-consecutive-ones-iii/)

## 算法

### 解法1：滑动窗口

##### 解法1: 实现：c++

```
class Solution {
public:
    int longestOnes(vector<int>& A, int K) {
        deque<int> window;
        int n = A.size();
        int left = 0, right = 0;
        int ret = 0;
        auto check = [&]() { return window.size() <= K;};
        while (right < n)
        {
            if (!A[right]) window.push_back(right);
            while (!check())
            {
                if (left == window.front())
                    window.pop_front();
                left ++;
            }
            ret = max(ret, right - left + 1);
            right++;
        } 
        return ret;
    }
};
```