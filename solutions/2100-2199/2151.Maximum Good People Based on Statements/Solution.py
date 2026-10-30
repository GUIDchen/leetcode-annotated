# 题目：2151. 基于陈述统计最多好人数（Maximum Good People Based on Statements）
# 思路：用二进制掩码枚举「谁是好人」的所有非空子集，只校验好人说出的话，与假设矛盾就排除，取人数最大值。
# 时间复杂度：O(2^n · n^2)，枚举 2^n 个子集、每个子集检查 n^2 条陈述；空间复杂度：O(n)，嵌套函数外的常数级辅助空间。
class Solution:  # LeetCode 约定的题解类
    def maximumGood(self, statements: List[List[int]]) -> int:  # statements[i][j]：i 对 j 的陈述；返回最多好人数
        def check(mask: int) -> int:  # 辅助函数：判断某个「好人集合」假设是否自洽，返回好人数，矛盾则返回 0
            cnt = 0  # 当前假设下的好人数
            for i, row in enumerate(statements):  # 遍历每个人 i 及其陈述行
                if mask >> i & 1:  # 第 i 位为 1：假设 i 是好人，其陈述必须全部为真
                    for j, x in enumerate(row):  # 遍历 i 对每个人 j 的评价 x
                        if x < 2 and (mask >> j & 1) != x:  # 有明确评价（0 或 1）且与假设不符
                            return 0  # 该假设矛盾，返回 0 表示排除
                    cnt += 1  # 本行陈述全部符合假设，好人数加一
            return cnt  # 返回该假设下的好人数

        return max(check(i) for i in range(1, 1 << len(statements)))  # 枚举所有非空子集（1 到 2^n-1），取最大好人数
