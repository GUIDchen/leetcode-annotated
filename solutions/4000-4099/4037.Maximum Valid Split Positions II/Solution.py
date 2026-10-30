# 题目：4037. 最多有效分割位置 II / Maximum Valid Split Positions II
# 核心思路：先算不删除时的答案，再用正序与倒序前缀 gcd 的变化位置筛出真正值得尝试的删除下标，从而避开全部下标的 O(n^2) 重算
# 复杂度：时间复杂度 O(n^2 log V)（候选下标大幅减少），空间复杂度 O(n)
class Solution:  # 定义 LeetCode 题解类
    def maxValidSplits(self, nums: List[int]) -> int:  # 最多允许删除一个元素，返回能得到的最大有效分割位置个数
        n = len(nums)  # 数组长度

        def calc(arr):  # 闭包：统计 arr 中满足前缀 gcd 等于后缀 gcd 的分割位置个数
            m = len(arr)  # 当前数组长度
            pre = [0] * m  # 前缀 gcd 数组
            suf = [0] * m  # 后缀 gcd 数组

            pre[0] = arr[0]  # 前缀 gcd 首项
            for i in range(1, m):  # 从左到右递推前缀 gcd
                pre[i] = gcd(pre[i - 1], arr[i])  # 前缀 gcd 等于上一项与当前元素求 gcd

            suf[-1] = arr[-1]  # 后缀 gcd 首项（最后一个元素）
            for i in range(m - 2, -1, -1):  # 从右到左递推后缀 gcd
                suf[i] = gcd(suf[i + 1], arr[i])  # 后缀 gcd 等于后一项与当前元素求 gcd

            ans = 0  # 有效分割位置计数
            for i in range(m - 1):  # 枚举分割点 i
                if pre[i] == suf[i + 1]:  # 左右两段 gcd 相等则为有效分割
                    ans += 1  # 计数加一

            return ans  # 返回有效分割位置个数

        def mark(arr):  # 闭包：标记前缀 gcd 首次发生变化的位置
            pos = [False] * n  # pos[i] 为真表示删掉 arr[i] 会改变前缀 gcd
            pos[0] = True  # 首个元素必然参与前缀 gcd
            g = arr[0]  # 当前前缀 gcd

            for i in range(1, n):  # 依次向前扩展前缀
                ng = gcd(g, arr[i])  # 加入 arr[i] 之后的新前缀 gcd
                pos[i] = ng != g  # gcd 变小说明该位置是关键位置
                g = ng  # 更新前缀 gcd

            return pos  # 返回标记数组

        pos1 = mark(nums)  # 正序数组的前缀 gcd 变化位置
        pos2 = mark(nums[::-1])  # 倒序数组的前缀 gcd 变化位置，用于从另一侧筛选关键删除点

        ans = calc(nums)  # 基准答案：不删除任何元素时的有效分割数

        for i in range(n):  # 枚举要删除的下标 i
            if pos1[i] or pos2[n - 1 - i]:  # 只有确实影响某一侧前缀 gcd 的删除点才可能改善答案
                arr = nums[:i] + nums[i + 1 :]  # 构造删除 nums[i] 之后的数组
                ans = max(ans, calc(arr))  # 用该方案的有效分割数更新答案

        return ans  # 返回最大有效分割位置个数
