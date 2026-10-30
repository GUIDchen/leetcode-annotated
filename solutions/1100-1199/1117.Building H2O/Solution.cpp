// 题目：1117. H2O 生成（Building H2O）
// 思路：信号量 h 表示本轮还剩几个氢槽位（初值 2）、o 表示等待放行的氧（初值 0）；两个氢用完后唤醒氧，氧再一次性归还 2 个氢槽位。
// 时间复杂度：O(n)，每个原子只做常数次信号量操作；空间复杂度：O(1)，只有两个信号量与一个计数。
#include <semaphore.h>  // 需要 POSIX 信号量 sem_t 以及 sem_init/sem_wait/sem_post

class H2O {  // LeetCode 约定的多线程题解类
private:  // 以下状态只在类内部使用
    sem_t h, o;  // h：还能进入几个氢原子；o：凑满两个氢后放行氧原子
    int st;  // 本轮已经到达的氢原子个数

public:  // 构造函数与两个线程入口对外可见
    H2O() {  // 构造：初始化信号量与氢计数
        sem_init(&h, 0, 2);  // 初值 2：允许两个氢原子先进入本轮
        sem_init(&o, 0, 0);  // 初值 0：氧原子必须等两个氢到齐
        st = 0;  // 本轮还没有氢原子到达
    }  // 构造结束

    void hydrogen(function<void()> releaseHydrogen) {  // 氢线程：每两个氢配一个氧
        sem_wait(&h);  // 占用一个氢槽位（剩余槽位数减 1）
        // 下面这行是判题器提供的输出回调，题目要求原样保留，不能删除或改写
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();  // 输出一个 H
        ++st;  // 累计本轮已到达的氢原子数
        if (st == 2) {  // 两个氢已经到齐
            sem_post(&o);  // 放行一个氧原子
        }  // 条件结束
    }  // hydrogen 结束

    void oxygen(function<void()> releaseOxygen) {  // 氧线程：每个氧开启新的一轮
        sem_wait(&o);  // 等两个氢原子都到齐后才被唤醒
        // 下面这行是判题器提供的输出回调，题目要求原样保留，不能删除或改写
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();  // 输出一个 O
        st = 0;  // 新一轮开始，氢计数清零
        sem_post(&h);  // 归还一个氢槽位
        sem_post(&h);  // 再归还一个，下一轮的 h 初值恢复为 2
    }  // oxygen 结束
};  // 类定义结束