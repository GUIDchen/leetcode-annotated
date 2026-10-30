# 题目：2237. 计算街道上满足所需亮度的位置数量（Count Positions on Street With Required Brightness）
# 思路：差分数组。每盏灯把区间 [p-r, p+r] 截断到 [0, n-1] 后做端点 +1 / -1，再用 accumulate 求前缀和还原每个位置的灯数，逐点与 requirement 比较。
# 时间复杂度：O(n + m)，m 为灯的数量，每个位置、每盏灯各访问一次；空间复杂度：O(n)，差分数组长度为 n+1。
class Solution:  # LeetCode 约定的题解类
    def meetRequirement(  # n：街道位置数；lights：每盏灯的 [位置, 照明半径]；requirement：每个位置所需的最少灯数
        self, n: int, lights: List[List[int]], requirement: List[int]
    ) -> int:
        d = [0] * (n + 1)  # 差分数组：多开一位，让 d[n] 用来承接右端点之后的减一，避免越界
        for p, r in lights:  # 逐盏灯把它能照亮的区间累计到差分数组上
            i, j = max(0, p - r), min(n - 1, p + r)  # 覆盖区间左右端点，并截断到街道范围 [0, n-1] 内
            d[i] += 1  # 区间起点 +1：从这里开始灯数增加
            d[j + 1] -= 1  # 区间终点后一位 -1：从 j+1 开始灯数减少（j+1 最大为 n，不越界）
        # 前缀和长度是 n+1，zip 只取前 n 个，正好对应 n 个街道位置
        return sum(s >= r for s, r in zip(accumulate(d), requirement))  # accumulate 求前缀和得到每个位置的灯数；zip 把前缀和与要求逐点配对，统计满足要求的个数
