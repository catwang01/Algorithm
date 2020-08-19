[toc]

# Leetcode 1. 两数之和

## 问题描述

leetcode [两数之和 - 两数之和 - 力扣（LeetCode）](https://leetcode-cn.com/problems/two-sum/solution/liang-shu-zhi-he-by-leetcode-2/)

给定一个整数数组 `nums` 和一个目标值 `target`，请你在该数组中找出和为目标值的那两个整数，并返回他们的数组下标。

你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。

示例:

给定 nums = [2, 7, 11, 15], target = 9

因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]


本题还可以先排序后再查找，可以看输入有序数组的版本 [两数之和 II - 输入有序数组(C) - 两数之和 II - 输入有序数组 - 力扣（LeetCode）](https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted/solution/liang-shu-zhi-he-ii-shu-ru-you-xu-shu-zu-c-by-zed-/)

## 算法

### 解法一：bruteforce

暴力遍历，时间复杂度 $O(n^2)$，空间复杂度 $O(1)$

### 解法二：两次hash表

用两次遍历：

1. 第一次建立hashtab，key是元素的值，value是元素在数组中的索引（因为要返回索引）

2. 第二次扫描hashtab，对于元素 nums[i]，在hashtab中搜索 `target-nums[i]`，如果找到，则返回 `[i, hashtab[target-nums[i]]]`
注意，在这一步中，如果找到了则必然有 `i < hashtab[target-nums[i]]`，因为如果 `i > hashtab[target-nums[i]]`，说明 `target-nums[i]` 的下标小于 i，说明在 `nums[i] `之前就已经查找过了。

时间复杂度：一次建表，一次查表 $O(n)$
空间复杂度： $O(n)$

#### 解法二c++

```
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result(2);
        map<int, int> hashtab;
        // 建立hash表
        for (int i=0; i<nums.size(); i++) hashtab[nums[i]] = i;
        // 查找hashtab
        int complement;
        for (int i=0; i<nums.size(); i++) {
            complement = target - nums[i];
            if (hashtab.find(complement)!=hashtab.end()) {
                if (i!=hashtab[complement]) {
                    result[0] = i ;
                    result[1] = hashtab[complement];
                     return result;
                } 
            }
        }
        return result;
    }
};
```

### 解法二改进：一次hash表

注意到，在插入的时候就已经可以查找了，因此可以将建表和查找的步骤放在一起。

每当来一个新的元素 nums[i] 时，先查找当前的 `hashtab` 中有没有 `target-nums[i]` ，如果有，直接返回 `[hashtab[target-nums[i]], i]`，如果没有，则将 nums[i] 插入到 hashtab 中

时间复杂度： $O(n)$
空间复杂度： $O(n)$

#### 解法二一次hash表python

```
class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        hashtab = {}
        for i in range(len(nums)):
            if target - nums[i] in hashtab:
                return [hashtab[target - nums[i]], i]
            else:
                hashtab[nums[i]] = i
        return [-1, -1]
```

#### 解法二一次hash表c++

```
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashtab;
        vector<int> ret(2);
        for (int i=0; i<nums.size(); i++) {
            if (hashtab.find(target-nums[i]) == hashtab.end()) {
                hashtab[nums[i]] = i;
            } else {
                ret[0] = hashtab[target-nums[i]];
                ret[1] = i;
                break;
            }
        }
        return ret;
    }
};
```

### 解法3: 排序 + 双指针

需要注意的点：
1. 对index排序，而不是对 nums 本身排序
 2. 要防止 left==right 情况的出现。实际上，如果可以保证nums 中一定有两个数之和为 target 时，不可能出现 left==right 的情况。因为在 left == right 之前就返回了。但是，如果不能保证nums 中 一定有两个数之和为 target 时，还是应该防止 left ==right 情况的出现。

#### 解法3: 实现

##### 解法3: c++

```
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        if (nums.size()<=1) return {-1, -1};

        vector<int> index(nums.size());
        for(int i=0; i<nums.size(); i++) index[i] = i;
        sort(begin(index), end(index), [&](int i, int j) {return nums[i] < nums[j];});
        // [0, i) 左侧排除的结果
        // (j, n-1] 右侧排除的结果
        // [i, j] 可能的结果
        // i == j=> 循环结束
        // i < j 循环进行
        int i = 0, j = nums.size()-1;
        int s;
        while (i < j) 
        {
            s = nums[index[i]] + nums[index[j]];
            if (s == target)
            {
                return {index[i], index[j]};
            } else {
                if (s > target) j--;
                else i++;
            }
        }
        
        return {-1, -1};
    }
};
```

##### 解法3: python

```
class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        index = list(range(len(nums)))
        index.sort(key=lambda idx: nums[idx])
        left, right = 0, len(nums) - 1
        # [0, left) 左侧排除的结果
        # (right, high-1] 右侧排除的结果
        # [left, right] 可能的结果集合
        # 当可能当结果集合中只有一个数时停止，因为不能出现重复使用一个数的情况，即停止条件 left == right 
        while left < right:
            s = nums[index[left]] + nums[index[right]]
            if s == target:
                if index[left] > index[right]:
                    return [index[right], index[left]]
                else:
                    return [index[left], index[right]]
            elif s > target:
                right -= 1
            else:
                left += 1
        return [-1, -1]
```

