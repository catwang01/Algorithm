[toc]

# Leetcode 88. 合并两个有序数组

## 问题描述

[88. 合并两个有序数组 - 力扣（LeetCode）](https://leetcode-cn.com/problems/merge-sorted-array/)

[面试题 10.01. 合并排序的数组 - 力扣（LeetCode）](https://leetcode-cn.com/problems/sorted-merge-lcci/)

给定两个有序整数数组 nums1 和 nums2，将 nums2 合并到 nums1 中，使得 num1 成为一个有序数组。

说明:

初始化 nums1 和 nums2 的元素数量分别为 m 和 n。
你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。
示例:

输入:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3

输出: [1,2,2,3,5,6]

这个题的链表版本为 [Leetcode 21. 合并两个有序链表](https://app.yinxiang.com/shard/s54/nl/22483756/9a948143-4a1b-425e-96f1-c71c95f89f3a/)

## 算法


### 解法一：使用辅助外数组

使用一个大小为 n+m 的辅助数组 tmp，将合并后的结果保存在tmp中，再将 tmp 中的结果复制到 num1 中；

时间复杂度： $O(n+m)$
空间复杂度： $O(n+m)$

#### 解法一c++

```
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> tmp(n+m);
        int i=0, j=0, k=0;
        while(i<m && j<n) {
            if (nums1[i] < nums2[j]){
                tmp[k] = nums1[i];
                i++;
            }    
            else {
                tmp[k] = nums2[j];
                j++;
            }
            k++;
        }
        if (i == m) {
            while(j<n) {
                tmp[k] = nums2[j];  
                k++, j++;
            }
        } else {
            while(i<m) {
                tmp[k] = nums1[i];
                k++, i++;
            }
        }
        for(k=0; k<n+m; k++){
            nums1[k] = tmp[k];
        }
    }
};
```

- 一个小优化：由于最终合并后的结果需要保存在 nums1 中，因此可以使用一个大小为 m 的辅助数组 nums1_copy，用来保存 nums1 的值，并将合并后的结果直到保存在 nums1 中，这样使用的额外空间为 $O(m)$

### 解法二：双指针从后往前

时间复杂度： $O(n+m)$
空间复杂度： $O(1)$ 因为只使用到了几个指针

![e0161f074d077aa6e09d86809e2c041e.jpeg](evernotecid://8E200321-31A9-427B-BECA-CC44235980BC/appyinxiangcom/22483756/ENResource/p10714)

#### 解法二python递归


```
class Solution:
    def merge(self, nums1: List[int], m: int, nums2: List[int], n: int) -> None:
        """
        Do not return anything, modify nums1 in-place instead.
        """
        self._merge(nums1, nums2, m-1, n-1, m+n-1)

    def _merge(self, nums1, nums2, p1, p2, cur):
        # p1, p2 分别指向 nums1, nums2 尾部第一个没有参与排序的元素
        # cur 指向尾部第一个空闲的空间。nums1[p1+1:cur+1] 代表空闲空间，可以直接对其赋值
        if p1 == -1: # nums1 消耗完，将剩下的 nums2 复制到 nums1 中
            nums1[:cur+1] = nums2[:p2+1]
        else:
            if p2 != -1: # nums1 和 nums2都没有消耗完
                if nums1[p1] > nums2[p2]:
                    nums1[cur] = nums1[p1]
                    p1 -= 1
                else:
                    nums1[cur] = nums2[p2]
                    p2 -= 1
                cur -= 1
                self._merge(nums1, nums2, p1, p2, cur)
```

#### 解法二：实现2 迭代

##### 解法2: 实现2 python

```
class Solution:
    def merge(self, nums1: List[int], m: int, nums2: List[int], n: int) -> None:
        """
        Do not return anything, modify nums1 in-place instead.
        """
        p1, p2, cur = m-1, n-1, m+n-1
        while p1 != -1 and p2 != -1:
            if nums1[p1] > nums2[p2]:
                nums1[cur] = nums1[p1]
                p1 -= 1
            else:
                nums1[cur] = nums2[p2]
                p2 -= 1
            cur -= 1
        if p1 == -1:
            nums1[:cur+1] = nums2[:p2+1]
```

##### 解法2: 实现2: c++

```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1, j = n - 1, k = n + m - 1;
        // 循环不变式：在进入 while 前，有下面的关系
        // [0, i] 未排序 
        // [0, j] 未排序
        // [k, n+m-1] 已排序
        while ( i>=0 && j>=0)
        {
            if (nums1[i] < nums2[j])
            {
                nums1[k] = nums2[j];
                k--, j--;
            } else {
                nums1[k] = nums1[i];
                k--, i--;
            }
        }
        // i < 0 or j < 0
        if (i < 0) 
        {
            while ( j >= 0)
            {
                nums1[k] = nums2[j];
                k--, j--;
            }
        }
    }
};
```
