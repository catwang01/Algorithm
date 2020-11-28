[toc]

# Leetcode 56. 合并区间

## 问题描述

[56. 合并区间 - 力扣（LeetCode）](https://leetcode-cn.com/problems/merge-intervals/)

## 算法

### 解法1：滑动窗口

对区间进行sort。相当于对区间做出了限制：若 i < j，则 

```
1. intervals[i][0] <= intervals[i][1]
2. intervals[j][0] <= intervals[j][1]
3. intervals[i][0] <= intervals[j][0]
```

1. 如何判断重叠？
然后判断当前的区间的右端点是否比之后的区间的左端点小。如果是，就算重叠，如果不是，就不算重叠。

2. 如何合并？

之后的区间与当前区间合并时，只需要更新左端点（右端点不需要变，其最大性由排序保证）。

注意 `intervals[i][1]` 和 `intervals[j][1]` 的大小是不定的。因此需要注意，合并后的区间的右端点并不一定是排序后靠后的区间的右端点。如 [[1,100], [2,3]]


#### 解法1:实现

##### 解法1: c++

```
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const vector<int>& x, const vector<int>& y) {
            return x[0]==y[0] ? x[1] < y[1]: x[0] < y[0];
        });
        int i = 0, j, end;
        vector<vector<int>> ret;
        while (i < intervals.size()) {
            j = i; end = intervals[i][1];
            while (j < intervals.size()-1 && end >= intervals[j+1][0]) {
                end = max(end, intervals[j+1][1]);
                j++;
            }
            ret.push_back({intervals[i][0], end});
            i = j+1;
        }
        return ret;
    }
};
```

##### 解法1: python

```
class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        intervals.sort()
        left = 0
        ret = []
        rightmax = intervals[left][1]
        n = len(intervals)
        while left < n:
            right = left + 1
            while right < n and intervals[right][0] <= rightmax:
                rightmax = max(rightmax, intervals[right][1])
                right += 1
            ret.append([intervals[left][0], rightmax])
            left = right
            if left < n: rightmax = intervals[left][1]
        return ret
```