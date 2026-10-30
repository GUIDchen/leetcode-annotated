# 题目：2917. 找出数组中的 K-or 值（Find the K-or of an Array）
# 思路：按位统计，某一二进制位上为 1 的元素不少于 k 个，就把答案的该位置 1。
# 时间复杂度：O(32n)，逐位扫一遍数组；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def findKOr(self, nums: List[int], k: int) -> int:  # nums 是输入数组，k 是阈值；返回 K-or 值
        ans = 0  # 按位构造答案
        for i in range(32):  # 依次检查第 0 到第 31 个二进制位
            cnt = sum(x >> i & 1 for x in nums)  # 用生成器统计当前这一位上为 1 的元素个数
            if cnt >= k:  # 至少有 k 个数的第 i 位为 1
                ans |= 1 << i  # 把答案的第 i 位置为 1
        return ans  # 返回按位构造出的 K-or 值
