# 题目：1072. 按列翻转得到最大值等行数（Flip Columns For Maximum Number of Equal Rows）
# 思路：两行能同时变成相同行当且仅当它们完全相同或逐位互补；把首元素统一归一化为 0 后用计数器统计出现最多的模式。
# 时间复杂度：O(n · m)，逐行逐列扫一遍；空间复杂度：O(n · m)，计数器存归一化后的行元组。
class Solution:  # LeetCode 约定的题解类
    def maxEqualRowsAfterFlips(self, matrix: List[List[int]]) -> int:  # matrix：0/1 矩阵；返回若干次整列翻转后最多能有多少行完全相同
        cnt = Counter()  # 归一化行模式 → 出现次数
        for row in matrix:  # 逐行处理
            t = tuple(row) if row[0] == 0 else tuple(x ^ 1 for x in row)  # 首元素为 0 时保持原样；为 1 时逐位异或 1 取反，让互补的行归到同一模式
            cnt[t] += 1  # 该模式计数加一
        return max(cnt.values())  # 出现次数最多的模式对应的行数即答案
