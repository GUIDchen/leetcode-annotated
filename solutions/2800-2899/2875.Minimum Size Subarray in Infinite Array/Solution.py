# 题目：2875. 无限数组的最短子数组（Minimum Size Subarray in Infinite Array）
# 思路：先按整轮拆分 target，再用前缀和字典在「一轮内区间」及其补区间中取最短长度。
# 时间复杂度：O(n)，一轮只遍历一次；空间复杂度：O(n)，字典最多保存 n 个前缀和。
class Solution:  # LeetCode 约定的题解类
    def minSizeSubarray(self, nums: List[int], target: int) -> int:  # nums 是循环数组，target 是目标和
        s = sum(nums)  # 一轮的元素和
        n = len(nums)  # 一轮的长度
        a = 0  # a：完整轮贡献的长度
        if target > s:  # 目标超过一轮总和，可以整轮地取
            a = n * (target // s)  # 先拿走 target // s 个完整轮
            target -= target // s * s  # 把余数留在 target 里继续处理
        if target == s:  # 剩余目标正好等于一轮总和
            return n  # 一轮就是最短长度
        pos = {0: -1}  # 前缀和 → 最近下标，0 的虚拟下标取 -1
        pre = 0  # 当前前缀和
        b = inf  # b：不足一轮部分的最短长度，inf 表示还没找到
        for i, x in enumerate(nums):  # 遍历一轮内的每个位置 i 与元素值 x
            pre += x  # 累加到当前位置的前缀和
            if (t := pre - target) in pos:  # 海象运算符：先算出目标起点前缀 t，再看是否出现过
                b = min(b, i - pos[t])  # 区间长度是 i 减去起点下标，取更短者
            if (t := pre - (s - target)) in pos:  # 中间段和等于 s - target 时，答案取它的补段
                b = min(b, n - (i - pos[t]))  # 补段长度等于一轮长度减去中间段长度
            pos[pre] = i  # 记录当前前缀和最近一次出现的位置
        return -1 if b == inf else a + b  # 没更新过 b 说明凑不出，否则整轮长度加剩余长度
