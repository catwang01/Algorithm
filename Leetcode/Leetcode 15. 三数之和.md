[toc]

# Leetcode 15. 三数之和

## 问题描述

[15. 三数之和 - 力扣（LeetCode）](https://leetcode-cn.com/problems/3sum/)

给定一个包含 n 个整数的数组 `nums`，判断 `nums` 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？找出所有满足条件且不重复的三元组。
注意：答案中不可以包含重复的三元组。
示例：
给定数组 nums = [-1, 0, 1, 2, -1, -4]，
满足要求的三元组集合为：

```
[
  [-1, 0, 1],
  [-1, -1, 2]
]
```

## 算法

### 解法一：双指针

##### 解法1: 实现：python

```
class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        nums.sort()
        i = 0
        n = len(nums)
        ret = []

        def next_bigger(i):
            while i + 1 < len(nums) and nums[i] == nums[i+1]:
                i += 1
            i += 1
            return i
        
        def next_smaller(j):
            while j - 1 >= 0 and nums[j-1] == nums[j]:
                j -= 1
            j -= 1
            return j

        while i < n:
            j, k = i + 1, n - 1
            while j < k:
                s = nums[i] + nums[j] + nums[k]
                if s == 0:
                    ret.append([nums[i], nums[j], nums[k]])
                    j = next_bigger(j)
                elif s < 0:
                    j = next_bigger(j)
                elif s > 0:
                    k = next_smaller(k)
            i = next_bigger(i)
        return ret
```


##### 解法1: 实现：c++

```
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ret;
        int n = nums.size();
        if (n < 3) return ret;
        sort(nums.begin(), nums.end());
        int i = 0, j, k;
        while ( i <= n - 3)
        {
            j = i + 1, k = n - 1;
            while (j < k)
            {
                int s = nums[i] + nums[j] + nums[k] ;
                if (s > 0) k = get_next(nums, k, true);
                else if (s < 0)
                {
                    j = get_next(nums, j, false);
                }
                else 
                {
                    ret.push_back({nums[i], nums[j], nums[k]});
                    j = get_next(nums, j, false);
                }
                if (j==n || k==n) break;
            }
            i = get_next(nums, i, false);
        }
        return ret;
    }

    int get_next(vector<int>& nums, int i, bool reverse)
    {
        if (reverse)
        {
            for (int j=i-1; j>=0; j--)
            {
                if (nums[j] < nums[i]) return j;
            }
        }
        else
        {
            for (int j=i+1; j < nums.size(); j++)
            {
                if (nums[j] > nums[i]) return j;
            }

        }
        return nums.size();
    }
};
```