# 题目：3023. 在无限流中寻找模式 I（Find Pattern in Infinite Stream I）
# 核心思路：把模式串拆成高 half 位 a 与低 m-half 位 b，再用 x、y 两个滚动窗口分别维护流中最近 m 位的高半段与低半段（左移拼接 + 掩码截断）；当已读入 i ≥ m 且 x == a、y == b 时，窗口起点 i - m 就是答案。
# 时间复杂度：O(m + 答案位置)，每个流元素只读一次；空间复杂度：O(1)，只有几个整数掩码与窗口变量。
# Definition for an infinite stream.
# class InfiniteStream:
#     def next(self) -> int:
#         pass
class Solution:  # LeetCode 约定的题解类
    def findPattern(  # 在无限流中寻找模式串首次出现的起始下标
        self, stream: Optional["InfiniteStream"], pattern: List[int]  # stream：无限流对象；pattern：要寻找的 0/1 模式
    ) -> int:  # 返回模式首次出现的起始下标（0 基）
        a = b = 0  # a：模式高 half 位拼成的整数；b：模式低 m-half 位拼成的整数
        m = len(pattern)  # m：模式长度，同时就是滑动窗口大小
        half = m >> 1  # 把窗口切成两半，前 half 位放进 a，其余放进 b
        mask1 = (1 << half) - 1  # 保留低 half 位的掩码，用来截断窗口 x
        mask2 = (1 << (m - half)) - 1  # 保留低 m-half 位的掩码，用来截断窗口 y
        for i in range(half):  # 把模式的前半段逐位拼进 a
            a |= pattern[i] << (half - 1 - i)  # 第 i 位左移到它在 a 中的位置后按位或进去
        for i in range(half, m):  # 把模式的后半段逐位拼进 b
            b |= pattern[i] << (m - 1 - i)  # 第 i 位左移到它在 b 中的位置后按位或进去
        x = y = 0  # x：流窗口的高半段；y：流窗口的低半段
        for i in count(1):  # i 记录已从流中读入的元素个数，从 1 开始；无限循环，找到即返回
            v = stream.next()  # 取出流中的下一个 0/1
            y = y << 1 | v  # 新元素进入最低位：y 左移一位再拼上 v
            v = y >> (m - half) & 1  # 取出被挤出低半段的最高位，它接下来要移入高半段
            y &= mask2  # 截断 y，只保留低 m-half 位
            x = x << 1 | v  # 把挤出的那一位推进高半段 x
            x &= mask1  # 截断 x，只保留低 half 位
            if i >= m and a == x and b == y:  # 已经读满 m 位，且窗口两半都与模式完全一致
                return i - m  # 当前窗口的起点就是 i - m，返回这个 0 基下标
