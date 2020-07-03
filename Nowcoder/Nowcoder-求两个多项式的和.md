[toc]

# Nowcoder 求两个多项式的和

## 题目描述

[求两个多项式的和_牛客网](https://www.nowcoder.com/practice/a9901ba9163549a590d1d1c245f14d2a?tpId=40&&tqId=21534&rp=1&ru=/activity/oj&qru=/ta/kaoyan/question-ranking)


## 算法

### 解法1: 使用 map 来表示多项式

因为 c++ 的 map 基于红黑树，是有序的，可以用来从低位到高位遍历。

map 的 key 表示次数，val 表示系数。每次计算的时候都对应位数相加即可。

#### 解法1: c++

```cpp
#include <iostream>
#include <map>
 
using namespace std;
 
int main() {
    map<int, int> d1;
    map<int, int> ret;
    int n, val, key;
    cin >> n;
     
    while (n--) {
        cin >> val >> key;
        d1[key] = val;
    }

    cin >> n;
    while (n--) {
        cin >> val >> key;
        // 如果在 d1 中出现
        if (d1.find(key) != d1.end()) {
            val += d1[key];
            d1.erase(key); // 注意要从 d1 中删除
        }
        if (val) ret[key] = val; // 如果 val 非零才添加到结果中。
    }
    // d1 中那些没有在 d2 出现的项加入到结果中
    for (map<int, int>::iterator it=d1.begin(); it!=d1.end(); it++) {
        ret[it->first] = it->second;
    }

    for (auto it=ret.rbegin(); it!=ret.rend();  it++) {
        cout << it->second << " " << it->first << " ";
    }
}
```

### 解法2: 使用栈来表示多项式
