# 题目：1864. 构成交替字符串需要的最小交换次数（Minimum Number of Swaps to Make the Binary String Alternating）
# 思路：先判断 0 与 1 的个数之差是否超过 1；交替形态只由首字符决定，统计与目标形态不符的位置数，一次交换修正两个位置，故除以 2，两种形态取较小值。
# 时间复杂度：O(n)，常数次线性扫描；空间复杂度：O(1)，只用若干计数变量。
class Solution:  # LeetCode 约定的题解类
    def minSwaps(self, s: str) -> int:  # s：只含 '0' 和 '1' 的字符串
        def calc(c: int) -> int:  # 计算改成「第 i 位为 c ^ (i&1)」这种交替形态所需的最少交换次数
            return sum((c ^ i & 1) != x for i, x in enumerate(map(int, s))) // 2  # 逐位比较：与目标形态不同的位置数除以 2（一次交换修正两个错位）

        n0 = s.count("0")  # '0' 的个数
        n1 = len(s) - n0  # '1' 的个数 = 总长度 - '0' 的个数
        if abs(n0 - n1) > 1:  # 两种字符数量相差超过 1 时无法排成交替串
            return -1  # 返回 -1 表示不可行
        if n0 == n1:  # 数量相等时，首字符为 0 或 1 都合法，取两种形态的较小值
            return min(calc(0), calc(1))  # 返回两种形态中的最小值
        return calc(0 if n0 > n1 else 1)  # 数量不等时只有一种合法形态：多的那种字符占偶数下标，于是 c 为 0 或 1
