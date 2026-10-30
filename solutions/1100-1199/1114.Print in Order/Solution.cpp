// 题目：1114. 按序打印（Print in Order）
// 思路：两把互斥锁做接力。构造函数先把 m2、m3 锁住，first 打印后解锁 m2 放行 second，second 打印后解锁 m3 放行 third。
// 时间复杂度：O(1)，每个方法只需常数次加解锁；空间复杂度：O(1)，只多出两把互斥锁。
class Foo {  // LeetCode 约定的并发题类
private:  // 内部同步状态
    mutex m2, m3;  // m2 控制 first→second 的先后，m3 控制 second→third 的先后

public:  // 对外暴露给三个线程调用的接口
    Foo() {  // 构造函数在三个线程启动之前执行
        m2.lock();  // 预先锁住 m2，使 second 一进入就被阻塞
        m3.lock();  // 预先锁住 m3，使 third 一进入就被阻塞
    }

    void first(function<void()> printFirst) {  // printFirst 负责输出 "first"
        printFirst();  // 第一阶段直接打印
        m2.unlock();  // 打印完释放 m2，唤醒等待中的 second
    }

    void second(function<void()> printSecond) {  // printSecond 负责输出 "second"
        m2.lock();  // 等待 first 释放 m2，确保排在它之后
        printSecond();  // 拿到锁后执行第二阶段的打印
        m3.unlock();  // 打印完释放 m3，唤醒等待中的 third
    }

    void third(function<void()> printThird) {  // printThird 负责输出 "third"
        m3.lock();  // 等待 second 释放 m3，确保排在最后
        printThird();  // 最后执行打印
    }
};