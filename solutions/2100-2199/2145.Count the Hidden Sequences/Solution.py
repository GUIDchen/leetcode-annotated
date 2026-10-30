# 题目：2145. 统计隐藏数组数目（Count the Hidden Sequences）
# 思路：隐藏数组各项等于首项加上差分前缀和，记录前缀和的极差即可算出首项的合法区间长度。
# 时间复杂度：O(n)，一次线性遍历；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def numberOfArrays(self, differences: List[int], lower: int, upper: int) -> int:  # differences 是差分数组，元素须落在 lower 与 upper 之间
        x = mi = mx = 0  # x：前缀和；mi/mx：前缀和的最小值与最大值，都从 0 开始
        for d in differences:  # 依次遍历每个差分值
            x += d  # 累加差分，得到下一个前缀和
            mi = min(mi, x)  # 维护前缀和最小值
            mx = max(mx, x)  # 维护前缀和最大值
        return max(upper - lower - (mx - mi) + 1, 0)  # 合法首项个数（区间长度），为负说明无解取 0
