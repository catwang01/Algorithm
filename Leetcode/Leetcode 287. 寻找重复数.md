
[toc]

# Leetcode 287. 寻找重复数

## 问题描述

[287. 寻找重复数 - 力扣（LeetCode）](https://leetcode-cn.com/problems/find-the-duplicate-number/)

给定一个包含 n + 1 个整数的数组 nums，其数字都在 1 到 n 之间（包括 1 和 n），可知至少存在一个重复的整数。假设只有一个重复的整数，找出这个重复的数。

**示例 1:**
**输入:** [1,3,4,2,2]
**输出:** 2

**示例 2:**
**输入:** [3,1,3,4,2]
**输出:** 3

说明：解法需要满足下面的限制：
1.  **不能**更改原数组（假设数组是只读的）。
2.  只能使用额外的 $O(1)$ 的空间。
3.  时间复杂度小于 $O(n^2)$ 。
4.  数组中只有一个重复的数字，但它可能不止重复出现一次。

## 算法

### 解法一：排序（非原地）

不满足限制1，因为更改了原数组

```cpp
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        for (int i=1; i<n; i++)
        {
            if (nums[i-1]==nums[i])
            {
                return nums[i];
            }
        }  
        return 0; 
    }
};
```

### 解法二：hash（非常数空间）

时间复杂度： $O(n)$
空间复杂度： $O(n)$

不满足条件，因为空间复杂度为  $O(n)$

#### 法二python

```
class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        d = set()
        for x in nums:
            if x not in d:
                d.add(x)
            else:
                return x
```


### 解法三：利用桶原理（非原地）

#### 解法3: 实现1（修改了数组，不满足要求）

注意到，我们有 n+1 个位置，下标范围为 `[0, n]`

而我们只有 `[1, n]` 的数字会出现。假设我们可以修改原数组，我们做这样一个操作：将 nums[i] 放在下标为 nums[i] 的位置上，即让 `nums[i] == nums[nums[i]]`。可以预计，那些只出现一次的数字，都可以正确放在自己对应的位置上。而那些不满足 `nums[i] == nums[nums[i]]` 的数字一定是重复的数字。

那么有一个问题，下标为 0 的位置对应那个数字？一定是重复出现的数字。

因此我们只需要对原数组做上述操作，然后返回 nums[0] 位置上的数字即可。

时间复杂度： $O(n)$ 每交换一次有一个数字回到了正确的位置，最多交换n次；
空间复杂度： $O(1)$

##### 解法3： 实现1: python

```
class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        def swap(i, j):
            nums[i],nums[j] = nums[j], nums[i]
        while nums[0] != nums[nums[0]]:
            swap(0, nums[0])
        return nums[0]
```

### 解法4：（桶原理改进）快慢指针（满足要求）


实际上，我们不需要真的去对原数组修改。而只需要用一个变量来表示当前 nums[0] 这个位置上的数字就可以了。

假设原数组为 `[1,3,4,2,2]` 我们做下面的模拟

```
1. 我们取一个变量 p = nums[0]，并初始化一个 list，命名为 processed，表示处理过的结果
2. 我们检查 p，它的值为1，对应的正确位置是下标为 1 的位置，我们再看 nums[1] 的值，这个数为3，我们令 p = nums[1] = 3，并将 1 添加到 processed 中。

此时 p = 3, processed = [1]

上面这一步虽然没有修改原数组，但是实际上是在模拟对原数组的修改：我们将 nums[0] 和 nums[1] 交换了，此时可以看作有一个虚拟的交换后的数组，[3, 1, 4, 2, 2]。

我们实际上是在用 p 和 processed 两个东西在模拟这个交换后的数组。其中 processed 中的元素表示这个位置上的元素已经处于正确的位置，如果 p 的值出现在 processed 中，说明 p 位置上的数重复出现，因此应该返回 p。

3. 我们取出 nums[0]，它的值为3。对应的正确位置是下标为 3 的位置，我们再看 nums[3] 的值，这个数为2，我们令 p = nums[3] = 2

此时 p = 2, processed = [1, 3]，对应的虚拟数组为 [2, 1, 4, 3, 2]

4. 我们检查 p，它的值为2。对应的正确位置是下标为 2 的位置，我们再看 nums[2] 的值，这个数为4，我们令 p = nums[3] = 4
此时 p = 4, processed = [1,3,2]，对应的虚拟数组为 [4, 1, 2, 3, 2]

5. 我们检查 p，它的值为4。对应的正确位置是下标为 4 的位置，我们再看 nums[4] 的值，这个数为2，我们发现 2 这个数字实际上在 processed 数组中，因此我们直接返回 p。
```

上面我们借助了 p 数组。这个数组中的数字可以构成一个有环链表，实际上我们是在这个链表中找环的入口节点。因此这个问题转化为了 [142. 环形链表 II - 力扣（LeetCode）](https://leetcode-cn.com/problems/linked-list-cycle-ii/)

#### 解法4：实现

##### 解法4：实现: python

```
class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        def getNext(i): # 用这个来模拟链表的next操作
            return nums[i]

        slow = fast = nums[0]
        while True:
            fast = getNext(getNext(fast))
            slow = getNext(slow)
            if slow == fast:
                break
        newSlow = nums[0]
        while slow != newSlow:
            slow = getNext(slow)
            newSlow = getNext(newSlow)
        return slow
```


### 解法5：二分法

#### 解法5：实现1:

$\forall  1 \leq k \leq n$, 令 $count(k) = \#\{i:A[i] \leq k\}$

1. 若 count > k，说明重复的数一定在 [1, k] 中
2. 若 count <= k, 说明重复的数一定在 [k+1, n] 中

问题实际上变成了求 $\argmin_i count(i) > i$，可以用二分法来解决。

##### 解法四：实现1：python

```py
class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        n = len(nums) - 1
        return self.bisearch(nums, 1, n)

    def bisearch(self, A, low, high):
        while low < high:
            mid = low + high >> 1
            count = 0
            for x in A:
                if x <= mid:
                    count += 1
            if count > mid:
                high = mid
            else:
                low = mid+1
        return low
```

#### 解法四：实现2：左闭右开区间

##### 解法四：实现2：python

```
class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        n = len(nums) - 1

        def count(i):
            ret = 0
            for x in nums: 
                if x <= i: ret += 1
            return ret

        def condition(i):
            return count(i) > i
            
        # min(count(i) != i)
        low, high = 1, n + 1
        while high - low > 2:
            mid = low + high >> 1
            if condition(mid):
                high = mid + 1
            else:
                low = mid + 1
        if condition(low): return low
        return high - 1
```
