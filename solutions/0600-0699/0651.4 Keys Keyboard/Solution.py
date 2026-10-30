# 题目：651. 四个键的键盘（4 Keys Keyboard）
# 思路：动态规划。dp[i] 表示按 i 次键最多能得到的 A 数，枚举最后一次「全选 + 复制」的位置 j，之后的按键全部用来粘贴，故 dp[i] = max(dp[i], dp[j-1] * (i-j))。
# 时间复杂度：O(n^2)，两层循环；空间复杂度：O(n)，dp 数组。
class Solution:  # LeetCode 约定的题解类
    def maxA(self, n: int) -> int:  # n 是允许按下的按键次数，返回屏幕上最多能出现的 A 的个数
        dp = list(range(n + 1))  # 基线：全程只按 A 键，按 i 次得到 i 个 A
        for i in range(3, n + 1):  # 从按 3 次键开始才可能用上「全选 + 复制 + 粘贴」
            for j in range(2, i - 1):  # 枚举最后一次全选复制的位置 j，后面至少要留一次粘贴
                dp[i] = max(dp[i], dp[j - 1] * (i - j))  # j 处全选复制，之后每次粘贴都让 A 数翻倍
        return dp[-1]  # dp[n] 即按 n 次键能得到的最大 A 数
