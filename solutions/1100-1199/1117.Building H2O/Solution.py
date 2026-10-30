# 题目：1117. H2O 生成（Building H2O）
# 思路：Semaphore(2) 充当剩余氢槽位，Semaphore(0) 代表等待放行的氧；氢把槽位减到 0 时释放一个氧，氧再一次性补回 2 个槽位。
# 时间复杂度：O(n)，每个原子只做常数次信号量操作；空间复杂度：O(1)，只有两个信号量。
from threading import Semaphore  # Semaphore 即信号量，用内部计数控制氢氧配对


class H2O:  # LeetCode 约定的多线程题解类
    def __init__(self):  # 构造：初始化两个信号量
        self.h = Semaphore(2)  # 初值 2：允许两个氢原子先进入本轮
        self.o = Semaphore(0)  # 初值 0：氧原子必须等两个氢到齐

    def hydrogen(self, releaseHydrogen: "Callable[[], None]") -> None:  # 氢线程入口：每两个氢配一个氧
        self.h.acquire()  # 占用一个氢槽位（内部计数减 1）
        # 下面这行是判题器提供的输出回调，题目要求原样保留，不能删除或改写
        # releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen()  # 输出一个 H
        if self.h._value == 0:  # 读内部计数：减到 0 说明本轮两个氢已到齐
            self.o.release()  # 放行一个氧原子

    def oxygen(self, releaseOxygen: "Callable[[], None]") -> None:  # 氧线程入口：每个氧开启新的一轮
        self.o.acquire()  # 等两个氢原子都到齐后才被唤醒
        # 下面这行是判题器提供的输出回调，题目要求原样保留，不能删除或改写
        # releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen()  # 输出一个 O
        self.h.release(2)  # 一次性补回 2 个氢槽位，开启下一轮
