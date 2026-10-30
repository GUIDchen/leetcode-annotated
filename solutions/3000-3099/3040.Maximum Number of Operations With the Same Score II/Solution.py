# 题目：3040. 相同分数的最大操作数目 II（Maximum Number of Operations With the Same Score II）
# 思路：首次操作只有删首对、删尾对、删首尾三种可能，枚举这三种分数，用记忆化 DFS 求每种分数下最多还能删多少对。
# 时间复杂度：O(n²)，状态数即区间个数；空间复杂度：O(n²)，@cache 缓存每个区间的结果。
class Solution:  # LeetCode 约定的题解类
    def maxOperations(self, nums: List[int]) -> int:  # nums 是输入数组
        @cache  # 记忆化装饰器：相同参数 (i, j, s) 只真正计算一次
        def dfs(i: int, j: int, s: int) -> int:  # 在区间 nums[i..j] 上、固定分数为 s 时能继续操作的最大次数
            if j - i < 1:  # 区间内不足两个元素
                return 0  # 无法再操作，返回 0
            ans = 0  # 当前区间能继续操作的最大次数
            if nums[i] + nums[i + 1] == s:  # 方案一：删掉最左边两个元素
                ans = max(ans, 1 + dfs(i + 2, j, s))  # 本次算一次，区间左端点右移两位
            if nums[i] + nums[j] == s:  # 方案二：删掉最左与最右各一个元素
                ans = max(ans, 1 + dfs(i + 1, j - 1, s))  # 本次算一次，区间左右各收缩一位
            if nums[j - 1] + nums[j] == s:  # 方案三：删掉最右边两个元素
                ans = max(ans, 1 + dfs(i, j - 2, s))  # 本次算一次，区间右端点左移两位
            return ans  # 返回当前区间的最大操作数

        n = len(nums)  # 数组长度
        a = dfs(2, n - 1, nums[0] + nums[1])  # 情形一：首次删首两个，目标分数固定为它们之和
        b = dfs(0, n - 3, nums[-1] + nums[-2])  # 情形二：首次删尾两个，目标分数固定为它们之和
        c = dfs(1, n - 2, nums[0] + nums[-1])  # 情形三：首次删首尾各一个，目标分数固定为它们之和
        return 1 + max(a, b, c)  # 首次操作本身算一次，再加上三种情形中最优的后续次数
