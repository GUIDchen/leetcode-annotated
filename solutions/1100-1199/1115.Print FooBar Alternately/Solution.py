# 题目：1115. 交替打印 FooBar（Print FooBar Alternately）
# 思路：两个 Semaphore 做乒乓：f 初值 1、b 初值 0；foo 每轮先 acquire f 再 release b，bar 反过来，从而严格交替。
# 时间复杂度：O(n)，每轮常数次信号量操作；空间复杂度：O(1)，只多出两个信号量与一个计数器。
from threading import Semaphore


class FooBar:  # LeetCode 约定的并发题类
    def __init__(self, n):  # 构造函数在两个线程启动之前执行
        self.n = n  # 记录需要交替打印的轮数
        self.f = Semaphore(1)  # f 初值为 1：foo 的第一轮可以立即执行
        self.b = Semaphore(0)  # b 初值为 0：bar 必须等 foo 先放行

    def foo(self, printFoo: "Callable[[], None]") -> None:  # printFoo 负责输出 "foo"
        for _ in range(self.n):  # 共执行 n 轮
            self.f.acquire()  # 申请 foo 的出场信号，拿不到就阻塞等待
            # printFoo() outputs "foo". Do not change or remove this line.
            printFoo()  # 真正输出 "foo"
            self.b.release()  # 放行 bar 的下一轮

    def bar(self, printBar: "Callable[[], None]") -> None:  # printBar 负责输出 "bar"
        for _ in range(self.n):  # 共执行 n 轮
            self.b.acquire()  # 等待 foo 放行
            # printBar() outputs "bar". Do not change or remove this line.
            printBar()  # 真正输出 "bar"
            self.f.release()  # 放行 foo 的下一轮
