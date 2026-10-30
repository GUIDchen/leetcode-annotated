// 题目：1188. 设计有限阻塞队列（Design Bounded Blocking Queue）
// 思路：用两个 POSIX 信号量协作——s1 统计剩余空位（入队前 P，出队后 V），s2 统计已有元素（出队前 P，入队后 V）。
// 时间复杂度：enqueue/dequeue 均摊 O(1)，size 为 O(1)；空间复杂度：O(capacity) 存队列元素。
#include <semaphore.h>  // POSIX 信号量，LeetCode 的 C++ 环境可以直接使用

class BoundedBlockingQueue {  // 有界阻塞队列：多线程环境下入队/出队会在满/空时自动阻塞
public:  // 对外提供的方法
    BoundedBlockingQueue(int capacity) {  // capacity：队列能容纳的最大元素个数
        sem_init(&s1, 0, capacity);  // s1 统计空位，初值就是容量：入队前必须拿到一个空位
        sem_init(&s2, 0, 0);  // s2 统计已有元素，初值 0：出队前必须有元素可用
    }  // 构造函数结束

    void enqueue(int element) {  // 生产者：队列满时在这里阻塞等待
        sem_wait(&s1);  // 先占用一个空位；队列已满时会一直阻塞
        q.push(element);  // 拿到空位后，入队是安全的
        sem_post(&s2);  // 元素数加一，唤醒可能在等元素的消费者
    }  // enqueue 结束

    int dequeue() {  // 消费者：队列空时在这里阻塞等待
        sem_wait(&s2);  // 先等一个元素；队列为空时会一直阻塞
        int ans = q.front();  // 读出队首元素
        q.pop();  // 从队列中移除该元素
        sem_post(&s1);  // 空位数加一，唤醒可能在等空位的生产者
        return ans;  // 把取到的元素返回给调用者
    }  // dequeue 结束

    int size() {  // 当前队列中的元素个数
        return q.size();  // 直接返回底层容器的大小
    }  // size 结束

private:  // 以下为内部状态
    queue<int> q;  // 底层容器，只在持有相应信号量时被访问
    sem_t s1, s2;  // s1：剩余空位；s2：已有元素数
};  // 类定义结束