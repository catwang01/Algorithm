[toc]

# Leetcode 面试题35. 复杂链表的复制 

## 问题描述

[面试题35. 复杂链表的复制 - 力扣（LeetCode）](https://leetcode-cn.com/problems/fu-za-lian-biao-de-fu-zhi-lcof/)

## 算法

### 解法1: 两次遍历 + 一个hashtab

#### 解法1:实现

##### 解法1: c++

参考[1]

```
class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> old2new;
        // 复制结点
        for (auto node=head; node!=NULL; node = node->next) {
            old2new[node] = new Node(node->val);
        }
        // 链接
        Node newnode(0), *virtualHead = &newnode;
        for (auto node=head; node!=NULL; node=node->next) {
            old2new[node]->random = old2new[node->random];
            old2new[node]->next = old2new[node->next];
        }
        return old2new[head];
    }
};
```

### 解法2: 一次遍历 + 两个hashtab

上面的用到了两次遍历。其中 next 指针的链接可以在第一次遍历中就进行；而 random 指针的链接不能在第一次遍历中进行，因为有可能出现 random 的结点还没有复制的情况。

为了解决这个问题，可以再用个 hash 表，来保存还没有创建的 random 结点的信息，由于可以有多个 random 结点指向同一个结点，因此这个 hash表的值是一个 vector<Node*>，把这个hashtab 起个名字，叫 waitingList 。

每个结点在复制之后，都到 waitingList 上去看看，有没有之前出现的结点想要引用它的，如果有，就将这些结点的 random 指针指向它。

#### 解法2:实现

##### 解法2: c++

```
class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, vector<Node*>> waitingList;
        unordered_map<Node*, Node*> old2new;

        Node node(0), *virtualHead = &node, *cur = virtualHead;

        while (head) {

            old2new[head] = new Node(head->val);

            // 复制random属性
            // 如果 random 属性指向的结点已经被复制，则指向它
            if (old2new.find(head->random) != old2new.end()) {
                old2new[head]->random = old2new[head->random];
            // 否则加入waitingList
            } else {
                waitingList[head->random].push_back(old2new[head]);
            }
            // 检查自己的waitingList，如果其中有结点，就填充他们的 random 值
            if (waitingList.find(head) != waitingList.end()) {
                for (auto waiter: waitingList[head]) {
                    waiter->random = old2new[head];
                }
            }

            // 更新上一个节点的next属性
            cur->next = old2new[head];
            cur = cur->next;
            head = head->next;
        }
        return virtualHead->next;
    }
};
```

### 解法3: 剑指offer解答

![picture goes here](https://gitee.com/EdwardElric_1683260718/picture_bed/raw/master/img/20200427220207.png)

![picture goes here](https://gitee.com/EdwardElric_1683260718/picture_bed/raw/master/img/20200427220634.png)

![picture goes here](https://gitee.com/EdwardElric_1683260718/picture_bed/raw/master/img/20200427220705.png)

#### 解法3:实现

##### 解法3: c++

```
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return NULL;
        head = copyDouble(head);

        // 链接random
        Node* cur = head;
        while (cur) {
            cur->next->random = cur->random ? cur->random->next: NULL;
            cur = cur->next->next;
        }

        Node *oldnode = head, *newnode = head->next;
        Node *ret = head->next;
        while (oldnode) {
            oldnode->next = newnode->next;
            oldnode = oldnode->next;
            newnode->next = oldnode ? oldnode->next: NULL;
            newnode = newnode->next;
        }
        return ret;
    }

    Node* copyDouble(Node* head) {
        Node *next, *node = head;
        while (node) {
            next = node->next;
            node->next = new Node(node->val);
            node->next->next = next;
            node = next;
        }
        return head;
    }
};
```

# References
1. [面试题35. 复杂链表的复制 - 力扣（LeetCode）](https://leetcode-cn.com/problems/fu-za-lian-biao-de-fu-zhi-lcof/comments/)
