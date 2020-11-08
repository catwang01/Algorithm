
[toc]

# Leetcode 162. 寻找峰值

## 问题描述

[162. 寻找峰值 - 力扣（LeetCode）](https://leetcode-cn.com/problems/find-peak-element/)

峰值元素是指其值大于左右相邻值的元素。

给定一个输入数组 `nums`，其中 `nums[i] ≠ nums[i+1]`，找到峰值元素并返回其索引。

数组可能包含多个峰值，在这种情况下，返回任何一个峰值所在位置即可。

你可以假设 `nums[-1] = nums[n] = -∞`。

**示例 1:**

**输入:** **nums** = `[1,2,3,1]`
**输出:** 2
**解释:** 3 是峰值元素，你的函数应该返回其索引 2。

**示例 2:**

**输入:** **nums** = `[`1,2,1,3,5,6,4\]
**输出:** 1 或 5
**解释:** 你的函数可以返回索引 1，其峰值元素为 2；
     或者返回索引 5， 其峰值元素为 6。

**说明:**

你的解法应该是 *O*(*logN*)时间复杂度的。

## 算法

### 解法一：bruteforce

时间复杂度： $O(n)$
空间复杂度： $O(1)$

#### 解法一c++

```
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        
        int n = nums.size();
        if (n==1) {
            return 0;
        }

        for(int i=0; i<nums.size(); i++) {
            if (i==0) {
                if (nums[0] > nums[1]) {
                    return i;
                }
            }  else if (i==nums.size()-1) {
                if (nums[i] > nums[i-1]) {
                    return i;
                }
            }  else if (nums[i-1] < nums[i] && nums[i] > nums[i+1]) {
                return i;
            }
        }
        return 0;
    }
};
```

### 解法二：二分法

时间复杂度为 $O(logn)$，提示我们使用二分法。一个比较直观的想法是对数组的长度二分。

假设我们取中点 mid。然后我们看看 mid 和左右两点的关系无非下列四种

```
1.  up up
2. up down
3. down up
4. down down
```

其中，如果是第一种情况，`nums[i-1] < nums[i] < nums[i+1]`，而 nums[n] = 负无穷，说明在 [i+1, n) 之间必定会有峰值。

其他类似。

这个需要证明

![644ee8e1cb7acb5fecfacaaa28109b1f.png](en-resource://database/8687:1)

#### 解法二c++ 

```
class Solution {
public:
    // nums[i] < nums[j] 时返回 true 否则返回 false
    // 可以处理下标越界时的比较问题
    bool safe_less(int i, int j, vector<int>& nums) {
        int n = nums.size();
        if (i<0) return true;
        if (j>=n) return false;
        return nums[i] < nums[j];
    }

    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        int low = 0, high = n-1;
        while (low <= high) {
            int mid = low + (high - low >> 1);
            if (safe_less(mid, mid+1, nums)) {
                low = mid + 1;
            } else {
                if (safe_less(mid-1, mid, nums)) {
                    return mid;
                } else {
                    high = mid - 1;
                }
            }
        }  
        return -1;
    }
};
```

##### 解法2:实现：python

```
class Solution:
    def findPeakElement(self, nums: List[int]) -> int:

        def safe_less(i, j): # return the result of nums[i] < nums[j]
            if i < 0: return True
            if j >= len(nums): return False
            return nums[i] < nums[j]

        low, high = 0, len(nums)
        while high - low > 2:
            mid = (low + high) // 2
            if safe_less(mid, mid+1):
                low = mid + 1
            elif safe_less(mid-1, mid):
                return mid
            else:
                high = mid
        if safe_less(high-2, high-1) and not safe_less(high-1, high):
            return high - 1
        return low
```