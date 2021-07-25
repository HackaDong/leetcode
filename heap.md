# 堆
堆是一种优先队列的实现，能够使插入和删除操作在O(logN)的时间复杂度完成  
## 堆的定义和分类  
### 定义  
堆是一种特别的二叉树，需要满足：
1. 完全二叉树
2. 每个节点的值必须**大于等于 或 小于等于**其孩子节点的值
### 特性  
1. O(logN)时间复杂度完成插入和删除操作
2. O(1)时间复杂度获取堆的最大值和最小值
### 分类  
1. 最大堆
堆顶元素是最大值
2. 最小堆
堆顶元素是最小值
## 堆的插入操作  
插入操作是指向**堆**中插入一个元素后，**堆**依旧能够维持他的特性。
### 最小堆的插入  
1. 检查完全二叉树
2. 每个节点的值<=孩子节点的值
### 最大堆的插入  
1. 检查完全二叉树
2. 每个节点的值>=孩子节点的值
## 堆的删除操作  
删除操作是指在**堆**中删除堆顶元素。元素删除之后，**堆**依旧需要维持它的特性。
> 二叉树根节点的删除一般是将最后一个节点的值复制到根节点，然后将最后一个节点删除。
### 最小堆的删除  
1. 删除堆顶元素
2. 每个节点的值<=孩子节点的值
### 最大堆的删除  
1. 删除堆顶元素
2. 每个节点的值>=孩子节点的值
## 堆的实现  
### 完全二叉树和数组的转换  
#### 1. 如何找到父节点  
n = n/2
#### 2. 如何找到左孩子节点和有孩子节点  
左孩子：n*2
右孩子：n*2+1
#### 3. 如何确定叶子节点  
i > n/2 --> 叶子节点
## 时间复杂度和空间复杂度
| 堆操作 | 时间复杂度 | 空间复杂度 |
| :-: | :-: | :-: |
| 创建 | O(N) | O(N) |
| 插入 | O(logN) | O(1) |
| 删除 | O(logN) | O(1) |
| 获取堆顶元素 | O(1) | O(1) |
| 获取堆长度 | O(1) | O(1) |
### 创建堆  
空间复杂度：N个元素
时间复杂度：
求和（每层元素个数*需要交换的次数）= N
### 插入  
时间复杂度：
就是插入元素需要交换的次数，即堆的层数 = logN
### 删除  
时间复杂度：删除堆顶元素会把最后一个节点复制到堆顶，时间复杂度就是该元素需要交换的次数，也即堆的层数 = logN
## 代码  
```c
/* Minimum Heap */
#define MAX_HEAP_NUM 1024
typedef struct{
    int heap[MAX_HEAP_NUM];
    int heap_size;
} heap_constructor;
void exchange(int a, int b){
    if(a > heap.heap[0] || b > heap.heap[0])
        return;
    int tmp = heap.heap[a];
    heap.heap[a] = heap.heap[b];
    heap.heap[b] = tmp;
}
heap_constructor heap = {0};
heap_init(int heap_size){
    heap.heap_size = heap_size;
    // [0]用来存放当前元素个数
    heap.heap[0] = 0;
}
void heap_push(int element){
    if(++heap.heap[0] > heap.heap_size){
        heap.heap[0]--;
        return;
    }
    int idx = heap.heap[0];
    heap.heap[idx] = element;
    //将当前节点和父节点比较
    //idx必须大于1，保证idx/2 != 0，即父节点存在
    while(idx >1 && heap.heap[idx] < heap.heap[idx/2]){
        exchange(idx, idx/2);
        idx /= 2;
    }
}
void heap_pop(){
    if(!heap.heap[0])
        return;
    
    int idx = heap.heap[0];
    //交换堆顶元素和最后一个元素，并删除最后一个元素
    heap.heap[1] = heap.heap[idx];
    heap.heap[idx] = 0;
    heap.heap[0]--;
    //比较堆顶元素和左右孩子节点，重排序
    //idx*2 -> 左孩子，idx*2+1 -> 右孩子
    idx = 1;
    while((idx*2 <= heap.heap[0]
           &&
           heap.heap[idx] > heap.heap[idx*2]) 
           ||
           (idx*2+1 <= heap.heap[0]
           &&
           heap.heap[idx] > heap.heap[idx*2+1]) ){
        //找到子节点中小的那个进行交换
        int min_ele;
        if(idx*2+1 <= heap.heap[0])
            min_ele = heap.heap[idx*2] < heap.heap[idx*2+1]?idx*2:idx*2+1;
        else
            min_ele = idx*2;
        exchange(idx, min_ele);
        idx = min_ele;
    }
}
int heap_size(){
    return heap.heap[0];
}
int heap_peek(){
    return heap.heap[1];
}
```
