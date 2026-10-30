# 3461. 判断操作后字符串中的数字是否相等 I / Check If Digits Are Equal in String After Operations I
# 核心思路：按题意暴力模拟，每轮把相邻两位相加后对 10 取个位，长度减一直至只剩两位，再比较这两位。
# 复杂度：时间 O(n^2)，空间 O(n)。
class Solution:  # 定义题解类
    def hasSameDigits(self, s: str) -> bool:  # 判断反复相邻求和后最后剩下的两位是否相等
        t = list(map(int, s))  # 把字符串拆成整数列表，便于原地修改
        n = len(t)  # 当前列表长度
        for k in range(n - 1, 1, -1):  # 每轮长度减一，直到只剩两位
            for i in range(k):  # 遍历本轮需要计算的位置
                t[i] = (t[i] + t[i + 1]) % 10  # 相邻两位相加取个位，写回当前位置
        return t[0] == t[1]  # 仅剩两位，判断是否相等
