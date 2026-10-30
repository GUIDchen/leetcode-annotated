// 题目：1195. 多线程 Fizz Buzz（Fizz Buzz Multithreaded）
// 思路：四个线程共用一把互斥锁和一个原子计数器，只有编号匹配的线程才有资格输出并推进计数器。
// 时间复杂度：O(n)，每个编号只输出一次；空间复杂度：O(1)，只多存了互斥锁与计数器。
class FizzBuzz {  // LeetCode 约定的题解类
private:  // 以下为私有成员，四个线程共享
    std::mutex mtx;  // 互斥锁：保证「判断 index + 输出 + index++」三步整体原子
    atomic<int> index;  // 原子计数器，表示当前该输出的编号，从 1 走到 n
    int n;  // 输出上界，各线程的 while 条件都要用它

    // 这里主要运用到了C++11中的RAII锁(lock_guard)的知识。
    // 需要强调的一点是，在进入循环后，要时刻不忘加入index <= n的逻辑
public:  // 对外暴露构造函数与四个线程入口
    FizzBuzz(int n) {  // 构造函数：记录上界并把计数器置为 1
        this->n = n;  // 把传入的上界保存到成员变量
        index = 1;  // 从 1 开始输出（输出范围 1..n）
    }

    void fizz(function<void()> printFizz) {  // fizz 线程：专门负责 3 的倍数（且不是 5 的倍数）
        while (index <= n) {  // 没输出完就持续尝试；原子读取 index，这里不加锁
            std::lock_guard<std::mutex> lk(mtx);  // RAII 加锁，离开作用域自动解锁，不会忘记 unlock
            if (0 == index % 3 && 0 != index % 5 && index <= n) {  // 是 3 的倍数、不是 5 的倍数、且未越界时才能由本线程输出
                printFizz();  // 调用题目给出的回调，打印 fizz
                index++;  // 输出后推进计数器，把机会让给下一个编号
            }
        }
    }

    void buzz(function<void()> printBuzz) {  // buzz 线程：专门负责 5 的倍数（且不是 3 的倍数）
        while (index <= n) {  // 没输出完就持续尝试
            std::lock_guard<std::mutex> lk(mtx);  // 加锁进入临界区
            if (0 == index % 5 && 0 != index % 3 && index <= n) {  // 是 5 的倍数、不是 3 的倍数、且未越界时才轮到本线程
                printBuzz();  // 打印 buzz
                index++;  // 推进计数器
            }
        }
    }

    void fizzbuzz(function<void()> printFizzBuzz) {  // fizzbuzz 线程：负责同时是 3 和 5 的倍数（即 15 的倍数）
        while (index <= n) {  // 没输出完就持续尝试
            std::lock_guard<std::mutex> lk(mtx);  // 加锁进入临界区
            if (0 == index % 15 && index <= n) {  // 是 15 的倍数且未越界时由本线程输出
                printFizzBuzz();  // 打印 fizzbuzz
                index++;  // 推进计数器
            }
        }
    }

    void number(function<void(int)> printNumber) {  // number 线程：负责既非 3 倍数也非 5 倍数的数字
        while (index <= n) {  // 没输出完就持续尝试
            std::lock_guard<std::mutex> lk(mtx);  // 加锁进入临界区
            if (0 != index % 3 && 0 != index % 5 && index <= n) {  // 既不是 3 的倍数也不是 5 的倍数，才由本线程输出数字本身
                printNumber(index);  // 把当前编号打印出来
                index++;  // 推进计数器
            }
        }
    }
};