[toc]

# Leetcode 面试题45. 把数组排成最小的数

## 问题描述

[面试题45. 把数组排成最小的数 - 力扣（LeetCode）](https://leetcode-cn.com/problems/ba-shu-zu-pai-cheng-zui-xiao-de-shu-lcof/)

## 算法

### 解法1: 自定义排序规则

#### 解法1:实现

##### 解法1: c++

```
class Solution {
public:
    // 注意这个前面要加 static
    static bool cmp(int x, int y) {
        string sx = to_string(x), sy = to_string(y);
        return sx + sy < sy + sx;
    }

    string minNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), cmp);
        string ret = "";
        for (auto &s: nums) {
            ret += to_string(s);
        }
        return ret;
    }
};
```

##### 解法2: python

```
```



