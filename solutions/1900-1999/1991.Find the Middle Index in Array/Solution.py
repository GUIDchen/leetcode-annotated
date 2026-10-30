# 题目：1991. 找到数组的中间位置（Find the Middle Index in Array）
# 思路：前缀和。先把总和放进右和 r，遍历时先从 r 中扣掉 x，此时 l 与 r 恰好是左右两侧元素和，相等即答案，否则把 x 并入 l。
# 时间复杂度：O(n)，只需一次遍历；空间复杂度：O(1)，只用了两个累加变量。
class Solution:  # LeetCode 约定的题解类
    def findMiddleIndex(self, nums: List[int]) -> int:  # nums：输入数组
        l, r = 0, sum(nums)  # l 是左侧元素和（初值 0）；r 初始化为总和，相当于 i 右侧元素和
        for i, x in enumerate(nums):  # 同时取得下标 i 与元素值 x
            r -= x  # 先从右和中扣掉 x，此时 r 恰好是 [i+1, n) 的元素和
            if l == r:  # 左右两侧之和相等，i 就是中间位置
                return i  # 立即返回该下标
            l += x  # 左侧多累加一个 x，交给下一轮比较
        return -1  # 全都不满足则不存在中间位置，返回 -1
