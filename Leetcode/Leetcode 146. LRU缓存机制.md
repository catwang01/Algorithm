
[toc]


# Leetcode 146. LRU缓存机制

## 问题描述

[146. LRU缓存机制 - 力扣（LeetCode）](https://leetcode-cn.com/problems/lru-cache/)

运用你所掌握的数据结构，设计和实现一个  [LRU (最近最少使用) 缓存机制](https://baike.baidu.com/item/LRU)。它应该支持以下操作： 获取数据 `get` 和 写入数据 `put` 。

获取数据 `get(key)` \- 如果关键字 (key) 存在于缓存中，则获取关键字的值（总是正数），否则返回 \-1。
写入数据 `put(key, value)` \- 如果关键字已经存在，则变更其数据值；如果关键字不存在，则插入该组「关键字/值」。当缓存容量达到上限时，它应该在写入新数据之前删除最久未使用的数据值，从而为新的数据值留出空间。

**进阶:**

你是否可以在 **O(1)** 时间复杂度内完成这两种操作？

**示例:**

LRUCache cache = new LRUCache( 2 /\* 缓存容量 \*/ );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // 返回  1
cache.put(3, 3);    // 该操作会使得关键字 2 作废
cache.get(2);       // 返回 \-1 (未找到)
cache.put(4, 4);    // 该操作会使得关键字 1 作废
cache.get(1);       // 返回 \-1 (未找到)
cache.get(3);       // 返回  3
cache.get(4);       // 返回  4

## 算法

### 解法1: hashtab + deque

自己手写的 deque。使用虚拟头尾节点来简化判断。

注意理解什么是 LRU。其实很简单，如果某个值被访问过，那么这个值的状态会被刷新，注意对这个值对读和写都会导致这个值对状态被刷新！

#### 解法1:实现

##### 解法1: python

```py
class ListNode:
    def __init__(self, key, val):
        self.next = None
        self.prev = None
        self.key = key
        self.val = val

class Deque:
    def __init__(self):
        self.virtualHead = ListNode(-1, -1)
        self.virtualTail = ListNode(-1, -1)
        self.virtualHead.next = self.virtualTail
        self.virtualTail.prev = self.virtualHead
    
    def push_back_node(self, node):
        node.next = self.virtualTail
        node.prev = self.virtualTail.prev
        node.prev.next = node
        node.next.prev = node
    
    def push_back(self, key, val):
        node = ListNode(key, val)
        self.push_back_node(node)

    def empty(self):
        return self.virtualHead.next == self.virtualTail
    
    def pop_front(self):
        if not self.empty():
            node = self.virtualHead.next
            self.delete(node)
            return node
        else:
            return None

    def delete(self, node):
        node.prev.next = node.next
        node.next.prev = node.prev
        node.next = node.prev = None   
    
    def tail(self):
        return None if self.empty() else self.virtualTail.prev
    
    def head(self):
        return None if self.empty() else self.virtualHead.next
         
class LRUCache:

    def __init__(self, capacity: int):
        self.history = {}
        self.deque = Deque()
        self.capacity = capacity

    def get(self, key: int) -> int:
        if key in self.history:
            ret = self.history[key].val
            self.deque.delete(self.history[key])
            self.deque.push_back_node(self.history[key])
        else:
            ret = -1
        return ret

    def put(self, key: int, val: int) -> None:
        if key in self.history:
            self.history[key].val = val
            self.deque.delete(self.history[key])
            self.deque.push_back_node(self.history[key])
        else:
            if len(self.history) == self.capacity:
                del self.history[self.deque.head().key]
                self.deque.pop_front()
            self.deque.push_back(key, val)
            self.history[key] = self.deque.tail()
```

##### 解法1: 实现： c++

```
class LRUCache {
public:
    struct Node
    {
        Node *next, *last;
        int key, val;
        Node(int key=0, int val=0): key(key), val(val), next(nullptr), last(nullptr) {}
    };
    unordered_map<int, Node*> hash;
    int capacity = 0;
    int size = 0;
    Node *head, *tail;

    LRUCache(int capacity): capacity(capacity) {
        head = new Node; tail = new Node;
        head->next = tail;
        tail->last = head;
    }

    ~LRUCache()
    {
        while (head==nullptr)
        {
            Node* delete_head = head;
            head = head->next;
            delete delete_head;
        }
    }

    int empty() { return size==0;}
    int full() { return size == capacity;}

    void remove(Node* node)
    {
        node->last->next = node->next;
        node->next->last = node->last;
        hash.erase(node->key);
        delete node;
        size--;
    }

    void pop()
    {
        if (empty()) return;
        remove(head->next);
    }

    void push(int key, int val)
    {
        if (full()) return;
        Node* node = new Node(key, val);
        tail->last->next = node; 
        node->last = tail->last;
        node->next = tail;
        tail->last = node;
        hash[key] = node;
        size++;
    }

    int get(int key) {
        if (hash.find(key)==hash.end()) return -1;
        int val = hash[key]->val;
        remove(hash[key]);
        push(key, val);
        return val;
    }

    void put(int key, int val) {
        if (hash.find(key)!=hash.end()) remove(hash[key]);
        else if (full()) pop();
        push(key, val);
    }
};
 ```