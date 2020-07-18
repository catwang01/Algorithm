[toc]

# Leetcode 75. 颜色分类

## 问题描述

[75. 颜色分类 - 力扣（LeetCode）](https://leetcode-cn.com/problems/sort-colors/)

## 算法

### 解法1: 双指针

#### 解法1:实现

##### 解法1: c++

```
class Solution {
public:
    void print(vector<int>& nums) {
        for(int x:nums) cout << x << " ";
        cout << endl;
    }

    void sortColors(vector<int>& nums) {
        if (nums.size() <= 1) return;
        int n = nums.size();
        int red = -1, blue = n, curIdx = 0;
        while (curIdx < blue) {
            switch(nums[curIdx]) {
                case 0:
                    red++;
                    if (red==curIdx) curIdx++;
                    else swap(nums[red], nums[curIdx]);
                    break;
                case 1:
                    curIdx++;
                    break;
                case 2:
                    blue--;
                    swap(nums[blue], nums[curIdx]);
                    break;
            }
        }
    }
};
```

### 解法2: 双指针：使用循环不变量的思想来解

参考了 [1]，感觉很有帮助

#### 解法2:实现

设计如下的循环不变量

```
[0, zero) 其中的位置放 0 
[zeor, i) 其中的位置放 i，i是工作指针
[two, n) 其中的位置放2
```

1. 初始值
因此，需要设置初始值使用这三个区间为空。
易知，`zero=0, i=0, two=n`  

2. 停止条件
当三个区间不重不漏得覆盖所有数据时停止。即 `i = two` 

3. 循环条件
由停止条件得到循环条件为 `i < two` 

##### 解法2: 

```
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        if (n<=1) return;
        int zero = 0, two = n, i = 0;
        while (i < two) {
            switch(nums[i]) {
                case 0:
                    swap(nums[zero], nums[i]);
                    zero++;
                    i++;
                    break;
                case 1:
                    i++;
                    break;
                case 2:
                    two--;
                    swap(nums[i], nums[two]);
                    break;
            }
        }  
    }
};
```

##### 解法2：python

```
class Solution:
    def sortColors(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        if  n <= 1: return
        # [0, i) ==> 0
        # [i, k) ==> 1
        # (j, n-1] ==> 2
        # [k, j] 未排序的元素
        # k > j 时循环停止
        # k <= j 时循环条件
        i, j, k = 0, n-1, 0
        while k <= j:
            while k <= j and nums[k]==2:
                nums[k], nums[j] = nums[j], nums[k]
                j -= 1
            # nums[k]==0 or nums[k]==1
            if nums[k] == 0:
                nums[k], nums[i] = nums[i], nums[k]
                i += 1
                k += 1
            else:
                k += 1
```

# References
1. [快速排序 partition 过程（重点在设计循环不变量） - 颜色分类 - 力扣（LeetCode）](https://leetcode-cn.com/problems/sort-colors/solution/kuai-su-pai-xu-partition-guo-cheng-she-ji-xun-huan/)

