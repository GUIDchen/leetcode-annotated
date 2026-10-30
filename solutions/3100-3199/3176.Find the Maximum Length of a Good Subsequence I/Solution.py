# 题目：3176. 求出最长好子序列 I（Find the Maximum Length of a Good Subsequence I）
# 思路：动态规划，f[i][h] 表示以 nums[i] 结尾、相邻不相等次数不超过 h 的最长好子序列长度，枚举前驱 j 做转移。
# 时间复杂度：O(n^2 k)，n 为数组长度；空间复杂度：O(n k)，即状态表 f 的大小。
class Solution:  # LeetCode 约定的题解类
    def maximumLength(self, nums: List[int], k: int) -> int:  # nums：输入数组；k：允许的相邻不相等次数上限
        n = len(nums)  # 记录数组长度，后面循环与建表都要用
        f = [[1] * (k + 1) for _ in range(n)]  # 状态表，全部初始化为 1：只取单个元素时长度即为 1
        ans = 0  # 记录全局最优答案
        for i, x in enumerate(nums):  # 枚举子序列的最后一个位置 i 及其值 x
            for h in range(k + 1):  # 枚举已使用的相邻不相等次数上限 h
                for j, y in enumerate(nums[:i]):  # 枚举前驱位置 j 及其值 y，只考虑 i 之前的元素
                    if x == y:  # 相邻元素相等，不消耗坏对额度
                        f[i][h] = max(f[i][h], f[j][h] + 1)  # 继承 j 处相同额度 h 的长度并加上当前元素
                    elif h:  # 相邻元素不相等，需要消耗一次坏对额度，且额度必须还有剩余
                        f[i][h] = max(f[i][h], f[j][h - 1] + 1)  # 从 j 处额度 h-1 的状态转移并加上当前元素
            ans = max(ans, f[i][k])  # 用「额度恰好用到上限 k」的状态更新答案
        return ans  # 返回最长好子序列的长度
