# 题目：198. 打家劫舍（House Robber）
# 思路：记忆化搜索。dfs(i) 表示从第 i 间房开始能偷到的最大金额，偷第 i 间就跳到 i+2，不偷就看 i+1，取较大值。
# 时间复杂度：O(n)，每个下标只被真正计算一次；空间复杂度：O(n)，缓存表加上递归栈。
class Solution:  # LeetCode 约定的题解类
    def rob(self, nums: List[int]) -> int:  # nums：每间房的现金金额；返回最多能偷到的金额
        @cache  # functools.cache 把 dfs 的记忆化数组自动补齐，无需手写 -1 初始化
        def dfs(i: int) -> int:  # dfs(i)：从第 i 间房开始决策能偷到的最大金额
            if i >= len(nums):  # 越过最后一间房，已无房可偷
                return 0  # 金额为 0
            return max(nums[i] + dfs(i + 2), dfs(i + 1))  # 偷第 i 间则第 i+1 间不能碰，跳到 i+2；不偷则看 i+1；两者取较大值

        return dfs(0)  # 从第 0 间房开始决策
