## 特性
后进先出
## 函数
```c++
#include <iostream>

int main() {
    // 1. Initialize a stack.
    stack<int> s;
    // 2. Push new element.
    s.push(5);
    s.push(13);
    s.push(8);
    s.push(6);
    // 3. Check if stack is empty.
    if (s.empty()) {
        cout << "Stack is empty!" << endl;
        return 0;
    }
    // 4. Pop an element.
    s.pop();
    // 5. Get the top element.
    cout << "The top element is: " << s.top() << endl;
    // 6. Get the size of the stack.
    cout << "The size is: " << s.size() << endl;
}
```
## 实现
```c++
#include <iostream>

class MyStack {
    private:
        vector<int> data;               // store elements
    public:
        /** Insert an element into the stack. */
        void push(int x) {
            data.push_back(x);
        }
        /** Checks whether the queue is empty or not. */
        bool isEmpty() {
            return data.empty();
        }
        /** Get the top item from the queue. */
        int top() {
            return data.back();
        }
        /** Delete an element from the queue. Return true if the operation is successful. */
        bool pop() {
            if (isEmpty()) {
                return false;
            }
            data.pop_back();
            return true;
        }
};
```
## 解决问题
### 带最小值的栈
> 155.最小栈       

设计一个支持 **push** ，**pop** ，**top** 操作，并能在常数时间内检索到最小元素的栈。
**思路一： 辅助栈：** 添加最小栈，每次push后比较当前值和最小栈top()，如果当前值小则将其push到最小栈，否则最小栈push自己栈顶元素。pop时两个栈同时删除元素。查询最小值则返回最小值top()。
**思路二：储存diff：** 
```c++
class MinStack {
private:
    stack<long> st;
    long  _min;
    
public:
    /** initialize your data structure here. */
    MinStack() {}
    
    void push(int x) {
        if (!st.empty()) {
            long long diff = x - _min;
            _min = diff > 0 ? _min : x;
            st.push(diff);
        }
        else {
            _min = x;
            st.push(0);
        }
    }
    
    void pop() {
        if (!st.empty()) {
            long long diff = st.top();
            st.pop();
            if (diff < 0) {
                _min = int (_min - diff);
            }
        }
    }
    
    int top() {
        return st.top() < 0 ? _min : int(st.top() + _min);
    }
    
    int getMin() {
        return _min;
    }
};
```
### 对称问题
> 20. 有效的括号

给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。
**思路：** 将左括号对应的右括号入栈，遇到右括号时出栈，同时比较是否相等

### 单调栈模板问题
> 739.每日温度
> 496.下一个更大元素1
> 503.下一个更大元素2

给你一个数组，返回一个等长的数组，对应索引存储着下一个更大元素，如果没有更大的元素，就存 -1。
[参考](https://github.com/labuladong/fucking-algorithm/blob/master/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%E7%B3%BB%E5%88%97/%E5%8D%95%E8%B0%83%E6%A0%88.md)
**思路：单调栈** 一般只用于处理这类Next Greater Element问题
处理数组从后向前，如果是更大元素问题，生成一个单调栈，站内元素单调递减或者单调不增。当处理某个元素时，将该元素和栈顶元素进行比较，如果栈顶元素<=当前元素，说明栈顶元素不是下个更大元素，则将其pop，进行下一次比较。如果栈顶元素>当前元素，则将栈顶元素作为当前元素对应的结果。
更大元素模板：
```c++

vector<int> nextGreaterElement(vector<int>& nums) {
    vector<int> res(nums.size()); // 存放答案的数组
    stack<int> s;
    // 倒着往栈里放
    for (int i = nums.size() - 1; i >= 0; i--) {
        // 判定个子高矮
        while (!s.empty() && s.top() <= nums[i]) {
            // 矮个起开，反正也被挡着了。。。
            s.pop();
        }
        // nums[i] 身后的 next great number
        res[i] = s.empty() ? -1 : s.top();
        // 
        s.push(nums[i]);
    }
    return res;
}
```
#### 问题变形
1. 每日问题，求距离下个最大值的距离
**思路：** 栈中储存距离值
2. 环形队列问题
**思路：** index求模
2.1 如何求解最后一个数的下个最大值
**思路：** 数组长度翻倍，在操作时因为有求模操作，所以只需要index加倍
