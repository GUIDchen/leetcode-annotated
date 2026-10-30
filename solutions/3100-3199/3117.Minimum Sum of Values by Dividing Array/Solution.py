# 题目：3117. 划分数组得到最小的值之和（Minimum Sum of Values by Dividing Array）
# 思路：记忆化搜索 dfs(i, j, a)：前 i 个数已切成 j 段、当前段按位与为 a，每步可选「并入当前段」或「按位与达标后切段」。
# 时间复杂度：O(n·m·log V)，按位与只减不增使状态数受控；空间复杂度：O(n·m·log V)，cache 缓存所有状态。
class Solution:  # LeetCode 约定的题解类
    def minimumValueSum(self, nums: List[int], andValues: List[int]) -> int:  # nums：原数组；andValues：每个分组的目标按位与值
        @cache  # 记忆化装饰器：同一组参数只计算一次
        def dfs(i: int, j: int, a: int) -> int:  # dfs：前 i 个数已切成 j 段，当前段的按位与为 a
            if n - i < m - j:  # 剩余数字比还需要的段数少，不可能再分出足够多的组
                return inf  # 返回不可达
            if j == m:  # 所有分组都已切完
                return 0 if i == n else inf  # 恰好也用完所有数字才合法（代价 0），否则不可达
            a &= nums[i]  # 把当前数字并入当前段的按位与
            if a < andValues[j]:  # 按位与只会变小，已经比目标小就不可能再等于目标
                return inf  # 返回不可达
            ans = dfs(i + 1, j, a)  # 选择一：把 nums[i] 继续并入当前段，不切段
            if a == andValues[j]:  # 当前段按位与正好等于目标，可以在此处切段
                ans = min(ans, dfs(i + 1, j + 1, -1) + nums[i])  # 选择二：切段，并把 nums[i] 作为新一段的第一个元素
            return ans  # 返回两种选择中的较小值

        n, m = len(nums), len(andValues)  # 分别记录数组长度与目标分组数
        ans = dfs(0, 0, -1)  # 从下标 0、第 0 组、按位与初值 -1（全 1）开始搜索
        return ans if ans < inf else -1  # 搜不到可行划分时按题目要求返回 -1
