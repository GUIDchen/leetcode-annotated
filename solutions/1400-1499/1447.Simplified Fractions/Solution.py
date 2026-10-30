# 题目：1447. 最简分数（Simplified Fractions）
# 核心思路：用列表推导式枚举所有 1 ≤ i < j ≤ n 的分数，保留满足 gcd(i, j) == 1 的最简分数。
# 时间复杂度：O(n^2 log n)，共 O(n^2) 对分数、每对做一次 gcd；空间复杂度：O(n^2) 存放答案。
class Solution:  # LeetCode 约定的题解类
    def simplifiedFractions(self, n: int) -> List[str]:  # 返回 0 到 1 之间（不含 0 和 1）、分母不超过 n 的所有最简分数
        return [  # 列表推导式开始，结果直接作为返回值
            f'{i}/{j}'  # 每个元素是 f-string 拼出的 "分子/分母"
            for i in range(1, n)  # 枚举分子 i，范围 1 到 n-1
            for j in range(i + 1, n + 1)  # 枚举分母 j，保证 j > i 且 j ≤ n
            if gcd(i, j) == 1  # 只有互质（最大公约数为 1）的分数才保留
        ]  # 列表推导式结束
