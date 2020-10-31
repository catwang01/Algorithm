[toc]

# Leetcode 169. 多数元素

## 问题描述

[169. 多数元素 - 力扣（LeetCode）](https://leetcode-cn.com/problems/majority-element/)

给定一个大小为 *n* 的数组，找到其中的多数元素。多数元素是指在数组中出现次数**大于** `⌊ n/2 ⌋` 的元素。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。

**示例 1:**

**输入:** \[3,2,3\]
**输出:** 3

**示例 2:**

**输入:** \[2,2,1,1,1,2,2\]
**输出:** 2

## 算法

### 解法一：hash

#### 解法一复杂度分析

时间复杂度： $O(n)$
空间复杂度： $O(n)$

#### 解法一实现

##### 解法一：c++ 

```
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> counter;
        for (int num: nums) {
            counter[num]++;
            if (counter[num] > n / 2) {
                return num;
            }
        }
        return 0;
    }
};
```

##### 解法一：scala

```
import scala.collection.mutable.Map
import util.control.Breaks._

object Solution {
    def majorityElement(nums: Array[Int]): Int = {
        var n = nums.length;
        var result = nums(0);
        var hashmap = Map.empty[Int, Int]
        nums foreach {
            x => {
                breakable {
                    if (hashmap.contains(x)) {
                        hashmap(x) += 1;
                        if (hashmap(x) > n /2 ) {
                            result = x;
                            break;
                        }
                } else {
                     hashmap(x) = 1;
                    } 
                }
            }
        }
        result;
    }
}
```

### 解法二：排序法

由于多数元素个数大于 n/2个，因此排序后下标为 n/2 的元素一定是多数元素

#### 解法二：实现

##### 解法二：c++

```
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[nums.size()/2];
    }
};
```

### 解法3: 快速选择

和解法二的思路相同，只不过是使用快速选择来做的。

注意：在 Leetcode 中，使用 python版本的快速选择貌似过不了。因为有一个案例会超时。

#### 解法3: 实现

##### 解法3： python

```
import random
class Solution:
    def majorityElement(self, nums: List[int]) -> int:
        return self._majorityElement(nums, 0, len(nums), len(nums) // 2 + 1)
        
    def _majorityElement(self, nums, low, high, k):
        if low == high: return -1
        # [low, high)
        # [low, i) 小于等于 pivot
        # [i, j) 大于 pivot
        # [j, high) 未排序 => j == high 停止 => j < high 循环
        pivot_index = random.randint(low, high-1)
        pivot = nums[pivot_index]
        nums[high-1], nums[pivot_index] = nums[pivot_index], nums[high-1]
        i = j = low
        while j < high:
            if nums[j] <= pivot:
                nums[i], nums[j] = nums[j], nums[i]
                i += 1
            j += 1

        # pivot 在 i-1 处
        if i == k:
            return pivot
        elif i < k:
            return self._majorityElement(nums, i, high, k)
        elif i > k:
            return self._majorityElement(nums, low, i - 1,  k)
```

