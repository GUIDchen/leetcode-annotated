# 题目：2945. 找到最大非递减数组的长度（Find Maximum Non-decreasing Array Length）
# 思路：DP + 前缀和 + 二分。f[i] 是前 i 个元素能合并出的最大段数，pre[i] 记录取到该段数时最后一段的前驱位置；再用 bisect_left 求出哪些后继位置可以把 i 当作前驱，并用「前缀取最大」把前驱信息向后传播。
# 时间复杂度：O(n log n)，每轮一次二分；空间复杂度：O(n)，存放前缀和与两个 DP 数组。
class Solution:  # LeetCode 约定的题解类
    def findMaximumLength(self, nums: List[int]) -> int:  # nums 是待合并的数组，返回合并后非递减数组的最大长度
        n = len(nums)  # 数组长度
        s = list(accumulate(nums, initial=0))  # 构造前缀和，initial=0 让 s[i] 正好表示前 i 项之和
        f = [0] * (n + 1)  # f[i]：前 i 个元素能合并出的最大段数
        pre = [0] * (n + 2)  # pre[i]：f[i] 最优时最后一段的前驱位置；多留一格保证 j == n+1 时不越界
        for i in range(1, n + 1):  # 按前缀长度从小到大递推
            pre[i] = max(pre[i], pre[i - 1])  # 前缀最大值传播，保证前驱尽量靠后
            f[i] = f[pre[i]] + 1  # 在最优前驱的基础上再多切一段
            j = bisect_left(s, s[i] * 2 - s[pre[i]])  # 找出第一个前缀和使「下一段和不小于当前段」的位置 j
            pre[j] = i  # 登记 i 为 j 的前驱候选
        return f[n]  # 前 n 个元素的最大段数即答案
