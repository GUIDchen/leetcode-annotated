# 题目：1114. 按序打印（Print in Order）
# 思路：两把 Lock 组成接力链。构造函数先 acquire 掉两把锁，first 打印后 release l2，second 打印后 release l3，从而强制先后顺序。
# 时间复杂度：O(1)，每个方法只需常数次加解锁；空间复杂度：O(1)，只多出两个锁对象。
class Foo:  # LeetCode 约定的并发题类
    def __init__(self):  # 构造函数在三个线程启动之前执行
        self.l2 = threading.Lock()  # 控制 first→second 先后的锁
        self.l3 = threading.Lock()  # 控制 second→third 先后的锁
        self.l2.acquire()  # 预先占住 l2，使 second 一进入就被阻塞
        self.l3.acquire()  # 预先占住 l3，使 third 一进入就被阻塞

    def first(self, printFirst: 'Callable[[], None]') -> None:  # printFirst 负责输出 "first"
        printFirst()  # 第一阶段直接打印
        self.l2.release()  # 打印完释放 l2，唤醒等待中的 second

    def second(self, printSecond: 'Callable[[], None]') -> None:  # printSecond 负责输出 "second"
        self.l2.acquire()  # 等待 first 释放 l2，确保排在它之后
        printSecond()  # 拿到锁后执行第二阶段的打印
        self.l3.release()  # 打印完释放 l3，唤醒等待中的 third

    def third(self, printThird: 'Callable[[], None]') -> None:  # printThird 负责输出 "third"
        self.l3.acquire()  # 等待 second 释放 l3，确保排在最后
        printThird()  # 最后执行打印
