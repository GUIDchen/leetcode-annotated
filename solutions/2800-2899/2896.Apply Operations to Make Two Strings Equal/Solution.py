# 题目：2896. 执行操作使两个字符串相等（Apply Operations to Make Two Strings Equal）
# 思路：收集两个字符串所有不同的位置；区间 DP 枚举同时翻两端（代价 x）或成对消掉相邻两个位置（代价为下标差），取最小值。
# 时间复杂度：O(m^2)，m 为不同位置个数，每个区间只算一次；空间复杂度：O(m^2)，@cache 缓存的结果。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, s1: str, s2: str, x: int) -> int:  # s1、s2：两个等长字符串；x：一次操作同时翻转两个不同位置的代价
        @cache  # 记忆化装饰器：同一区间只计算一次
        def dfs(i: int, j: int) -> int:  # dfs(i, j)：处理不同位置列表 idx 的区间 [i, j]
            if i > j:  # 区间为空，说明这段已全部消完
                return 0  # 不需要代价
            a = dfs(i + 1, j - 1) + x  # 方案一：一次操作同时翻转两端位置，代价 x
            b = dfs(i + 2, j) + idx[i + 1] - idx[i]  # 方案二：从左端起相邻两个位置各翻一次，代价为它们的下标差
            c = dfs(i, j - 2) + idx[j] - idx[j - 1]  # 方案三：从右端起相邻两个位置各翻一次，代价为它们的下标差
            return min(a, b, c)  # 三种方案取最小值

        n = len(s1)  # n：字符串长度
        idx = [i for i in range(n) if s1[i] != s2[i]]  # 收集所有 s1 与 s2 不相同的下标
        m = len(idx)  # m：不同位置的总数
        if m & 1:  # 不同位置为奇数个，每次操作只能消掉 2 个，无法全部消掉
            return -1  # 无解
        return dfs(0, m - 1)  # 从整个区间开始求解
