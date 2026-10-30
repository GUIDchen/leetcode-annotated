# 题目：2811. 判断是否能拆分数组（Check if it is Possible to Split Array）
# 思路：前缀和 + 记忆化搜索。dfs(i, j) 判断区间 nums[i..j] 能否被拆完：枚举切点 k，左段 [i, k] 与右段 [k + 1, j] 各自要么长度为 1、要么元素和达到 m，且两段内部都能继续拆，才说明整体可行。
# 时间复杂度：O(n^3)，共有 O(n^2) 个状态、每个状态枚举 O(n) 个切点；空间复杂度：O(n^2)，缓存与递归栈。
class Solution:  # LeetCode 约定的题解类
    def canSplitArray(self, nums: List[int], m: int) -> bool:  # nums：输入数组；m：每段的元素和阈值；返回能否拆完
        @cache  # cache 自动记忆化，相同 (i, j) 只真正计算一次
        def dfs(i: int, j: int) -> bool:  # dfs(i, j)：判断子数组 nums[i..j] 能否被拆完
            if i == j:  # 区间只剩一个元素时天然合法，这是递归出口
                return True  # 单元素段直接可行
            for k in range(i, j):  # 枚举切点 k，把 [i, j] 切成左段 [i, k] 与右段 [k + 1, j]
                a = k == i or s[k + 1] - s[i] >= m  # 左段长度为 1，或其元素和达到 m，都是合法的切出段
                b = k == j - 1 or s[j + 1] - s[k + 1] >= m  # 右段同理：长度为 1，或元素和达到 m
                if a and b and dfs(i, k) and dfs(k + 1, j):  # 左右两段都合法，且两段内部都能继续拆完
                    return True  # 一旦可行就立即返回 True
            return False  # 所有切点都失败，返回 False

        s = list(accumulate(nums, initial=0))  # 前缀和：initial=0 让 s[0] = 0，区间和写作 s[r + 1] - s[l]（dfs 内部闭包引用，调用前已就绪）
        return dfs(0, len(nums) - 1)  # 从整个数组 [0, n - 1] 开始判断
