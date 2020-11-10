[toc]

# Leetcode 31. 下一个排列

## 问题描述

[31. 下一个排列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/next-permutation/)

## 算法

### 解法1:

这里需要注意最大最小是怎么来的。当一个序列逆序时，这个序列表示的数字最大，当一个序列顺序时，这个序列表示度数字最小。

需要三个步骤：

获得全排列下一个数的 3 个步骤。

1. 从后向前查看逆序区域，找到逆序区域的前一位，也就是数字置换的边界。
2. 让逆序区域的前一位和逆序区域中大于它的最小的数字交换位置。
3. 把原来的逆序区域转为顺序状态 。

时间复杂度：$O(n)$，find 函数的部分可以写成二分查找，但是总的时间复杂度不变。

##### 解法1: 实现： c++

```
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        if (n<=1) return ;
        int j = n-2;
        while (j >= 0 && nums[j] >= nums[j+1])
        {
            j--;
        }
        if (j < 0) { 
            reverse(nums, 0, n); 
            return ;
        } // 说明 nums 整个是逆序的，返回最小值
        // 此时 nums[j] > nums[j+1] [..., j, j+1, ..., n-1] [j+1, n) 这一段是逆序
        int idx = find(nums, j+1, n, nums[j]); // 找到比 [j+1, n) 中比 nums[j] 大的最小值
                                                // 把这个值放在 nums[j] 的位置上
        swap(nums[idx], nums[j]);
        reverse(nums, j+1, n);
        
    }

    int find(vector<int>& nums, int start, int end, int x) // nums[i, end)
    {
        for (int i=start; i<end; i++)
        {
            if (nums[i] <= x) return i-1;
        }
        return end - 1;
    }

    void reverse(vector<int>& nums, int start, int end)  // nums[i, end)
    {
        int i = start, j = end-1;
        // [i,j] 没有交换过的
        while (i < j)
        {
            swap(nums[i++], nums[j--]);
        }
    }
};
```

##### 解法1: 实现：python

```
class Solution:
    def nextPermutation(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        j = n - 1
        while j >= 1 and nums[j-1] >= nums[j]:
            j -= 1
        # j < 1 or nums[j-1] < nums[j]
        if j == 0: # j < 1
            self.reverse(nums, 0, n)
            return
        print(j)
        # nums[j-1] < nums[j] 
        # [j, n) 逆序
        i = self.bisearch(nums, j, n, nums[j-1])
        print(i)
        nums[i], nums[j-1] = nums[j-1], nums[i]
        self.reverse(nums, j, n)

    def bisearch(self, A, low, high, x):
        # A reverese order 
        #  A[i] > x and A[i+1] <= x 
        while high - low > 2:
            mid = (low + high) // 2
            if A[mid] > x:
                low = mid
            else:
                high = mid
        if A[high-1] > x:
            return high - 1
        return low

    def reverse(self, A, low, high):
        i, j = low, high-1
        while i < j:
            A[i], A[j] = A[j], A[i]
            i += 1
            j -= 1
```
