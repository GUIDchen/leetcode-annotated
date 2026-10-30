# 题目：1151. 最少交换次数来组合所有的 1（Minimum Swaps to Group All 1's Together）
# 思路：最终连续 1 的窗口长度固定为 1 的总个数 k，滑动窗口统计窗口内 1 的最大个数 mx，答案就是 k - mx（窗口内 0 的个数）。
# 时间复杂度：O(n)，一次计数加一次滑动；空间复杂度：O(1)，只用常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def minSwaps(self, data: List[int]) -> int:  # data 只含 0 和 1
        k = data.count(1)  # 1 的总个数就是最终窗口长度 k
        mx = t = sum(data[:k])  # 第一个窗口内 1 的个数，同时作为当前最大值
        for i in range(k, len(data)):  # 窗口右移，遍历后续位置
            t += data[i]  # 纳入右端新元素
            t -= data[i - k]  # 移出左端旧元素
            mx = max(mx, t)  # 维护窗口内 1 的最大值
        return k - mx  # 窗口内 0 的个数就是最少交换次数
