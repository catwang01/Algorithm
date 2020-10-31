[toc]

# Leetcode 136 只出现一次的数字

## 算法

### 解法1: xor

用到了异或的这样几个性质

1. x ^ x= 0
2. x ^ 0 = x
3. x ^ y = y ^ x (交换性)

因此，可以将所有的数字依次异或，根据 3 交换性，可以将相同的数字放在一起，结果为0。最后只剩下只出现一次的数字。下面给出一个示例

数据: 2 2 3 4 4

则可做如下运算：

2 ^ 2 ^ 3 ^ 4 ^ 4 = (2 ^ 2) ^ (4 ^ 4) ^ 3  = 0 ^ 0 ^ 3 = 3

#### 解法1: 实现

##### 解法1: c++

```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ret = 0; // 因为 0 ^ x = x，因此可以初始化为 0 
        for(int x: nums) {
            ret ^= x;
        }
        return ret;
    }
};
```

# References
1. [136. 只出现一次的数字 - 力扣（LeetCode）](https://leetcode-cn.com/problems/single-number/)