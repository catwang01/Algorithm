[toc]

# Leetcode 496. 下一个更大元素 I 

## 问题描述

[496. 下一个更大元素 I - 力扣（LeetCode）](https://leetcode-cn.com/problems/next-greater-element-i/)

## 算法

### 解法1: 单调栈 + hash

使用 hash 来快速得到索引值。使用单调栈来得到下一个更大的元素。出栈时进行记录。

#### 解法1:实现

##### 解法1: c++

```
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> val2idx;
        for(int i=0; i<nums1.size(); i++) {
            val2idx[nums1[i]] = i;
        }
        vector<int> ret(nums1.size(), -1);
        stack<int> s;
        for (int x: nums2) {
            while (!s.empty() && s.top() < x) {
                if (val2idx.find(s.top()) != val2idx.end()) {
                    ret[val2idx[s.top()]] = x;
                }
                s.pop();
            }
            s.push(x);
        }
        return ret;
    }
};
```

