// 题目：1116. 打印零与奇偶数（Print Zero Even Odd）
// 思路：三个信号量 z/e/o 串成流水线——零线程打印 0 后按当前奇偶决定唤醒谁，奇/偶线程打印完数字再把打印权交回零线程。
// 时间复杂度：O(n)，共输出 2n 个字符且每个只输出一次；空间复杂度：O(1)，只用常量个信号量与计数变量。
#include <semaphore.h>  // 需要 POSIX 信号量 sem_t 以及 sem_init/sem_wait/sem_post

class ZeroEvenOdd {  // LeetCode 约定的多线程题解类
private:  // 以下三个成员只在类内部使用
    int n;  // 要打印到的上界，0 与数字各出现 n 次
    sem_t z, e, o;  // z：打印 0 的许可；o：打印奇数的许可；e：打印偶数的许可

public:  // 构造函数与三个线程入口对外可见
    ZeroEvenOdd(int n) {  // 构造：保存上界并初始化三个信号量
        this->n = n;  // 成员与形参同名，用 this 明确赋值给成员变量
        sem_init(&z, 0, 1);  // z 初值 1：零线程一启动就能拿到打印权
        sem_init(&e, 0, 0);  // e 初值 0：偶数线程先阻塞等待
        sem_init(&o, 0, 0);  // o 初值 0：奇数线程先阻塞等待
    }  // 构造结束

    // printNumber 是判题器注入的回调，真正负责输出数字；三个线程函数本身都不直接写 stdout
    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {  // 零线程：负责所有 0，并给奇数/偶数线程发许可
        for (int i = 0; i < n; ++i) {  // 一共 n 组「0 + 一个数字」，所以要打印 n 次 0
            sem_wait(&z);  // 等打印权：上一轮的数字打印完会释放 z
            printNumber(0);  // 输出 0（必须用题目给的回调，不能直接写 stdout）
            if (i % 2 == 0) {  // 第 i 组（从 0 计）后面接数字 i+1，i 为偶数时该数字是奇数
                sem_post(&o);  // 唤醒奇数线程去打印奇数
            } else {  // 否则下一个数字是偶数
                sem_post(&e);  // 唤醒偶数线程去打印偶数
            }  // 奇偶分支结束
        }  // n 组全部打完
    }  // zero 结束

    void even(function<void(int)> printNumber) {  // 偶数线程：输出 2,4,6,...
        for (int i = 2; i <= n; i += 2) {  // 起点 2、步长 2，保证只遍历偶数
            sem_wait(&e);  // 等零线程打印完 0 并唤醒自己
            printNumber(i);  // 输出当前偶数
            sem_post(&z);  // 把打印权交回零线程，进入下一组
        }  // 偶数打印完毕
    }  // even 结束

    void odd(function<void(int)> printNumber) {  // 奇数线程：输出 1,3,5,...
        for (int i = 1; i <= n; i += 2) {  // 起点 1、步长 2，保证只遍历奇数
            sem_wait(&o);  // 等零线程打印完 0 并唤醒自己
            printNumber(i);  // 输出当前奇数
            sem_post(&z);  // 把打印权交回零线程，进入下一组
        }  // 奇数打印完毕
    }  // odd 结束
};  // 类定义结束