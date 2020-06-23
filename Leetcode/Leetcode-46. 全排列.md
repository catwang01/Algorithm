
[toc]

# Leetcode 46. 全排列

## 问题描述

[46. 全排列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/permutations/)

## 算法

### 解法一：递归

最简单的递归，中间产生了很多中间变量

#### 解法一：递归python

```
class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        n = len(nums)
        if n <= 1: return [nums]
        else:
            result = []
            for i in range(n):
                partialresult = self.permute(nums[:i] + nums[i+1:])
                for each in partialresult:
                    result.append([nums[i]] + each)
            return result
```

### 解法二：回溯

用一个 flags 标识位标记是否某个数字是否被选中

#### 回溯算法的框架

```
result = []
def backtrack(路径, 选择列表):
    if 满足结束条件:
        result.add(路径)
        return
    
    for 选择 in 选择列表:
        做选择
        backtrack(路径, 选择列表)
        撤销选择
```

#### 解法二：实现

##### 解法二：c++

画出递归树，便于编写程序

![递归树](https://gitee.com/EdwardElric_1683260718/picture_bed/raw/master/img/20200621152843.png)

```
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        int n = nums.size();
        vector<int> seen(n, 0);
        vector<vector<int>> ret;
        vector<int> curpath;
        dfs(n, curpath, nums, seen, ret);
        return ret;
    }
    
    void dfs(int n, vector<int>& curpath, vector<int>& nums, vector<int>& seen, vector<vector<int>>& ret) {
        if (n==0) {
            ret.push_back(curpath);
            return;
        }
        for (int i=0; i<seen.size(); i++) {
            if (!seen[i]) {
                seen[i] = 1;
                curpath.push_back(nums[i]);
                dfs(n-1, curpath, nums, seen, ret);
                // 恢复现场
                curpath.pop_back();
                seen[i] = 0;
            }
        }
    }
};
```

##### 解法二：python

python 可以在函数中定义函数，因此代码会简单一些

```
class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        n = len(nums)
        result = []
        seen = [0 for i in range(n)]
        
        def dfs(path):
            if len(path) == n:
                result.append(path)
                return 
            for i in range(n):
                if seen[i] != 1:
                    seen[i] = 1
                    dfs(path+[nums[i]])
                    seen[i] = 0
        dfs([])
        return result
```

# References

1. [【HOT 100】46.全排列 Python3 回溯 step by step理解回溯 要画图！ - 全排列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/permutations/solution/hot-100-46quan-pai-lie-python3-hui-su-step-by-step/)

2. [回溯算法详解 - 全排列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/permutations/solution/hui-su-suan-fa-xiang-jie-by-labuladong-2/)

3. [从全排列问题开始理解“回溯搜索”算法（深度优先遍历 + 状态重置 + 剪枝） - 全排列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/permutations/solution/hui-su-suan-fa-python-dai-ma-java-dai-ma-by-liweiw/)
