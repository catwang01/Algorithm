
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

### 解法3: 回溯法： 交换法

参考了 [ 4 ]

这个解法的好处是，不需要 $O(n)$ 的空间来存储中间结果。坏处是得到的结果不是按照顺序的。

对于数组 nums[i:]，利用 for 循环遍历所有的数，将其交换到 nums[i] 的位置做头，然后递归 nums[i+1:]

需要注意的一点是，当 nums[i+1:] 递归调用结束后，需要在此 swap 以恢复现场。

#### 解法3: 实现

##### 解法3: python

```
class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        def swap(i, j):
            nums[i], nums[j] = nums[j], nums[i]

        ret = []
        def helper(i): # [0, i) 处理过
            if i == len(nums):
                ret.append(nums[:])
                return 
            for j in range(i, len(nums)):
                swap(j, i)
                helper(i+1)
                swap(j, i)
        helper(0)
        return ret
```

# References

1. [【HOT 100】46.全排列 Python3 回溯 step by step理解回溯 要画图！ - 全排列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/permutations/solution/hot-100-46quan-pai-lie-python3-hui-su-step-by-step/)

2. [回溯算法详解 - 全排列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/permutations/solution/hui-su-suan-fa-xiang-jie-by-labuladong-2/)

3. [从全排列问题开始理解“回溯搜索”算法（深度优先遍历 + 状态重置 + 剪枝） - 全排列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/permutations/solution/hui-su-suan-fa-python-dai-ma-java-dai-ma-by-liweiw/)

4. [【46】C++ 回溯法/交换法/stl 简洁易懂的全排列 - 全排列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/permutations/solution/c-hui-su-fa-jiao-huan-fa-stl-jian-ji-yi-dong-by-sm/)