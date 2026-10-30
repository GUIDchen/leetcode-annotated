# 题目：158. 用 Read4 读取 N 个字符 II - 多次调用（Read N Characters Given read4 II - Call Multiple Times）
# 思路：把 read4 的缓冲区 buf4 与游标 i、size 放到实例属性上，上次没被取走的多余字符留到下一次 read 继续消费。
# 时间复杂度：每次 read 为 O(n)，字符不会被重复搬运；空间复杂度：O(1)，固定长度 4 的缓冲加三个属性。
# The read4 API is already defined for you.
# def read4(buf4: List[str]) -> int:


class Solution:  # LeetCode 约定的题解类（判题器已提供全局函数 read4）
    def __init__(self):  # 构造函数：初始化跨多次调用保留的状态
        self.buf4 = [None] * 4  # read4 的缓冲，必须持久化，才能留住上次未消费的字符
        self.i = self.size = 0  # i 是本批下一个待消费字符的下标；size 是本批有效字符数，初始都为 0 表示还没有缓冲

    def read(self, buf: List[str], n: int) -> int:  # buf：目标缓冲区；n：本次最多读取的字符数；返回本次实际读到的字符数
        j = 0  # j 记录本次已经写进 buf 的字符数
        while j < n:  # 还没凑够 n 个就继续
            if self.i == self.size:  # 上一批已全部消费完，需要再向 read4 要一批
                self.size = read4(self.buf4)  # 读新的一批，size 记录本批实际长度
                self.i = 0  # 从本批第 0 个字符开始消费
                if self.size == 0:  # 本批长度为 0 说明文件已读完
                    break  # 跳出循环，返回本次实际读到的 j
            while j < n and self.i < self.size:  # 把本批剩余字符搬进 buf，同时推进两个游标
                buf[j] = self.buf4[self.i]  # 写入目标的第 j 个位置
                self.i += 1  # buf4 的读游标前进
                j += 1  # buf 的写游标前进
        return j  # 返回本次调用实际写入的字符数
