
[toc]

# Nowcoder 中位数

## 问题描述

[中位数_牛客网](https://www.nowcoder.com/practice/2364ff2463984f09904170cf6f67f69a?tpId=40&&tqId=21367&rp=1&ru=/activity/oj&qru=/ta/kaoyan/question-ranking)

## 算法

### 解法1: 使用大根堆

#### 解法1:实现

##### 解法1: c++


```
#include <iostream>
#include <queue>

using namespace std;

const int debug = 0;

int main( ) {
    int N, x;
    priority_queue<int> heap;
    while (cin >> N) {
        if (N==0) break;
        int mid = 0;
        bool isodd = N & 1;
        int size = N / 2  + 1;
        if (debug) cout << "isodd: " << isodd << " N: " << N <<  " size: " << size << endl;
        while (!heap.empty()) heap.pop();
        while (N--) {
            cin >> x;
            heap.push(x);
            if ((int)heap.size() > size) {
                heap.pop();
            }
        }
        if (isodd) {
            cout << heap.top() << endl;
        } else {
            mid += heap.top(); 
            if (debug) cout << "top: " << heap.top() << endl;
            heap.pop();
            mid += heap.top();
            if (debug) cout << "top: " << heap.top() << endl;
            cout << mid / 2 << endl;
        }
    }
    return 0;
}
```
