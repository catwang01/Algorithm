[toc]

# Leetcode 1670. 设计前中后队列

## 问题描述

[1670. 设计前中后队列 - 力扣（LeetCode）](https://leetcode-cn.com/problems/design-front-middle-back-queue/)

## 算法

### 解法1：双端队列

#### 解法1：实现

##### 解法1： 实现：python

```
DEBUG = False

class Node:
    def __init__(self, val):
        self.val = val
        self.prev = None
        self.next = None

class FrontMiddleBackQueue:

    def __init__(self):
        self.head = Node(-1)
        self.tail = Node(-1)
        self.head.next = self.tail
        self.tail.prev = self.head
        self.middle = None # 维护中间节点
        self.size = 0
        
    def __repr__(self): # 用于 debug
        ret = "(size: {}) ".format(self.size)
        cur = self.head.next
        while cur != self.tail:
            if cur != self.middle:
                ret += str(cur.val) + "->"
            else:
                ret += "{}(middle)->".format(cur.val)
            cur = cur.next
        return ret.strip("->")

    def empty(self):
        return self.size == 0

    def insert(self, node, newNode): # insert a newNode after node without increasing self.size
        node.next.prev = newNode
        newNode.next = node.next
        node.next = newNode
        newNode.prev = node
        
    def delete(self, node): # delete the next node after node
        node1 = node
        node2 = node.next
        node3 = node.next.next
        node1.next = node3
        node3.prev = node1
        node2.next = node2.prev = None
        return node2.val
        
    def pushFront(self, val: int) -> None:
        newnode = Node(val)
        self.insert(self.head, newnode)
        if self.size & 1: # 奇数
            self.middle = self.middle.prev
        elif self.size == 0:
            self.middle = newnode
        # else: pass 
        self.size += 1
        if DEBUG: print(self)

    def pushMiddle(self, val: int) -> None:
        if self.empty():
            self.pushFront(val)
            return
        newNode = Node(val)
        if self.size & 1: # 奇数
            # x [1, 2, 3] ==> [1, x, 2, 3]
            self.insert(self.middle.prev, newNode)
        else:
            # x [1, 2, 3, 4] => [1, 2, x, 3, 4]
            self.insert(self.middle, newNode)
        self.middle = newNode
        self.size += 1
        if DEBUG: print(self)

    def pushBack(self, val: int) -> None:
        newnode = Node(val)
        self.insert(self.tail.prev, newnode)
        if self.size & 1: # 奇数
            pass # 不变
        elif self.size == 0:
            self.middle = newnode
        else: 
            self.middle = self.middle.next
        self.size += 1
        if DEBUG: print(self)

    def popFront(self) -> int:
        if self.empty(): return -1
        if self.size == 1:
            nextMiddle = None
        elif self.size & 1: # 奇数
            nextMiddle = self.middle
        else:
            nextMiddle = self.middle.next  
        ret = self.delete(self.head)
        self.middle = nextMiddle
        self.size -= 1
        if DEBUG: print(self)
        return ret
        
    def popMiddle(self) -> int:
        if self.empty(): return -1
        if self.size == 1:
            nextMiddle = None
        elif self.size & 1:
            nextMiddle = self.middle.prev
        else:
            nextMiddle = self.middle.next
        ret = self.delete(self.middle.prev)
        self.middle = nextMiddle
        self.size -= 1
        if DEBUG: print(self)
        return ret

    def popBack(self) -> int:
        if self.empty(): return -1
        if self.size == 1:
            nextMiddle = None
        elif self.size & 1: 
            nextMiddle = self.middle.prev
        else:
            nextMiddle = self.middle
        ret = self.delete(self.tail.prev.prev)
        self.middle = nextMiddle
        self.size -= 1
        if DEBUG: print(self)
        return ret
        



# Your FrontMiddleBackQueue object will be instantiated and called as such:
# obj = FrontMiddleBackQueue()
# obj.pushFront(val)
# obj.pushMiddle(val)
# obj.pushBack(val)
# param_4 = obj.popFront()
# param_5 = obj.popMiddle()
# param_6 = obj.popBack()
```
