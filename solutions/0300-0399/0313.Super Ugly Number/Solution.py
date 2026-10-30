# 题目：313. 超级丑数（Super Ugly Number）
# 思路：小根堆逐个生成丑数：每次弹出最小值，再乘以各质数入堆；利用「x 能被 k 整除就 break」去重。
# 时间复杂度：O(n·p·log(np))，p 为质数个数；空间复杂度：O(np)，堆可能存放的候选数。
class Solution:  # LeetCode 约定的题解类
    def nthSuperUglyNumber(self, n: int, primes: List[int]) -> int:  # n：要找第 n 个超级丑数；primes：给定的质数集合
        q = [1]  # 小根堆：用列表模拟，初始只有 1（第一个超级丑数）
        x = 0  # 保存每次弹出的丑数，循环结束时它就是答案
        mx = (1 << 31) - 1  # int32 最大值，用来判断乘法是否会溢出
        for _ in range(n):  # 循环 n 次，第 n 次弹出的堆顶就是答案
            x = heappop(q)  # 弹出当前最小的丑数
            for k in primes:  # 用每个质数分别生成新丑数
                if x <= mx // k:  # 用除法判断，保证 k * x 不会溢出
                    heappush(q, k * x)  # 生成新丑数并入堆
                if x % k == 0:  # x 能被当前质数整除，继续乘会产生重复
                    break  # 提前跳出内层循环，减少冗余入堆
        return x  # 第 n 次弹出的值就是答案
