# 题目：2397. 被列覆盖的最多行数（Maximum Rows Covered by Columns）
# 思路：先把每行的 1 压缩成位掩码，再枚举所有恰好选中 numSelect 列的列掩码，统计被完全覆盖的行数并取最大值。
# 时间复杂度：O(2^n * m)，枚举 2^n 个列掩码、每个掩码检查 m 行；空间复杂度：O(m)，保存每行的位掩码。
class Solution:  # LeetCode 约定的题解类
    def maximumRows(self, matrix: List[List[int]], numSelect: int) -> int:  # matrix：0/1 矩阵；numSelect：必须选择的列数
        rows = []  # 保存每一行压缩后的位掩码
        for row in matrix:  # 逐行处理
            mask = reduce(or_, (1 << j for j, x in enumerate(row) if x), 0)  # 把该行所有值为 1 的列号对应的位或起来，初值为 0
            rows.append(mask)  # 收集这一行的位掩码

        ans = 0  # 记录被完全覆盖的最多行数
        for mask in range(1 << len(matrix[0])):  # 枚举所有列选择方案，mask 的第 j 位为 1 表示选中第 j 列
            if mask.bit_count() != numSelect:  # 选中的列数必须正好等于 numSelect
                continue  # 列数不符，跳过这个方案
            t = sum((x & mask) == x for x in rows)  # 行掩码是列掩码的子集时该行被完全覆盖，布尔值求和即为覆盖行数
            ans = max(ans, t)  # 用当前方案的行数更新最大值
        return ans  # 返回最多能被覆盖的行数
