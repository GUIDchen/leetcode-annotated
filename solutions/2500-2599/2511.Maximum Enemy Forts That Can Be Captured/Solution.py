# 题目：2511. 最多可以摧毁的敌人城堡数目（Maximum Enemy Forts That Can Be Captured）
# 思路：挑出相邻的一对非零位置，若它们一个是我方堡垒 1、一个是敌方堡垒 -1（相加为 0），中间的 0 有多少个就能占领多少个，取最大值。
# 时间复杂度：O(n)，i 单调跳到下一个非零位置，每个下标只被访问常数次；空间复杂度：O(1)，只用了几个整型变量。
class Solution:  # LeetCode 约定的题解类
    def captureForts(self, forts: List[int]) -> int:  # forts：1 我方城堡、-1 敌方城堡、0 空城
        n = len(forts)  # 数组长度
        i = ans = 0  # i：当前检查的位置；ans：最多能占领的空城数
        while i < n:  # 从左到右扫描
            j = i + 1  # j 用于找 i 之后第一个非零位置
            if forts[i]:  # 当前位置是城堡（非 0）才可能展开一段空城
                while j < n and forts[j] == 0:  # 跳过中间连续的 0
                    j += 1  # 继续向右寻找下一个城堡
                if j < n and forts[i] + forts[j] == 0:  # 右端有城堡且一为我方(1)、一为敌方(-1)
                    ans = max(ans, j - i - 1)  # 中间空城个数即可占领的敌人城堡数
            i = j  # 跳到下一个非零位置，跳过已经统计过的空城段
        return ans  # 返回最大可占领的空城数
