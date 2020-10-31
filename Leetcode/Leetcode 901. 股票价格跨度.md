[toc]

# Leetcode 901. 股票价格跨度

## 问题描述

[901. 股票价格跨度 - 力扣（LeetCode）](https://leetcode-cn.com/problems/online-stock-span/)

## 算法

### 解法1: 单调栈

#### 解法1: 实现

##### 解法1: c++

```cpp
class StockSpanner {
    stack<int> mono_stack;
    vector<int> prices;
    int next_idx;
    
public:
    StockSpanner() 
    {
        next_idx = 0;
        mono_stack.push(-1);
    }

    int next(int price) 
    {
        prices.push_back(price); 
        while (mono_stack.top() != -1 && prices[mono_stack.top()] <= price) 
        {
            mono_stack.pop();
        }
        int ret = next_idx - mono_stack.top();
        mono_stack.push(next_idx);
        next_idx++;
        return ret;
    }
};
```