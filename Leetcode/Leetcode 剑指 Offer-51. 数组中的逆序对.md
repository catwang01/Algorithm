[toc]

# Leetcode 面试题51. 数组中的逆序对

## 问题描述

[面试题51. 数组中的逆序对 - 力扣（LeetCode）](https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/)

## 算法

### 解法1 mergesort

#### 解法1：实现1

注意有个坑，当 `A[i] > A[j]` 时，记数方式为 `ret += mid - i +1;`

因为 当 A[i] > A[j] 时， j需要自增1。因此需要将 j 构成的所有可能的逆序数都加到 ret 上。 由于 A[i] > A[j]，因此 A[i+1], ..., A[mid] 都大于 A[j]，因此 j 可以和 A[i],...,A[mid] 构成逆序对。因此  ret += mid - i + 1;

##### 解法1：实现1:C++

```
class Solution {
    private:
    vector<int> tmp;
public:
    int reversePairs(vector<int>& nums) {
        if (nums.size()<=1) return 0;
        tmp.resize(nums.size());
        return help(0, nums.size()-1, nums);
    }
    
    int help(int low, int high, vector<int>& nums) {
        int ret = 0;
        if (low < high) {
            int mid = low + (high - low ) / 2;
            ret += help(low, mid, nums); // 左边内部的逆序数
            ret += help(mid+1, high, nums); // 右边内部的逆序数
            ret += merge(low, mid, high, nums); // 左边对右边的逆序数
        }
        return ret;
    }

    int merge(int low, int mid, int high, vector<int>& A) {
        int ret = 0;
        int i = low, j = mid+1, k = low;
        while (i<=mid && j <= high) {
            if (A[i] <= A[j]) {
                tmp[k++] = A[i++];
            } else {
                // 有一个坑
                ret += mid - i +1;
                tmp[k++] = A[j++];
            }
        }
        while (i<=mid) {
            tmp[k++] = A[i++];
        }
        while (j<=high) {
            tmp[k++] = A[j++];
        }
        for (k=low; k<=high; k++) 
            A[k] = tmp[k];
        return ret;
    }
};
```

#### 解法1:实现2:左闭右开区间

##### 解法1:实现2:c++

```
class Solution {
public:
    vector<int> tmp;
    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        tmp.resize(n);
        return mergeSort(0, n, nums);
    }
    // [low, high)
    int mergeSort(int low, int high, vector<int>& A)
    {
        // cout << low << " " << high << endl;
        if (high - low <= 1) return 0;
        int ret = 0;
        int mid = low + (high - low) / 2;
        ret += mergeSort(low, mid, A);
        ret += mergeSort(mid, high, A);
        // [low, i) 处理过的 [mid, j) 处理过的 [low, k) 处理过的
        int i = low, j = mid, k = low;
        while ( i < mid && j < high)
        {
            if (A[i] <= A[j])
            {
                tmp[k++] = A[i++];
            }
            else 
            {
                ret += mid - i;
                tmp[k++] = A[j++];
            }
        }
        if (i == mid)
        {
            while (j < high)
            {
                tmp[k++] = A[j++];
            }
        }
        else 
        {
            while ( i < mid)
            {
                tmp[k++] = A[i++];
            }
        }
        for (int k=low; k < high; k++)
        {
            A[k] = tmp[k];
        }
        return ret;
    }
};
```