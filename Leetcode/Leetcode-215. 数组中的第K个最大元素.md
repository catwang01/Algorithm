
[toc]

# Leetcode 215. 数组中的第K个最大元素

## 问题描述

[215. 数组中的第K个最大元素 - 力扣（LeetCode）](https://leetcode-cn.com/problems/kth-largest-element-in-an-array/submissions/)

## 算法

### 解法一：暴力排序

排序后选第k大的数据，时间复杂度 $O(nlogn)$

### 解法二：堆

时间复杂度：$NO(logk)$
空间复杂度： $O(k)$

建立一个k个元素的大根堆，每次往堆中插入一个元素，最后弹出堆中最后的一个元素。

#### 解法二c++


```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> q;
        for(int num:nums) {
            q.push(num);
            if (q.size() > k) {
                q.pop();
            }
        }
        return q.top();
    }   
};
```



### 解法三：快速选择

快速选择算法的思路类似于快速排序。是利用分治的思想，先找到一个pivot元素，找到其位置j，有下面三种情况：

1. j==k，返回 pivot
2. j<k 说明第k大元素在 A[j+1:len-1] 中
3. j>k 说明第k大元素在 A[0:j-1] 中

注意在使用时添加一步随机化，避免极端测试用例。

平均时间复杂度 $O(n)$，最坏时间复杂度 $O(n^2)$

#### 解法三c++

```
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        return quickSelet(nums, 0, n-1, k-1);
    }

    int quickSelet(vector<int>& A, int low, int high, int k) {
        if (low==high) {
            return A[low];
        }
        int j = low - 1;
        // 随机选择pivot，防止退化到 O(n^2)复杂度的情况
        int pivot_index = (rand()%(high-low)) + low;
        int pivot = A[pivot_index];
        swap(A[pivot_index], A[high]);
        for (int i=low;i<=high;i++) {
            if (A[i] >= pivot) {
                j++;
                if (i!=j) {
                    swap(A[i], A[j]);
                }
            }
        }
        if (j==k) {
            return A[j];
        } else {
            if (j<k) {
                return quickSelet(A, j+1, high, k);
            } else {
                return quickSelet(A, low, j-1, k);
            }
        }
    }
};
```

#### 解法3: c++ 另一种循环不变式
```
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        return quickSelect(nums, 0, nums.size(), k);
    }

   
    int quickSelect(vector<int>& nums, int low, int high, int k) {
        // 随机化
        int pivot_index = int(rand() % (high - low) + low);
        int pivot = nums[pivot_index];
        swap(nums[pivot_index], nums[high-1]);

        // [low, i) 大于等于 pivot
        // [i, j) 小于 pivot
        // [j, high) 没有处理
        int i = low, j = low;
        while (j < high) {
            if (nums[j] >= pivot) {
                swap(nums[i], nums[j]);
                i++;
            }
            j++;
        }
        if (i==k) return pivot;
        else {
            if ( i < k) {
                return quickSelect(nums, i, high, k);
            } else {
                return quickSelect(nums, low, i-1, k);
            }
        }
        return -1;
    }
};
```

#### 解法三python

```
import random
class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        return self.quickSelect(nums, 0, len(nums)-1, k-1)
    
    def quickSelect(self, A, low, high, k):
        if low < high:
            pivot_idx = random.randint(low, high)
            pivot = A[pivot_idx]
            A[pivot_idx], A[high] = A[high], A[pivot_idx]
            i = low - 1
            for j in range(low, high+1):
                if A[j] >= pivot:
                    i += 1
                    if A[i] != A[j]:
                        A[i], A[j] = A[j], A[i]
            if i==k:
                return A[k]
            elif i>k:
                return self.quickSelect(A, low, i-1, k)
            else:
                return self.quickSelect(A, i+1, high, k)
        else: # low = high = k
            return A[k]
```

#### 解法三python

```
import random
class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        return self.quickSelect(nums, 0, len(nums)-1, k-1)
    
    def quickSelect(self, A, low, high, k):
        if low < high:
            pivot_idx = random.randint(low, high)
            pivot = A[pivot_idx]
            A[pivot_idx], A[high] = A[high], A[pivot_idx]
            i = low - 1
            for j in range(low, high+1):
                if A[j] >= pivot:
                    i += 1
                    if A[i] != A[j]:
                        A[i], A[j] = A[j], A[i]
            if i==k:
                return A[k]
            elif i>k:
                return self.quickSelect(A, low, i-1, k)
            else:
                return self.quickSelect(A, i+1, high, k)
        else: # low = high = k
            return A[k]
```
