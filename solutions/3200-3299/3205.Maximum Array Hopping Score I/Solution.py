# 题目：3205. 最大数组跳跃得分 I（Maximum Array Hopping Score I）
# 思路：从下标 0 跳到末尾，每次跳跃得分 (j - i) * nums[j]；用记忆化 DFS 枚举所有落点并取最大值，@cache 缓存从 i 出发的最优解。
# 时间复杂度：O(n²)，每个状态枚举 O(n) 个落点；空间复杂度：O(n)，缓存与递归栈。
class Solution:  # LeetCode 题解类，固定入口名
    def maxScore(self, nums: List[int]) -> int:  # 返回从下标 0 跳到末尾的最大得分；nums 为跳跃数组
        @cache  # 为 dfs 自动加上记忆化，避免重复计算相同下标
        def dfs(i: int) -> int:  # 求从下标 i 出发能取得的最大得分
            return max(  # 在所有落点中取最大值；若已到末尾没有落点，则用 [0] 兜底
                [(j - i) * nums[j] + dfs(j) for j in range(i + 1, len(nums))] or [0]  # 枚举每个落点 j：得分 = (j - i) * nums[j] + 从 j 继续跳的最优得分
            )  # max 的参数列表结束

        return dfs(0)  # 从下标 0 出发求答案
