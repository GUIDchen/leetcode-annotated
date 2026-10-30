# 题目：464. 我能赢吗（Can I Win）
# 思路：状态压缩 + 记忆化搜索。mask 记录已被选走的数字，dfs(mask, s) 表示当前轮到的人能否必胜；mask 唯一决定 s。
# 时间复杂度：O(k·2^k)，k 为可选数字个数；空间复杂度：O(2^k)，缓存最多存 2^k 个状态。
class Solution:  # LeetCode 约定的题解类
    def canIWin(self, maxChoosableInteger: int, desiredTotal: int) -> bool:  # maxChoosableInteger：可选数字上界；desiredTotal：累计和达到即胜
        @cache  # 自动缓存 dfs 结果，避免重复搜索同一局面
        def dfs(mask: int, s: int) -> bool:  # mask 为已选数字位图，s 为当前累计和
            for i in range(1, maxChoosableInteger + 1):  # 枚举数字 1..maxChoosableInteger
                if mask >> i & 1 ^ 1:  # 第 i 位为 0 说明数字 i 还没被选走
                    if s + i >= desiredTotal or not dfs(mask | 1 << i, s + i):  # 本步直接达标，或走完后对手必败，则当前局面必胜
                        return True  # 记录必胜并返回
            return False  # 所有走法都让对手必胜，则当前局面必败

        if (1 + maxChoosableInteger) * maxChoosableInteger // 2 < desiredTotal:  # 全部数字之和都不足目标，先手不可能赢
            return False  # 直接返回 False
        return dfs(0, 0)  # 从「没有数字被选、累计和为 0」开局
