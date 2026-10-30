# 题目：813. 最大平均值和的分组（Largest Sum of Averages）
# 思路：前缀和配合记忆化搜索，枚举第一段的分割点，把问题递归成「剩余元素分成 k-1 段」。
# 时间复杂度：O(k * n^2)；空间复杂度：O(k * n)，cache 保存全部状态。
class Solution:  # LeetCode 约定的题解类
    def largestSumOfAverages(self, nums: List[int], k: int) -> float:  # nums 为数组，k 为最多分成的段数
        @cache  # cache 装饰器让相同状态只计算一次
        def dfs(i: int, k: int) -> float:  # i 是当前起点，k 是还可以分成的段数
            if i == n:  # 没有元素剩余
                return 0  # 贡献为 0
            if k == 1:  # 只剩一段，剩余元素全部归为这一段
                return (s[n] - s[i]) / (n - i)  # 剩余区间的平均值
            ans = 0  # 当前最优值
            for j in range(i + 1, n):  # 枚举第一段的结束下标，区间左闭右开
                ans = max(ans, (s[j] - s[i]) / (j - i) + dfs(j, k - 1))  # 第一段平均值加上剩余部分分 k-1 段的最优值
            return ans  # 返回本状态的最优值

        n = len(nums)  # 数组长度与前缀和都在闭包定义之后才赋值，调用时按闭包捕获读取
        s = list(accumulate(nums, initial=0))  # 前缀和：s[i] 表示前 i 个元素之和
        return dfs(0, k)  # 从下标 0 开始分成 k 段
