## 单链表
### 表示
```c
typedef struct SingleLinkedList_t {
  int val;
  struct SingleLinkedList_t *next;
} SingleLinkedList;
```
### 插入操作
> 先让新来的节点有所指向。
### 删除操作
方法一：找到prev节点和next节点，让prev->next直接指向next节点  
方法二，不需要遍历寻找前序节点：
1. 将当前节点的后继节点值赋给当前节点，val = val->next，相当于把后继节点提前；
2. 这时有两个重复的节点，然后index->next = index->next->next，相当于删除了后继节点。
> 总结来说，也就是把后继节点的值保留在当前节点上，然后删除后继节点，避免寻找前序节点的复杂操作。

## 双链表
### 表示
```c
typedef struct ngx_queue_s ngx_queue_t;
struct ngx_queue_s {
  ngx_queue_t prev;
  ngx_queue_t next;
};
```
### 插入操作
先把new节点的prev和next指定，然后链接prev->next = new && next->prev = new
### 删除操作
prev->next = next
> 使用虚拟头节点和尾节点可以统一头尾节点的插入和删除操作

## 双指针技巧
1. 两个指针从不同位置出发：一个从始端开始，另一个从末端开始；
2. 两个指针以不同速度移动：一个指针快一些，另一个指针慢一些。  
对于单链表，因为我们只能在一个方向上遍历链表，所以第一种情景可能无法工作。然而，第二种情景，也被称为慢指针和快指针技巧，是非常有用的。
### 判断链表是否有环
解法一：哈希表，储存所有元素，然后比较  
解法二：快慢指针，快指针一次两步，慢指针一次一步，如果有环，入环后，快指针总能追上慢指针，公式计算：
a=c+(n-1)(b+c)  a: 入环前距离 b：慢指针入环后走的距离 c：（b+c）==环长  
note：注意判断fast->next和fast->next->next
### 寻找公共节点
解法一：哈希表  
解法二：栈，全部入栈，依次出栈判断是否有相同节点，思路是如果有公共节点，那从尾节点开始，公共区域是相同的  
解法三：双指针，分别指向两个链表，每个指针走完自己的链表就到对方链表的头节点接着走，当两个指针指向相同节点时就是公共节点。思路是a+b+c==b+a+c，a：链表a的不同区域，b：链表b的不同区域，c：公共区域  
### 删除倒数节点
快慢指针，快指针到尾节点时，删除慢指针指向节点  
### 反转链表
解法一：迭代法  
```c
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* curr = head;
    while (curr) {
        struct ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
```
解法二：栈，先全部入栈，然后依次push  
