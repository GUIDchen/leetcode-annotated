# 题目：798. 得分最高的最小轮调（Smallest Rotation with Highest Score）
# 思路：元素 i 在轮调 k 次后落到 (i-k+n)%n，只有该位置 >= nums[i] 才得分，因此它只在环形区间 [i+1, n+i+1-v) 内贡献 1 分。用差分数组记录每个 k 的得分变化，再做前缀和取最大，即得最小 k。
# 时间复杂度：O(n)，一次差分构建加一次前缀和；空间复杂度：O(n)，差分数组。
class Solution:  # LeetCode 约定的题解类
    def bestRotation(self, nums: List[int]) -> int:  # nums：原始数组，返回得分最高的最小轮调次数
        n = len(nums)  # 数组长度
        mx, ans = -1, n  # mx 记录最高得分；ans 先置为 n，严格大于才更新所以天然取最小 k
        d = [0] * n  # 差分数组：d[k] 是第 k 次轮调相对 k-1 次的得分变化
        for i, v in enumerate(nums):  # 逐个元素计算它能得分的轮调次数区间
            l, r = (i + 1) % n, (n + i + 1 - v) % n  # 环形区间 [l, r)：起点是 i+1，长度取决于元素值 v
            d[l] += 1  # 区间起点处得分 +1
            d[r] -= 1  # 区间终点（开）处得分 -1
        s = 0  # 前缀和就是当前轮调的得分
        for k, t in enumerate(d):  # 按 k 从小到大还原差分
            s += t  # 累加差分，得到第 k 次轮调的总得分
            if s > mx:  # 严格大于才更新，保证保留最小的 k
                mx = s  # 更新最高得分
                ans = k  # 记录当前最优轮调次数
        return ans  # 返回得分最高且最小的轮调次数
