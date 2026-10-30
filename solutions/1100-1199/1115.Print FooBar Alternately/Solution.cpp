// 题目：1115. 交替打印 FooBar（Print FooBar Alternately）
// 思路：两个信号量做乒乓：f 初值 1、b 初值 0；foo 每轮先等 f 再放 b，bar 每轮先等 b 再放 f，从而严格交替输出。
// 时间复杂度：O(n)，每轮常数次信号量操作；空间复杂度：O(1)，只多出两个信号量与一个计数器。
#include <semaphore.h>

class FooBar {  // LeetCode 约定的并发题类
private:  // 内部同步状态
    int n;  // 需要交替打印的轮数
    sem_t f, b;  // f 是 foo 的出场信号，b 是 bar 的出场信号

public:  // 对外暴露的接口
    FooBar(int n) {  // 构造函数在两个线程启动之前执行
        this->n = n;  // 记录需要交替打印的轮数
        sem_init(&f, 0, 1);  // f 初值为 1：foo 的第一轮可以立即执行
        sem_init(&b, 0, 0);  // b 初值为 0：bar 必须等 foo 先放行
    }

    void foo(function<void()> printFoo) {  // printFoo 负责输出 "foo"
        for (int i = 0; i < n; i++) {  // 共执行 n 轮
            sem_wait(&f);  // 申请 foo 的出场信号，拿不到就阻塞等待
            // printFoo() outputs "foo". Do not change or remove this line.
            printFoo();  // 真正输出 "foo"
            sem_post(&b);  // 放行 bar 的下一轮
        }
    }

    void bar(function<void()> printBar) {  // printBar 负责输出 "bar"
        for (int i = 0; i < n; i++) {  // 共执行 n 轮
            sem_wait(&b);  // 等待 foo 放行
            // printBar() outputs "bar". Do not change or remove this line.
            printBar();  // 真正输出 "bar"
            sem_post(&f);  // 放行 foo 的下一轮
        }
    }
};