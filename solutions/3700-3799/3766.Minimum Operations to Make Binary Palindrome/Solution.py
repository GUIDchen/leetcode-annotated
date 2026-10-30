# 3766. 将数字变成二进制回文数的最少操作 / Minimum Operations to Make Binary Palindrome
# 核心思路：预处理 14 位以内的所有二进制回文数并保持升序，对每个 x 二分查找左右相邻的两个回文数，取最近距离。
# 复杂度：时间 O(2^14 + n log 2^14)，空间 O(2^14)。
p = []  # 存放所有二进制回文数，天然升序
for i in range(1 << 14):  # 枚举 0..2^14-1
    s = bin(i)[2:]  # 去掉 “0b” 前缀得到二进制串
    if s == s[::-1]:  # 与自身反转相同即为回文
        p.append(i)  # 记录该回文数


class Solution:  # 定义解法类
    def minOperations(self, nums: List[int]) -> List[int]:  # 对每个元素求变成二进制回文数的最少操作数
        ans = []  # 结果列表
        for x in nums:  # 逐个处理每个数
            i = bisect_left(p, x)  # 二分找到第一个大于等于 x 的回文数下标
            times = inf  # 最少操作数先设为无穷大
            if i < len(p):  # 右侧存在候选回文数
                times = min(times, p[i] - x)  # 用右侧回文数更新答案
            if i >= 1:  # 左侧存在候选回文数
                times = min(times, x - p[i - 1])  # 用左侧回文数更新答案
            ans.append(times)  # 记录当前数的最少操作数
        return ans  # 返回结果
