# 题目：3179. K 秒后第 N 个元素的值（Find the N-th Value After K Seconds）
# 思路：数组初始全为 1，每秒把每个位置更新为「自身 + 前一个位置」的当前值；模拟 k 轮前缀和即可。
# 时间复杂度：O(n k)，每轮都要遍历一次数组；空间复杂度：O(n)，只保存一个长度为 n 的数组。
class Solution:  # LeetCode 约定的题解类
    def valueAfterKSeconds(self, n: int, k: int) -> int:  # n：数组长度；k：经过的秒数
        a = [1] * n  # 初始数组，每个元素都是 1
        mod = 10**9 + 7  # 题目要求结果对 1e9+7 取模，防止数值过大
        for _ in range(k):  # 逐秒模拟，每轮代表一次「同时更新全部元素」
            for i in range(1, n):  # 从左到右滚动更新；a[i-1] 此时已是本轮的累加结果
                a[i] = (a[i] + a[i - 1]) % mod  # 新值 = 自身 + 左邻元素，并立即取模
        return a[n - 1]  # 返回 k 秒后最后一个元素的值，即第 n 个元素
