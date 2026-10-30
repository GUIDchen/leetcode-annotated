# 题目：2189. 建造纸牌屋的方法数（Number of Ways to Build House of Cards）
# 思路：第 k 层三角形要 3k+2 张牌且层数递增，用 @cache 记忆化 dfs(剩余牌数, 下一层编号)：摆下这一层或跳过它；恰好用完记一种方案。
# 时间复杂度：O(n²) 个状态、每个 O(1)；空间复杂度：O(n²)。
class Solution:  # LeetCode 约定的题解类
    def houseOfCards(self, n: int) -> int:  # n：可用纸牌总数
        @cache  # 记忆化：同一 (n, k) 状态只计算一次
        def dfs(n: int, k: int) -> int:  # n 剩余牌数，k 是下一层的层号
            x = 3 * k + 2  # 第 k 层三角形需要 3k+2 张牌
            if x > n:  # 剩余牌不够摆这一层
                return 0  # 这种摆法不成立
            if x == n:  # 恰好用完，是一种完整方案
                return 1  # 记一种方案
            return dfs(n - x, k + 1) + dfs(n, k + 1)  # 摆下这一层 / 跳过这一层，两种选择求和

        return dfs(n, 0)  # 从剩 n 张牌、第 0 层开始搜索
