
[toc]

# Leetcode 面试题40. 最小的k个数

## 问题描述

[面试题40. 最小的k个数 - 力扣（LeetCode）](https://leetcode-cn.com/problems/zui-xiao-de-kge-shu-lcof/)

## 算法

### 解法1.1：小根堆

将所有的数依次放入大小为 n 的小根堆，然后 pop 出前 k 个数即可，

时间复杂度： $O(n+klogn)$ 其中建堆有 $O(n)$，pop出最顶端的有 $O(klogn)$
空间复杂度： $O(n)$ 堆里面需要将所有数都放进去。

#### 解法1.1：实现

##### 解法1.1：python

```
import heapq
class Solution:
    def getLeastNumbers(self, arr: List[int], k: int) -> List[int]:
        heapq.heapify(arr)
        return [heapq.heappop(arr) for i in range(k)] 
```

### 解法1.2：大根堆

使用大根堆可以达到 $O(k)$ 的空间复杂度。

当堆中的元素小于 k 个时，将其中添加元素。当堆中的元素为 k 个时，判断添加的元素 x 是否比堆顶小，如果是就删除堆顶之后添加 x。

时间复杂度： $O(n+klogn)$ 其中建堆有 $O(n)$，pop出最顶端的有 $O(klogn)$
空间复杂度： $O(k)$ 堆里面需要将所有数都放进去。

#### 解法1.2：实现

##### 解法1.2：java

```
class Solution {
    public int[] getLeastNumbers(int[] arr, int k) {
        if (k==0) return new int[0];
        int[] result = new int[k];
        PriorityQueue<Integer> heap = new PriorityQueue<>((o1,o2)->{return o2-o1;});
        for (int x: arr) {
            if (heap.size() < k) {
                heap.add(x);
            } else {
                if (x < heap.peek()) {
                    heap.poll();
                    heap.add(x);
                }
            }
        }
        for (int i=0; i<k; i++) result[i] = heap.poll();
        return result;
    }
}
```

### 解法2 :quickSelect（快慢双指针）

#### 解法2:实现1: 

##### 解法2:实现1: c++

i 是慢指针，cur 是快指针

循环不变量为：
1. 工作区间是 [low, high) 
2. [low, i) 小于 pivot 
3. [i, cur) 大于 pivot 
4. [cur, high-1) 未排序
5. high-1 的位置是 pivot

初始值为 i = 0, cur = 0

停止条件：cur == high - 1
循环条件： cur < high - 1

```
class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        if (k==0) {
            vector<int> ret;
            return ret;
        }
        quickSelect(0, arr.size(), k, arr);
        vector<int> ret(arr.begin(), arr.begin() + k);
        return ret;
    }

    void quickSelect(int low, int high, int k, vector<int>& arr) {
        if (low < high) { // low == high 时为空
            int i = 0, cur = 0;
            int pivot = arr[high-1];
            while (cur < high - 1) {
                if (arr[cur] <= pivot) {
                    swap(arr[cur], arr[i]);
                    i++;
                }
                cur++;
            }
            swap(arr[cur], arr[i]);
            if (i==k-1) {
                return ;
            } else {
                if (i < k-1) quickSelect(i+1, high, k, arr);
                else quickSelect(low, i, k, arr);
            }
        }
    }
};
```

##### 解法2.1:java

```
class Solution {
    public int[] getLeastNumbers(int[] arr, int k) {
        int[] result = new int[k];
        quickSelect(arr, 0, arr.length-1, k);
        for (int i=0; i<k; i++) result[i] = arr[i];
        return result;
    }
    
    public void quickSelect(int[] arr, int low, int high, int k) {
        if (low < high) {
            int mid = partition(arr, low, high);
            if (mid==k-1) {
                return;
            } else {
                if (mid>k-1) {
                    quickSelect(arr, low, mid-1, k);
                } else {
                    quickSelect(arr, mid+1, high, k);
                }
            }
        }

    }

    public int partition(int[] arr, int low, int high) {
        int i=low-1, j=low; // i是哨兵指针，j是工作指针
        int pivot = arr[high];
        while (j<=high) {
            if (arr[j] <= pivot) {
                i++;
                swap(arr, i, j);
            }
            j++;
        }
        return i;
    }

    public void swap(int[] arr, int i, int j) {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}
```

### 解法2.2：quickSelect（首尾双指针）

#### 解法2.2：实现

##### 解法2.2:java

```
class Solution {
    public int[] getLeastNumbers(int[] arr, int k) {
        int[] result = new int[k];
        quickSelect(arr, 0, arr.length-1, k);
        for (int i=0; i<k; i++) result[i] = arr[i];
        return result;
    }
    
    public void quickSelect(int[] arr, int low, int high, int k) {
        if (low < high) {
            int mid = partition(arr, low, high);
            if (mid==k-1) {
                return;
            } else {
                if (mid>k-1) {
                    quickSelect(arr, low, mid-1, k);
                } else {
                    quickSelect(arr, mid+1, high, k);
                }
            }
        }

    }

    public int partition(int[] arr, int low, int high) {
        int pivot = arr[high];
        int i=low, j=high;
        while (i<j) {
            while (i<j && arr[i]<=pivot) i++;
            // 此时 i 指向左侧第一个大于 pivot 的值；
            arr[j] = arr[i]; 
            while (i<j && arr[j]>pivot) j--;
            // 此时 j 指向右侧第一个小于 pivot 的值
            arr[i] = arr[j]; 
        }
        arr[i] = pivot;
        return i;
    }
}
```

### 解法3:直接排序

时间复杂度： $O(nlogn)$
空间复杂度： $O(n)$

#### 解法3:实现

##### 解法3:java

```
import java.util.Arrays;

class Solution {
    public int[] getLeastNumbers(int[] arr, int k) {
        Arrays.sort(arr);
        int[] result = new int[k];
        for (int i=0; i<k; i++) result[i] = arr[i];
        return result;
    }
}
```
