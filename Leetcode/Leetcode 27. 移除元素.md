
[toc]

# Leetcode 27. 移除元素

## 问题描述

[27. 移除元素 - 力扣（LeetCode）](https://leetcode-cn.com/problems/remove-element/)

## 算法

### 解法一：双指针--前后双指针

类似于快排中的排序方法，利用双指针 i, j；
i表示不等于 val 的数字的范围的右端点，即 `[0,i)` 是不等于 val 的数字的范围；
j是工作指针，当每次j增加1，检查 nums[j] 是否不等于 val，如果是，则 nums[i] = nums[j]，并且 i 增加 1；

时间复杂度：$O(n)$，两个指针合起来走的步数为 $O(2n)=O(n)$
空间复杂度： $O(1)$

#### 解法1: python

```
class Solution:
    def removeElement(self, nums: List[int], val: int) -> int:
        if nums == []: return 0
        i = j = 0 # [0, i) 表示当前不为0的数字所在的范围
        while j < len(nums):
            if nums[j] != val:
                nums[i] = nums[j]
                i += 1
            j += 1
        return i
```

#### 解法1: c++

循环不变式：

[0, slow) 保存非 val 开始时没有元素，因此 slow 初始化为0
[slow, fast) 保存 val 开始时没有元素，因此 fast 初始化为0
[fast, n) 没有处理 --> 因此停止条件是 [fast, n) 为空集，即 fast = n。因此循环条件是 `while ( fast < n)`

```
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        // 特判
        int n = nums.size();
        if (n==0) return 0;
        
        int slow = 0, fast = 0;
        while (fast < n) {
            if (nums[fast] != val) {
                slow++;
                swap(nums[fast], nums[slow-1]);
            }
            fast++;
        }
        return slow;
    }
};
```

### 解法二： 双指针 -- 左右双指针

#### 解法二：python

```
class Solution:
    def removeElement(self, nums: List[int], val: int) -> int:
        n = len(nums)
        if n==0: return 0
        j = n # [j,n) 放的是val
        i = 0 # [0, i) 放的是非val
        while i < j:
            if nums[i] == val:
                j -= 1 # val的空间加1
                nums[i], nums[j] = nums[j], nums[i]
            else:
                i += 1 # 非val的空间加1
        return i
```

#### 解法2: c++

```
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        if (n==0) return 0;
        int left = 0, right = n;
        while (left < right) {
            while (left < right && nums[left] != val) {
                left++;
            }
            if (left < right) {
                right--;
                swap(nums[left], nums[right]);
            }
        }
        return left;
    }
};
```
