// 题目：641. 设计循环双端队列（Design Circular Deque）
// 核心思路：用定长数组当环形缓冲区，front 记录队头下标、size 记录元素个数；头插尾插、头删尾删都靠取模让下标绕回，队尾位置由 front + size 推出。
// 时间复杂度：每个操作 O(1)；空间复杂度：O(k)，存放 k 个槽位。
class MyCircularDeque {  // 循环双端队列：用定长数组模拟环形缓冲区
public:  // 对外提供的接口
    vector<int> q;  // 底层定长数组，循环使用
    int front = 0;  // 队头元素所在的下标
    int size = 0;  // 当前元素个数
    int capacity = 0;  // 容量上限 k

    MyCircularDeque(int k) {  // 构造函数：把容量设为 k
        q.assign(k, 0);  // 分配 k 个槽位并初始化为 0
        capacity = k;  // 记录容量
    }  // 构造完成

    bool insertFront(int value) {  // 从队头插入元素，成功返回 true
        if (isFull()) {  // 队列已满则无法插入
            return false;  // 插入失败
        }  // 未满，可以继续
        if (!isEmpty()) {  // 队列非空时队头需要前移一格
            front = (front - 1 + capacity) % capacity;  // 先加 capacity 再取模，避免出现负数下标
        }  // 空队列时 front 保持不动，直接写入
        q[front] = value;  // 把新元素写到新的队头位置
        ++size;  // 元素个数加一
        return true;  // 插入成功
    }  // insertFront 结束

    bool insertLast(int value) {  // 从队尾插入元素，成功返回 true
        if (isFull()) {  // 队列已满则无法插入
            return false;  // 插入失败
        }  // 未满，可以继续
        int idx = (front + size) % capacity;  // 队尾的下一个空位下标（取模绕回）
        q[idx] = value;  // 写入新元素
        ++size;  // 元素个数加一
        return true;  // 插入成功
    }  // insertLast 结束

    bool deleteFront() {  // 从队头删除元素，成功返回 true
        if (isEmpty()) {  // 空队列没有元素可删
            return false;  // 删除失败
        }  // 非空，可以继续
        front = (front + 1) % capacity;  // 队头后移一格，取模绕回
        --size;  // 元素个数减一
        return true;  // 删除成功
    }  // deleteFront 结束

    bool deleteLast() {  // 从队尾删除元素，成功返回 true
        if (isEmpty()) {  // 空队列没有元素可删
            return false;  // 删除失败
        }  // 非空，可以继续
        --size;  // 只需把个数减一，原队尾元素自然失效
        return true;  // 删除成功
    }  // deleteLast 结束

    int getFront() {  // 返回队头元素
        return isEmpty() ? -1 : q[front];  // 空队列按题意返回 -1，否则返回队头元素
    }  // getFront 结束

    int getRear() {  // 返回队尾元素
        return isEmpty() ? -1 : q[(front + size - 1) % capacity];  // 空队列返回 -1，否则取最后一个元素的下标
    }  // getRear 结束

    bool isEmpty() {  // 判断队列是否为空
        return size == 0;  // 元素个数为 0 即为空
    }  // isEmpty 结束

    bool isFull() {  // 判断队列是否已满
        return size == capacity;  // 元素个数等于容量即为满
    }  // isFull 结束
};  // 类结束

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */