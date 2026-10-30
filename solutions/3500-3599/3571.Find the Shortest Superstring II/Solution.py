# 题目：3571. 最短超级串 II（Find the Shortest Superstring II）
# 思路：先保证 s1 是较短的串；若 s1 已是 s2 的子串，答案就是 s2；否则枚举重叠长度，分别检查 s1 的后缀与 s2 的前缀重叠、s1 的前缀与 s2 的后缀重叠，命中就省掉重叠部分拼接返回；都不成立则直接首尾相连。
# 时间复杂度：O(n^2)，枚举 O(n) 次、每次子串判断最多 O(n)；空间复杂度：O(n)，需要存放临时切片。
class Solution:  # LeetCode 约定的题解类
    def shortestSuperstring(self, s1: str, s2: str) -> str:  # s1、s2：待合并的两个字符串；返回同时包含两者的最短超级串
        m, n = len(s1), len(s2)  # 两个字符串的长度
        if m > n:  # 保证 s1 是较短的串，可缩小后面的枚举范围
            return self.shortestSuperstring(s2, s1)  # 交换参数后递归求解，答案不变
        if s1 in s2:  # s1 已经完整出现在 s2 中，无需再拼接
            return s2  # 答案就是 s2
        for i in range(m):  # 枚举切分位置 i，重叠长度为 m - i
            if s2.startswith(s1[i:]):  # s1 的后缀 s1[i:] 恰好等于 s2 的前缀
                return s1[:i] + s2  # 把 s1 未重叠的前缀拼在 s2 前面
            if s2.endswith(s1[: m - i]):  # s1 的前缀 s1[:m-i] 恰好等于 s2 的后缀
                return s2 + s1[m - i :]  # 把 s1 未重叠的后缀拼在 s2 后面
        return s1 + s2  # 没有任何重叠，直接首尾相连
