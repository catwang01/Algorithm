[toc]

# Nowcoder LRU Cache_牛客网

## 题目描述

[LRU Cache_牛客网](https://www.nowcoder.com/practice/3da4aeb1c76042f2bc70dbcb94513338?tpId=182&&tqId=34883&rp=1&ru=/activity/oj&qru=/ta/exam-all/question-ranking)

## 算法

### 解法1: map

#### 解法1: 实现

##### 解法1: c++

```cpp
#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

class LRU {
    private:
        struct Item {
            int val;
            int time;
            void display() {
                cout << "val = " << val << " time: " << time << endl;
            }
        };

        unordered_map<int, Item> hashtab;
        map<int, int> timetab;
        int size;
        int time;
    public:
        LRU(int n=0) {
            this->size = n;
            this->time=0;
        } 
        void put(int k, int v) {
            if (this->size==0) return;
            if (hashtab.find(k) != hashtab.end()) {
                hashtab[k].val = v;
            } else {
                if (hashtab.size() == this->size) {
                    int pop_key = timetab.begin()-> second;
                    timetab.erase(timetab.begin()-> first);
                    hashtab.erase(pop_key);
                }
                hashtab[k] = {v, this->time};
                timetab[this->time] = k;
                this->time++;
            }
        }
        int get(int k) {
            int ret;
            if (hashtab.find(k) == hashtab.end()) {
                ret = -1;
            } else {
                ret = hashtab[k].val;
                timetab.erase(hashtab[k].time);
                timetab[this->time] = k;
                hashtab[k].time = this->time;
                this->time++;
            }
            return ret;
        }
};

int main () {
    int n; cin >> n;
    LRU lru(n);
    char action;
    int x, y;
    while ((cin >> action)) {
        if (action=='p') {
            cin >> x >> y;
            lru.put(x, y);
        } else {
            cin >> x;
            cout << lru.get(x) << endl;
        }
    }
}
```

### 解法2: 双端队列 + hashtab

上面一种解法是通过 map 来保持顺序从而找到最近没有使用的项的。还可以利用队列来完成这个工作。

1. LRU 的替换策略有点类于队列的先进先出： 如果只考虑 put，当队列中元素的个数没有达到最大个数，则直接 push 到队列末尾。如果达到最大个数，pop 掉队列头部（因为插入是从队列末尾插入的，因此队首的元素是 Least Recently 的元素。），再从队尾插入新的元素，这实际上就是队列的先进先出功能。
因此，只需要一个队列就可以满足 put 功能的需求。

2. 再考虑 get。 get 要求如果 key 出现在队列中，就将队列中的元素 pop 出来，然后push到队尾。这个删除的操作如果使用 queue 来完成，用时为 $O(n)$，因为需要通过遍历来找到结点的位置，然后再 pop。
如果要在 $O(1)$ 时间内完成这个操作，则不能直接使用普通的队列。由于需要在 $O(1)$ 时间内完成查找操作，因此可以使用 hashtab 来实现，用一个 hashtab 来保存每个节点。同时，还需要将普通的队列修改为双端队列，因此删除操作涉及到了当前节点的上一个节点，只使用普通的队列无法简单地实现这一点。

#### 解法2: 实现

##### 解法2: c++

这里基本是手写的双端队列的一些操作。实际上可以使用 std::list 来代替。

```cpp
#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

class LRU {
    private:
        struct Node {
            int val;
            int key;
            Node *next, *prev;
            Node(int key=-1, int val=-1): val(val), key(key), next(nullptr), prev(nullptr) {}
        };

        unordered_map<int, Node*> hashtab;
        int size;
        Node *virtualHead, *virtualTail;

        void push_back(Node *node) {
            node->next = this->virtualTail;
            node->prev = this->virtualTail->prev;
            this->virtualTail->prev->next = node;
            this->virtualTail->prev = node;
        }

        void pop_front() {
            deleteNode(this->virtualHead->next);
        }

        void deleteNode(Node *node) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            node->prev = nullptr;
            node->next = nullptr;
        }
    
    public:
        LRU(int n=0) {
            this->size = n;
            this->virtualHead = new Node;
            this->virtualTail = new Node;
            this->virtualHead->next = this->virtualTail;
            this->virtualTail->prev = this->virtualHead;
        } 

        ~LRU() {
            delete this->virtualHead;
            delete this->virtualTail;
        }
    
        void put(int k, int v) {
            if (this->size==0) return ;
            if (hashtab.find(k)!=hashtab.end()) {
                hashtab[k]->val = v;
            } else {
                if (hashtab.size() == this->size) {
                    int pop_key = this->virtualHead->next->key;
                    pop_front();
                    delete hashtab[k]; hashtab.erase(pop_key);
                }
                hashtab[k] = new Node(k, v);
                push_back(hashtab[k]);
            }
        }

        int get(int k) {
            int ret;
            if (hashtab.find(k) == hashtab.end()) {
                ret = -1;
            } else {
                ret = hashtab[k]->val;
                deleteNode(hashtab[k]);
                push_back(hashtab[k]);
            }
            return ret;
        }
};

int main () {
    int n; cin >> n;
    LRU lru(n);
    char action;
    int x, y;
    while ((cin >> action)) {
        if (action=='p') {
            cin >> x >> y;
            lru.put(x, y);
        } else {
            cin >> x;
            cout << lru.get(x) << endl;
        }
    }
}
```

##### 解法2: c++2 - 使用 std::deque

只 ac 60%，不知道问题在哪里，之后再看吧。

![](https://gitee.com/EdwardElric_1683260718/picture_bed/raw/master/img/20200625184903.png)

```
#include <iostream>
#include <unordered_map>
#include <deque>

using namespace std;

int debug = 0;

class LRU {
    private:
        struct Item {
            int key, val;
            Item(int key=-1, int val=-1): key(key), val(val) {}
        };

        unordered_map<int, deque<Item>::iterator> hashtab;
        deque<Item> history;
        int size;
    
    public:
        LRU(int n=0) {
            this->size = n;
        } 
    
        void put(int k, int v) {
            if (this->size==0) return ;
            if (hashtab.find(k)!=hashtab.end()) {
                hashtab[k]->val = v;
            } else {
                if (hashtab.size() == this->size) {
                    int pop_key = history.front().key;
                    history.pop_front();
                    hashtab.erase(pop_key);
                }
                history.push_back({k, v});
                hashtab[k] = --history.end();
            }
        }

        int get(int k) {
            int ret;
            if (hashtab.find(k) == hashtab.end()) {
                ret = -1;
            } else {
                ret = hashtab[k]->val;
                history.erase(hashtab[k]);
                history.push_back({k, ret});
                hashtab[k] = --history.end();
            }
            return ret;
        }
};

int main () {
    int n; cin >> n;
    LRU lru(n);
    char action;
    int x, y;
    while ((cin >> action)) {
        if (action=='p') {
            cin >> x >> y;
            lru.put(x, y);
        } else {
            cin >> x;
            cout << lru.get(x) << endl;
        }
    }
}
```
