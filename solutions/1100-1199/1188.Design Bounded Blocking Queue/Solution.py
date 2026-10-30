# 题目：1188. 设计有限阻塞队列（Design Bounded Blocking Queue）
# 思路：两个信号量分工——s1 表示空位（入队前 acquire、出队后 release），s2 表示已有元素（出队前 acquire、入队后 release），底层用 deque 存数据。
# 时间复杂度：enqueue/dequeue 均摊 O(1)，size 为 O(1)；空间复杂度：O(capacity)。
from threading import Semaphore  # Python 标准库的计数信号量，天然支持阻塞与唤醒


class BoundedBlockingQueue(object):  # 有界阻塞队列，多线程下满则阻塞入队、空则阻塞出队
    def __init__(self, capacity: int):  # capacity：队列容量上限
        self.s1 = Semaphore(capacity)  # s1 表示空位，初值为容量
        self.s2 = Semaphore(0)  # s2 表示已有元素，初值为 0
        self.q = deque()  # 底层用双端队列，两端增删都是 O(1)

    def enqueue(self, element: int) -> None:  # 生产者：队列满时阻塞
        self.s1.acquire()  # 先拿到一个空位，满了就阻塞在这里
        self.q.append(element)  # 从右端入队
        self.s2.release()  # 元素数加一，唤醒可能在等元素的消费者

    def dequeue(self) -> int:  # 消费者：队列空时阻塞
        self.s2.acquire()  # 先等到一个元素，空了就阻塞在这里
        ans = self.q.popleft()  # 从左端取出队首元素，保证先进先出
        self.s1.release()  # 归还一个空位，唤醒可能在等空位的生产者
        return ans  # 返回取到的元素

    def size(self) -> int:  # 当前元素个数
        return len(self.q)  # deque 的长度就是队列大小
