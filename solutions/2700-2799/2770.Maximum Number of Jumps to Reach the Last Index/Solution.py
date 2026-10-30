# 题目：2770. 达到末尾下标所需的最大跳跃次数（Maximum Number of Jumps to Reach the Last Index）
# 思路：记忆化 DFS，dfs(i) 表示从下标 i 跳到末尾所需的最大跳数；枚举满足 |nums[i] - nums[j]| <= target 的后继 j，取 1 + dfs(j) 的最大值。
# 时间复杂度：O(n^2)，n 个状态、每个状态枚举 O(n) 个后继；空间复杂度：O(n)，@cache 缓存与递归栈。
class Solution:  # LeetCode 约定的题解类
    def maximumJumps(self, nums: List[int], target: int) -> int:  # nums 是输入数组，target 是一次跳跃允许的最大差值
        @cache  # 缓存 dfs 的结果，同一状态只计算一次
        def dfs(i: int) -> int:  # dfs(i)：从下标 i 跳到末尾能得到的最大跳数
            if i == n - 1:  # 已经在末尾，不需要再跳
                return 0  # 剩余跳数为 0
            ans = -inf  # 用负无穷表示「从 i 暂时到不了末尾」
            for j in range(i + 1, n):  # 枚举所有可能的下一站（只能往右跳）
                if abs(nums[i] - nums[j]) <= target:  # 差值在允许范围内才是合法跳跃
                    ans = max(ans, 1 + dfs(j))  # 1 跳加上从 j 出发的最优解，取最大值
            return ans  # 返回从 i 出发的最大跳数（可能仍是 -inf）

        # 求长度后再从起点 0 开始搜索
        n = len(nums)  # 数组长度，dfs 内部需要用到
        ans = dfs(0)  # 从下标 0 开始跳
        return -1 if ans < 0 else ans  # 负数说明到不了末尾，按题目要求返回 -1
