[toc]

# Leetcode 剑指 Offer 21. 调整数组顺序使奇数位于偶数前面

## 问题描述

[剑指 Offer 21. 调整数组顺序使奇数位于偶数前面 - 力扣（LeetCode）](https://leetcode-cn.com/problems/diao-zheng-shu-zu-shun-xu-shi-qi-shu-wei-yu-ou-shu-qian-mian-lcof/)

## 算法

### 解法 1：双指针（类似于快排）

1. 两个指针，i 是工作指针，用来遍历所有元素；j 是哨兵，用来标记边界。j之前的元素（包括j）都小于等于 pivot



#### 解法 1:实现

##### 解法 1：java

```
class Solution {
    public int[] exchange(int[] nums) {
        int i=0, j=-1;
        while (i < nums.length) {
            if ( nums[i] % 2 == 1) {
                j++;
                if (i != j) { // 这里不判断也可，反正 nums[i]==nums[j],swap也没事
                    swap(nums, i, j);
                }
            }
            i++;
        }
        return nums;
    }
    public void swap(int[] nums, int i, int j) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
}
```

### 解法2：双指针（首尾指针）

1. 用left来表示奇数边界，right来表示偶数边界。 
2. left 向右扩张，直到left指向的元素不是奇数
3. right 向左扩张，直到right指向的元素不是偶数；
4. left和right交换。继续2、3步，直到left>=right时结束循环。

#### 解法2:实现

##### 解法2: java

```
class Solution {
    public int[] exchange(int[] nums) {
        int left = 0, right = nums.length-1;
        while (left < right) {
            // 左边界移动
            while (left < right && nums[left] % 2 == 1 ) {
                left++;
            }
            // 此时left为左侧第一个不是奇数的元素
            // 右边界移动
            while (right > left && nums[right] % 2 != 1) {
                right--;
            }
            // 此时right为右侧第一个不是偶数的元素
            swap(nums, left, right);
        }
        return nums;
    }
    public void swap(int[] nums, int i, int j) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
}
```

##### 解法2: c++

```
class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int n = nums.size();
        if (n<=1) return nums;
        
        // [0, i) 表示奇数 (j, n-1] 表示偶数
        // 初始化为 i==0 j==n-1 表示此时奇数和偶数均为空
        // [i, j] 为空表示循环停止 ==> i > j 时表示循环停止
        // i <= j 表示循环进行
        int i=0, j = n-1;
        while ( i <= j )
        {
            if (nums[i] % 2 == 0)
            {
                swap(nums[i], nums[j]);
                j--;
            }
            else 
            {
                i++;
            }
        }
        return nums;
    }
};
```

# References

1. [【题解】：首位双指针，快慢双指针 - 调整数组顺序使奇数位于偶数前面 - 力扣（LeetCode）](https://leetcode-cn.com/problems/diao-zheng-shu-zu-shun-xu-shi-qi-shu-wei-yu-ou-shu-qian-mian-lcof/solution/ti-jie-shou-wei-shuang-zhi-zhen-kuai-man-shuang-zh/)
