# 题目：1116. 打印零与奇偶数（Print Zero Even Odd）
# 思路：三个信号量 z/e/o 串成流水线，零线程打印 0 后按当前奇偶发放许可，奇/偶线程打印完数字再把许可交回零线程。
# 时间复杂度：O(n)，共输出 2n 个字符且每个只输出一次；空间复杂度：O(1)，只用常量个信号量。
from threading import Semaphore  # Semaphore 即信号量，用内部计数控制三个线程的先后次序


class ZeroEvenOdd:  # LeetCode 约定的多线程题解类
    def __init__(self, n):  # 构造：保存上界 n 并初始化三个信号量
        self.n = n  # 记录要打印到的最大值
        self.z = Semaphore(1)  # z 初值 1：零线程一启动就能拿到打印权
        self.e = Semaphore(0)  # e 初值 0：偶数线程先阻塞等待
        self.o = Semaphore(0)  # o 初值 0：奇数线程先阻塞等待

    # printNumber 是判题器注入的回调，真正负责输出数字；三个线程方法本身都不直接写 stdout
    # printNumber(x) outputs "x", where x is an integer.
    def zero(self, printNumber: 'Callable[[int], None]') -> None:  # 零线程：负责所有 0，并给奇数/偶数线程发许可
        for i in range(self.n):  # 一共 n 组「0 + 一个数字」，所以要打印 n 次 0
            self.z.acquire()  # 等打印权：上一轮的奇数或偶数释放 z 后才继续
            printNumber(0)  # 输出 0（必须调用题目给的回调）
            if i % 2 == 0:  # 第 i 组（从 0 计）后面接数字 i+1，i 为偶数时该数字是奇数
                self.o.release()  # 唤醒奇数线程去打印奇数
            else:  # 否则下一个数字是偶数
                self.e.release()  # 唤醒偶数线程去打印偶数

    def even(self, printNumber: 'Callable[[int], None]') -> None:  # 偶数线程：输出 2,4,6,...
        for i in range(2, self.n + 1, 2):  # 起点 2、步长 2、上界含 n，只枚举偶数
            self.e.acquire()  # 等零线程打印完 0 并唤醒自己
            printNumber(i)  # 输出当前偶数
            self.z.release()  # 把打印权交回零线程，进入下一组

    def odd(self, printNumber: 'Callable[[int], None]') -> None:  # 奇数线程：输出 1,3,5,...
        for i in range(1, self.n + 1, 2):  # 起点 1、步长 2、上界含 n，只枚举奇数
            self.o.acquire()  # 等零线程打印完 0 并唤醒自己
            printNumber(i)  # 输出当前奇数
            self.z.release()  # 把打印权交回零线程，进入下一组
