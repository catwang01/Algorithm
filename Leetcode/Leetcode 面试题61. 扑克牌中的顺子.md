[toc]

## Leetcode 面试题61. 扑克牌中的顺子

## 问题描述

[面试题61. 扑克牌中的顺子 - 力扣（LeetCode）](https://leetcode-cn.com/problems/bu-ke-pai-zhong-de-shun-zi-lcof/)

## 算法

### 解法1: 使用set

排序。目的是计算0的个数和找到最数组的非0最小值。

#### 解法1:实现

##### 解法1: c++

```
class Solution {
public:
    bool isStraight(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int i=0;
        while (nums[i]==0) i++;
        unordered_set<int> squence;
        for (int j=0; j<5; j++) {
            squence.insert(nums[i]+j);
        }
        for (int k=i; k<5; k++) {
            if (squence.find(nums[k])==squence.end()) {
                return false;
            }
            squence.erase(nums[k]);
        }
        return squence.size() == i;
    }
};
```
