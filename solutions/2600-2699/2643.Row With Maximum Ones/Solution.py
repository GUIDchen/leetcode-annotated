# 题目：2643. 一最多的行（Row With Maximum Ones）
# 思路：逐行用 sum 统计 1 的个数，只有严格大于当前最大值时才更新，因此并列时天然保留更小的行下标。
# 时间复杂度：O(m * n)，每个格子看一次；空间复杂度：O(1)，只保存行下标与 1 的个数。
class Solution:  # LeetCode 约定的题解类
    def rowAndMaximumOnes(self, mat: List[List[int]]) -> List[int]:  # mat 是只含 0/1 的 m 行 n 列矩阵
        ans = [0, 0]  # 答案格式为 [行下标, 该行 1 的个数]，初值 [0, 0]
        for i, row in enumerate(mat):  # 同时取得行下标 i 与本行内容 row
            cnt = sum(row)  # 本行求和，得到 1 的个数
            if ans[1] < cnt:  # 只有严格更大才更新，保证并列时保留最小行号
                ans = [i, cnt]  # 记录当前最优的行下标与个数
        return ans  # 返回 [行下标, 1 的个数]
