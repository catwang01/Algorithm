[toc]

# Nowcoder 质数因子

## 问题描述

[质数因子_牛客网](https://www.nowcoder.com/practice/196534628ca6490ebce2e336b47b3607?tpId=37&&tqId=21229&rp=1&ru=/activity/oj&qru=/ta/huawei/question-ranking)

## 算法

### 解法1

```
#include<iostream>
using namespace std;
int main()
{
    long long x;
    cin >> x;
    int i = 2;
    while (x != 1)
    {
        if (x % i) {
            i++;
        }
        else
        {
           x /= i;
            cout << i << " ";
        }
    }
    return 0;
}
```
