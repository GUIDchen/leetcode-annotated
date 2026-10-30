# 题目：1860. 增长的内存泄露（Incremental Memory Leak）
# 思路：按秒模拟，第 i 秒消耗 i 个单位且总是从较大的那块扣减；当较大的一块都不够时循环结束，此时 i 就是崩溃时刻。
# 时间复杂度：O(√(memory1 + memory2))，累加和超过总容量即停；空间复杂度：O(1)，只用常数额外变量。
class Solution:  # LeetCode 约定的题解类
    def memLeak(self, memory1: int, memory2: int) -> List[int]:  # memory1、memory2：两块内存的初始空闲容量
        i = 1  # 从第 1 秒开始模拟
        while i <= max(memory1, memory2):  # 较大的那块仍够第 i 秒消耗就继续
            if memory1 >= memory2:  # 优先消耗较大的那一块，相等时选 memory1，符合题目的贪心规则
                memory1 -= i  # 从 memory1 扣掉 i（它是较大者，不会扣成负数）
            else:  # 否则 memory2 才是较大者
                memory2 -= i  # 从 memory2 扣掉 i
            i += 1  # 进入下一秒
        return [i, memory1, memory2]  # 第 i 秒已放不下，返回崩溃时刻与两块剩余容量
