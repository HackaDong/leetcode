### 特性
先进先出
普通队列缺点：随着元素的pop，会越来越占用空间
循环队列：固定数组，两个指针
双端队列：
优先队列：
### 普通队列实现
```c++
#include <iostream>

class MyQueue {
    private:
        // store elements
        vector<int> data;       
        // a pointer to indicate the start position
        int p_start;            
    public:
        MyQueue() {p_start = 0;}
        /** Insert an element into the queue. Return true if the operation is successful. */
        bool enQueue(int x) {
            data.push_back(x);
            return true;
        }
        /** Delete an element from the queue. Return true if the operation is successful. */
        bool deQueue() {
            if (isEmpty()) {
                return false;
            }
            p_start++;
            return true;
        };
        /** Get the front item from the queue. */
        int Front() {
            return data[p_start];
        };
        /** Checks whether the queue is empty or not. */
        bool isEmpty()  {
            return p_start >= data.size();
        }
};
```
### 循环队列实现
#### 复杂度分析
头部读取，尾部写入
**时间复杂度**：O(1)，所有方法都具有恒定的时间复杂度。
**空间复杂度**：O(N)，与数组实现相同。但是单链表实现f方式的内存效率更高。
```c
class MyCircularQueue {
private:
    vector<int> data;
    int head;
    int tail;
    int size;
public:
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) {
        data.resize(k);
        head = -1;
        tail = -1;
        size = k;
    }
    
    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        if (isFull()) {
            return false;
        }
        if (isEmpty()) {
            head = 0;
        }
        tail = (tail + 1) % size;
        data[tail] = value;
        return true;
    }
    
    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        if (isEmpty()) {
            return false;
        }
        if (head == tail) {
            head = -1;
            tail = -1;
            return true;
        }
        head = (head + 1) % size;
        return true;
    }
    
    /** Get the front item from the queue. */
    int Front() {
        if (isEmpty()) {
            return -1;
        }
        return data[head];
    }
    
    /** Get the last item from the queue. */
    int Rear() {
        if (isEmpty()) {
            return -1;
        }
        return data[tail];
    }
    
    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() {
        return head == -1;
    }
    
    /** Checks whether the circular queue is full or not. */
    bool isFull() {
        return ((tail + 1) % size) == head;
    }
};

```
### 用法
```c++
#include <iostream>

int main() {
    // 1. Initialize a queue.
    queue<int> q;
    // 2. Push new element.
    q.push(5);
    q.push(13);
    q.push(8);
    q.push(6);
    // 3. Check if queue is empty.
    if (q.empty()) {
        cout << "Queue is empty!" << endl;
        return 0;
    }
    // 4. Pop an element.
    q.pop();
    // 5. Get the first element.
    cout << "The first element is: " << q.front() << endl;
    // 6. Get the last element.
    cout << "The last element is: " << q.back() << endl;
    // 7. Get the size of the queue.
    cout << "The size is: " << q.size() << endl;
}
```
### 解决什么问题
> 346.数据流中的移动平均值
> 剑指offer59.滑动窗口的最大值

**思路：** 循环队列queue很适合解决这类窗口问题，queue就是窗口
每次计算先pop header然后push new
