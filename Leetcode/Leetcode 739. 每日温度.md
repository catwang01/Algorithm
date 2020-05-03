[toc]

# Leetcode 739. 每日温度

## 问题描述

[739. 每日温度 - 力扣（LeetCode）](https://leetcode-cn.com/problems/daily-temperatures/)

## 算法

### 解法1: 单调栈

#### 解法1:实现

##### 解法1: c++

```
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) { 
        int n = T.size();
        vector<int> ret(n, 0);
        stack<int> s;
        for (int i=0; i<n; i++) {
            while (!s.empty() && T[s.top()] < T[i]) {
                ret[s.top()] = i - s.top();
                s.pop();
            }
            s.push(i);
        }
        return ret; }
};
```
