# 题目：2790. 长度递增组的最大数目（Maximum Number of Groups With Increasing Length）
# 思路：升序排序后原地累加，当前数字的剩余可用次数大于 k 就能多凑一组；把没用完的额度并给下一种数字继续使用。
# 时间复杂度：O(n log n)，瓶颈是排序；空间复杂度：O(1)，只做原地修改。
class Solution:  # LeetCode 约定的题解类
    def maxIncreasingGroups(self, usageLimits: List[int]) -> int:  # usageLimits[i] 表示数字 i 最多可以使用的次数
        usageLimits.sort()  # 升序排序，让可用次数少的数字先参与构造较短的组
        k, n = 0, len(usageLimits)  # k：已经构造出的组数；n：数字种类的数量
        for i in range(n):  # 依次遍历排序后的每种数字
            if usageLimits[i] > k:  # 当前数字还有剩余额度，能再支撑一个更长的组
                k += 1  # 组数加一
                usageLimits[i] -= k  # 扣掉新组对当前数字的消耗（第 k 组至少用 k 个）
            if i + 1 < n:  # 还有下一种数字时，把当前剩余的额度并过去
                usageLimits[i + 1] += usageLimits[i]  # 等价于把没用完的额度累积给后续数字继续使用
        return k  # 返回最多能构造的组数
