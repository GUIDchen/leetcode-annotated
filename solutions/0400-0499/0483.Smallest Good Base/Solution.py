# 题目：483. 最小好进制（Smallest Good Base）
# 思路：若 num 在 k 进制下全为 1 且共 m+1 位，则 num = 1 + k + ... + k^m。位数越多进制越小，所以 m 从 63 递减到 2，每个 m 用二分求 k，第一个命中的即最小好进制。
# 时间复杂度：O(log²num)，外层最多 62 个位数，每个位数二分 O(log num) 次、每次求和 O(log num)；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def smallestGoodBase(self, n: str) -> str:  # n 是十进制字符串形式的目标值，返回最小好进制的字符串形式
        def cal(k, m):  # 内层辅助函数：算 1 + k + ... + k^m
            p = s = 1  # p 是当前的幂 k^0 = 1，s 是累加和（Python 整数不溢出，无需截断）
            for i in range(m):  # 一共再乘加 m 次，最终得到 m+1 项之和
                p *= k  # 幂乘上 k，得到下一项
                s += p  # 把这一项累加进总和
            return s  # 返回 1 + k + ... + k^m

        num = int(n)  # 转成整数，便于比较
        for m in range(63, 1, -1):  # 枚举位数相关的 m，从大到小；m 越大进制越小，先命中即最小
            l, r = 2, num - 1  # 进制下界为 2，上界为 num - 1
            while l < r:  # 二分查找最小的 k 使 cal(k, m) >= num
                mid = (l + r) >> 1  # 取中点
                if cal(mid, m) >= num:  # 当前值已经不小于 num
                    r = mid  # 答案在左半区间（含 mid）
                else:  # 否则
                    l = mid + 1  # 说明 mid 太小，答案在右半区间
            if cal(l, m) == num:  # 二分结束后 l == r，检查它是否恰好等于 num
                return str(l)  # 相等说明找到合法进制，转成字符串返回
        return str(num - 1)  # 兜底：两位全 1 时进制为 num - 1，一定成立
