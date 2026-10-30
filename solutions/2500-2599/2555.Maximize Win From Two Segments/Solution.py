# 题目：2555. 两个线段获得的最多奖品（Maximize Win From Two Segments）
# 思路：DP + 二分。f[i] 表示只在前 i 个奖品中放一条线段能覆盖的最多奖品数；枚举第二条线段的右端点 i，用 bisect_left 求出它最左覆盖到的 j，答案为 f[j] + (i - j)。
# 时间复杂度：O(n log n)，每次枚举做一次二分；空间复杂度：O(n)，f 保存前缀最优。
class Solution:  # LeetCode 约定的题解类
    def maximizeWin(self, prizePositions: List[int], k: int) -> int:  # prizePositions 是递增的奖品坐标，k 是每条线段的长度
        n = len(prizePositions)  # n 是奖品个数
        f = [0] * (n + 1)  # f[i] 表示只在前 i 个奖品里放一条线段时能覆盖的最多奖品数
        ans = 0  # ans 记录两条线段一起最多能覆盖多少奖品
        for i, x in enumerate(prizePositions, 1):  # i 从 1 开始计数，x 是第 i 个奖品的坐标
            j = bisect_left(prizePositions, x - k)  # 二分找第一个坐标 >= x - k 的位置 j，[j, i) 这些奖品能被一条长 k 的线段覆盖
            ans = max(ans, f[j] + i - j)  # 前 j 个奖品里放第一条线段，[j, i) 放第二条，两者互不重叠
            f[i] = max(f[i - 1], i - j)  # 更新前缀最优：不用第 i 个奖品，或用覆盖 i - j 个奖品的这条线段
        return ans  # 返回最多能拿到的奖品数
