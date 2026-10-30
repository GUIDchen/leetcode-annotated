# 题目：3098. 求出所有子序列的能量和（Find the Sum of Subsequence Powers）
# 思路：先排序让相邻元素之差成为最小差值候选，再用 @cache 记忆化搜索枚举长度恰为 k 的子序列，状态 (i, j, k, mi) 表示当前下标、上一个已选下标、还需选的个数与已选元素的最小差值。
# 时间复杂度：O(n^2·k)，状态数约为 n*n*k 量级且每个状态 O(1) 转移；空间复杂度：O(n^2·k)，即缓存占用的空间。
class Solution:  # LeetCode 约定的题解类
    def sumOfPowers(self, nums: List[int], k: int) -> int:  # nums：输入数组；k：子序列长度；返回所有长度恰为 k 的子序列能量之和对 1e9+7 取模
        @cache  # 装饰器：自动缓存 dfs 的返回值，实现记忆化搜索
        def dfs(i: int, j: int, k: int, mi: int) -> int:  # i 为当前下标、j 为上一个已选元素下标、k 为还需选的个数、mi 为已选元素的最小差值
            if i >= n:  # 所有元素都已尝试完毕，递归终止
                return mi if k == 0 else 0  # 恰好选满 k 个才有能量 mi，否则该方案贡献 0
            if n - i < k:  # 剩余元素不足以凑满 k 个，剪枝
                return 0  # 该分支不可能产生合法子序列
            ans = dfs(i + 1, j, k, mi)  # 不选 nums[i] 的方案：状态不变继续往后
            if j == n:  # j == n 表示还没有上一个元素，当前是第一个被选中的元素
                ans += dfs(i + 1, i, k - 1, mi)  # 把它作为首元素，最小差值保持 mi
            else:  # 已经有上一个元素，需要更新最小差值
                ans += dfs(i + 1, i, k - 1, min(mi, nums[i] - nums[j]))  # 选它并让最小差值取 min(旧值, 与上一个元素之差)
            ans %= mod  # 累加后立即取模，避免数值过大（mod 在闭包外定义，调用 dfs 时已存在）
            return ans  # 返回本状态的答案，@cache 会自动记住它

        mod = 10**9 + 7  # 题目要求的取模常量，先于 dfs 的首次调用完成定义
        n = len(nums)  # 数组长度，供递归边界与剪枝使用，同样是闭包变量
        nums.sort()  # 排序后相邻元素之差才能作为子序列最小差值的候选
        return dfs(0, n, k, inf)  # 从下标 0、没有上一个元素（记为 n）、还需 k 个、最小差值为 inf 开始搜索
