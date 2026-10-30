// 题目：622. 设计循环队列（Design Circular Queue）
// 思路：定长数组 + 队头下标 + 元素个数；入队写在下标 (front+size)%capacity，出队后移 front，用 size 区分空与满。
// 时间复杂度：每个操作均为 O(1)；空间复杂度：O(k)，需要一个容量为 k 的定长数组。
class MyCircularQueue {  // 用定长数组加队头下标实现的循环队列
private:  // 内部状态对外隐藏
    int front;  // 队头元素在数组中的下标
    int size;  // 当前元素个数；用它可以避免「队头=队尾」时无法区分空与满
    int capacity;  // 队列容量 k
    vector<int> q;  // 承载数据的定长数组

public:  // 对外提供题目要求的六个操作
    MyCircularQueue(int k) {  // 构造函数，k 为队列容量
        capacity = k;  // 记录容量，取模时要用
        q = vector<int>(k);  // 申请 k 个槽位
        front = size = 0;  // 空队列：队头下标与元素个数都归零
    }

    bool enQueue(int value) {  // 入队：成功返回 true，队满返回 false
        if (isFull()) return false;  // 已满则无法入队
        int idx = (front + size) % capacity;  // 队尾下标 = 队头 + 元素个数，取模后自然绕回数组开头
        q[idx] = value;  // 把新值写到队尾槽位
        ++size;  // 元素个数加一
        return true;  // 入队成功
    }

    bool deQueue() {  // 出队：成功返回 true，队空返回 false
        if (isEmpty()) return false;  // 已空则无法出队
        front = (front + 1) % capacity;  // 队头后移一格并取模，走到末尾就绕回开头
        --size;  // 元素个数减一
        return true;  // 出队成功
    }

    int Front() {  // 取队头元素，空队列返回 -1
        if (isEmpty()) return -1;  // 空队列按题目约定返回 -1
        return q[front];  // 返回队头槽位的值
    }

    int Rear() {  // 取队尾元素，空队列返回 -1
        if (isEmpty()) return -1;  // 空队列按题目约定返回 -1
        int idx = (front + size - 1) % capacity;  // 队尾下标 = 队头 + 元素个数 - 1
        return q[idx];  // 返回队尾槽位的值
    }

    bool isEmpty() {  // 判空：元素个数为 0
        return size == 0;  // 用 size 判断，与判满条件互不冲突
    }

    bool isFull() {  // 判满：元素个数等于容量
        return size == capacity;  // size 达到容量即已满
    }
};

// 下面是 LeetCode 判题器自动生成的对象使用示例注释，原样保留
/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */