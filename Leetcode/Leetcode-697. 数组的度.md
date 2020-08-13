[toc]

# Leetcode 697. 数组的度

## 问题描述
 
 [697. 数组的度 - 力扣（LeetCode）](https://leetcode-cn.com/problems/degree-of-an-array/)

## 算法

### 解法1: hashmap

实际上，之需要求数组的众数出现的第一个位置 i 和最后一个位置 j，那么 j - i + 1 即为所求结果。

可以使用一个 `unordered_map<int, vector<int>>` 来保存每个数对应的所有下标。

这个会有不同的实现方式。如可以只保存第一个位置和最后一个位置，此时还需要保存元素出现的次数，可以考虑使用一个 struct 来实现。

考虑到 nums 中元素的取值范围是一个在0到49,999范围内的整数。可以用一个长度为 50000 的数数组代替hashmap。

#### 解法1: 实现1

##### 解法1: 实现1: c++

```
class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        unordered_map<int, vector<int>> counter;
        
        int degree = 0;
        for (int i=0; i<nums.size(); i++)
        {
            counter[nums[i]].push_back(i);
            degree = max(degree, int(counter[nums[i]].size()));
        }
        int ret = nums.size();
        for (const auto& p: counter)
        {
            int len = p.second.size();
            if (len == degree) { 
                ret = min(ret, p.second[len-1] - p.second[0] + 1);
            }
        }
        return ret;
    }
};
```

#### 解法1: 实现2

##### 解法1: 实现2: c++

```
class Solution {
public:
    struct Item {
        int freq, first, last;
        Item(int freq_=0, int first_=0, int last_=0): freq(freq_), first(first_), last(last_) {}
    };
    int findShortestSubArray(vector<int>& nums) {
        Item* map[50000];
        for (Item* &item: map) item=nullptr;
        int degree = 0;
        for (int i=0; i<nums.size(); i++)
        {
            if (map[nums[i]]==nullptr)
            {
                map[nums[i]] = new Item(1, i, i);
            }
            else {
                map[nums[i]]->freq++;
                map[nums[i]]->last = i;
            }
            degree = max(degree, map[nums[i]]->freq);
        }
        int ret = nums.size();
        for (Item* item: map)
        {
            if (item!=nullptr)
            {
                if (item->freq == degree)
                ret = min(ret, item->last - item->first + 1);
                delete item;
            }
        }
        return ret;
    }
};
```

