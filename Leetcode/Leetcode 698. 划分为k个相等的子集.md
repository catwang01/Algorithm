[toc]

# Leetcode 698. 划分为k个相等的子集

## 问题描述

[698. 划分为k个相等的子集 - 力扣（LeetCode）](https://leetcode-cn.com/problems/partition-to-k-equal-sum-subsets/)

## 算法

### 解法1: 回溯

#### 解法1: 实现

注意是如何进行剪枝的。当前如果选择了 nums[j]，下次从 nums[j+1] 开始选择。

##### 解法1: 实现： c++

```
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int s = 0;
        for_each(nums.begin(), nums.end(), [&s](int x) {s+=x;});
        if (s % k != 0) return false;
        int target = s / k;
        vector<int> seen(nums.size(), 0);
        return backtrack(0, 0, k, seen, nums, target);
    }

    // 这个 i 用于剪枝
    bool backtrack(int i, int cur, int k, vector<int>& seen, const vector<int>& nums, int target)
    {
        if (k==1) return true; // k==1 时返回，而不是 k==0 时返回，因为剩下的数字放在一起和一定等于 target
        bool flag;
        for (int j=i; j<nums.size(); j++)
        {
            if (seen[j]==0 && cur + nums[j] <= target)
            {
                seen[j] = 1;
                if (cur + nums[j]==target)
                    flag = backtrack(0, 0, k - 1, seen, nums, target);
                else
                    // [0, j] 之间的结果不需要尝试了，因为之前选择的时候以及选择过了
                    flag = backtrack(j+1, cur + nums[j], k, seen, nums, target);
                if (flag) return true;
                seen[j] = 0;
            }
        }
        return false;
    }
};
```

#### 解法1：实现2

第二种实现是先建立 4 个桶，然后拿着一个数往每个桶里都试着放一次。

这种方法需要进行从大到小排序，先放大的，后放小的。因为大的可以限制分支个数。比如希望让所有集合中的元素都是5，如果先放一个5到第一个集合中，那么第一个集合就不能再放其他元素了，因此只有一个分支。而如果先放一个1到第一个集合中，那么第一个集合中还需要放其他的值。也就是说此时有多个分支。

由于这个问题比较特殊，只需要碰到第一个 true 的分支就可以返回，因此我们希望使用较少的分支来碰到第一个 true 的分支（感觉这里没有说清楚）。

##### 解法1:实现2: c++

```
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int s = 0;
        for_each(nums.begin(), nums.end(), [&s](int x) {s+=x;});
        if (s % k != 0) return false;
        int each_size = s / k;
        sort(nums.begin(), nums.end(), greater<int>());
        vector<int> sum(k, 0);
        return bfs(0, sum, nums, each_size);
    }

    bool bfs(int i, vector<int>& sum, const vector<int>& nums, int each_size)
    {
        if (i==nums.size()) return true;
        for (int& s: sum)
        {
            if (s + nums[i] <= each_size)
            {
                s += nums[i]; // 选择
                if (bfs(i+1, sum, nums, each_size)) return true;
                s -= nums[i];   // 还原状态
            }  
        }
        return false;
    }
};
```