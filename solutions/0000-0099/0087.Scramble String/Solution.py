# 题目：87. 扰乱字符串（Scramble String）
# 思路：记忆化搜索。dfs(i, j, k) 判断 s1 从 i 起、s2 从 j 起、长度均为 k 的两段是否互为扰乱串；枚举切分长度 h，分「不交换」和「交换」两种拼法递归。
# 时间复杂度：O(n^4)，状态 O(n^3) 个、每个状态枚举 O(n) 种切分；空间复杂度：O(n^3)，@cache 缓存的搜索结果。

class Solution:  # LeetCode 约定的题解类
    def isScramble(self, s1: str, s2: str) -> bool:  # 判断 s2 是否由 s1 通过反复交换子串得到
        @cache  # 自动记忆化：相同 (i, j, k) 只计算一次
        def dfs(i: int, j: int, k: int) -> bool:  # 判断 s1[i..i+k) 与 s2[j..j+k) 是否互为扰乱串
            if k == 1:  # 只剩一个字符，没有可切分的位置
                return s1[i] == s2[j]  # 单字符互为扰乱串当且仅当字符相同
            for h in range(1, k):  # 枚举左半段长度 h，把两段切成 h 与 k - h
                if dfs(i, j, h) and dfs(i + h, j + h, k - h):  # 第一种拼法：不交换，两半一一对应
                    return True  # 找到可行切分
                if dfs(i + h, j, k - h) and dfs(i, j + k - h, h):  # 第二种拼法：交换两半
                    return True  # 找到可行切分
            return False  # 所有切分方式都不行

        return dfs(0, 0, len(s1))  # 从两串起点、全长开始搜索
