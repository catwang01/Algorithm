[toc]

# Leetcode 912. 排序数组

这个题目就是单纯的排序算法。可以用这个来验证自己的手写的排序算法到底有没有bug。

[912. 排序数组 - 力扣（LeetCode）](https://leetcode-cn.com/problems/sort-an-array/)

## 算法

### 解法1. 快排

#### 解法1：实现1

##### 解法1:c++

```
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        int n = nums.size();
        int low = 0, high = n-1;
        quickSort(nums, 0, n-1);
        return nums;
    }
    void quickSort(vector<int>& A, int low, int high) {
        if (low < high) {
            int v = A[high];
            int j, i = low - 1;
            for (j=low; j<=high; j++) {
                if (A[j] <= v) {
                    i++;
                    if (i!=j) {
                        swap(A[i], A[j]);
                    }
                }
            }
            quickSort(A, low, i-1);
            quickSort(A, i+1, high);
        }
    }
};
```

##### 解法1:java

```
import java.util.Arrays;
class Solution {
    public List<Integer> sortArray(int[] nums) {
        quickSort(nums, 0, nums.length-1);
        List<Integer> result = new ArrayList<Integer>();
        for (int i=0; i<nums.length; i++) {
            result.add(nums[i]);
        }
        return result;
    }

    public void quickSort(int[] nums, int low, int high) {
        if (low < high) {
            int pivot = nums[high];
            int i=low, j=low-1;
            while (i<=high) {
                if (nums[i] <= pivot) {
                    j++;
                    swap(nums, i, j);
                }
                i ++;
            }
            quickSort(nums, low, j-1);
            quickSort(nums, j+1, high);       
        }
    }

    public void swap(int[] nums, int i, int j) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
}
```

##### 解法1:python

```
class Solution:
    def sortArray(self, nums: List[int]) -> List[int]:
        self.quickSort(nums, 0, len(nums)-1)
        return nums

    def quickSort(self, A, low, high):
        if low < high:
            v = A[high]
            i = low - 1
            for j in range(low, high+1):
                if A[j] <= v:
                    i += 1
                    if i!=j:
                        A[i], A[j] = A[j], A[i]
            self.quickSort(A, low, i-1)
            self.quickSort(A, i+1, high)
```

#### 解法1: 实现2: 换一种循环不变量

定义循环不变量为

[low, left) 中表示
[left, i) 中表示
[i, high-1) 中的数据没有排序
high-1 为 pivot

1. 初始值
开始时，所有数据没有排序，因此 left = 0, i = 0;

2. 停止条件
[i, high-1) 中没有数据时停止，即 i == high - 1 时停止

3. 循环条件
i < high - 1

##### 解法1: 实现2: c++

```
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        quickSort(0, nums.size(), nums);
        return nums;
    }
    
    // 注意这里实现是左闭右开区间的情况
    void quickSort(int low, int high, vector<int>& nums) {
        if (low < high) {
            int left = low, i = low;
            int pivot = nums[high-1];
            while (i < high-1) {
                if (nums[i] <= pivot) {
                    swap(nums[left], nums[i]);
                    left++;
                }
                i++;
            }
            swap(nums[left], nums[high-1]);
            quickSort(low, left, nums);
            quickSort(left+1, high, nums);
        }
    }
};
```

### 2. 归并

#### 归并实现

##### 归并：c++

```
class Solution {
    vector<int> tmp; // 这个tmp是merge的时候用的，定义成全局的，这样就不会每次创建一个tmp
public:
    vector<int> sortArray(vector<int>& nums) {
        int n = nums.size();
        tmp.resize(n);
        MergeSort(nums, 0, n-1);
        return nums;
    }
    void MergeSort(vector<int>& A, int low, int high) {
        if (low < high) {
            int mid = (low + high) >> 1;
            MergeSort(A, low, mid);
            MergeSort(A, mid+1, high);
            Merge(A, low, mid, high);
        }         
    }
    void Merge(vector<int>& A, int low, int mid, int high) {
        int i=low, j=mid+1, k=low;
        while(i<=mid && j<=high) {
            if (A[i] < A[j]) {
                tmp[k++] = A[i++];
            } else {
                tmp[k++] = A[j++];
            }
        }
        if (i > mid) {
            while(j<=high) {
                tmp[k++] = A[j++];
            }
        }  else {
             while(i<=mid) {
                tmp[k++] = A[i++];
            }
        }
        for (k=low; k<=high; k++) {
            A[k] = tmp[k];
        }
    }
};
```


##### 归并：java

```
class Solution {
    int[] tmp;

    public int[] sortArray(int[] nums) {
        tmp = new int[nums.length];
        mergeSort(nums, 0, nums.length-1);
        return nums;
    }

    public void mergeSort(int[] A, int low, int high) {
        if (low < high) {
            int mid = low + high >> 1;
            mergeSort(A, low, mid);
            mergeSort(A, mid+1, high);
            int i=low, j = mid+1, k=low;
            while (i<=mid && j<=high) {
                if (A[i] < A[j]) {
                    tmp[k++] = A[i++];
                } else {
                    tmp[k++] = A[j++];
                }
            }
            if (i<=mid) {
                while (i<=mid) tmp[k++] = A[i++];
            } else {
                while (j<=high) tmp[k++] = A[j++];
            }
            for (i=low; i<=high; i++) A[i] = tmp[i];
        }
    }
}
```
