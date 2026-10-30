# 题目：1201. 丑数 III（Ugly Number III）
# 思路：二分答案——用容斥原理统计 ≤ mid 能被 a、b、c 整除的数的个数，找到第一个个数 ≥ n 的位置。
# 时间复杂度：O(log 2e9)，二分约 31 轮；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def nthUglyNumber(self, n: int, a: int, b: int, c: int) -> int:  # n 是目标序号，a、b、c 是三个除数，返回第 n 个丑数
        ab = lcm(a, b)  # ab 是 a 与 b 的最小公倍数，用于容斥去重
        bc = lcm(b, c)  # bc 是 b 与 c 的最小公倍数
        ac = lcm(a, c)  # ac 是 a 与 c 的最小公倍数
        abc = lcm(a, b, c)  # abc 是三者共同的最小公倍数
        l, r = 1, 2 * 10**9  # 二分区间：左端 1，右端 2*10**9 足够大
        while l < r:  # 二分：找第一个满足「丑数个数 ≥ n」的位置
            mid = (l + r) >> 1  # 取中点
            if (  # 容斥原理统计 ≤ mid 的丑数个数，判断是否已达到 n
                mid // a  # 能被 a 整除的个数
                + mid // b  # 加上能被 b 整除的个数
                + mid // c  # 加上能被 c 整除的个数
                - mid // ab  # 减去 ab 的公倍数，这是被重复统计的部分
                - mid // bc  # 减去 bc 的公倍数
                - mid // ac  # 减去 ac 的公倍数
                + mid // abc  # 三者公共部分被多减了，加回来
                >= n  # 个数达到 n，说明 mid 已经足够大
            ):  # 条件成立，答案在左半区间（含 mid）
                r = mid  # 把右端收缩到 mid
            else:  # mid 还不够大
                l = mid + 1  # 答案在右半区间，排除 mid
        return l  # l == r，这个位置就是第 n 个丑数
