# 题目：2464. 有效分割中的最少子数组数目（Minimum Subarrays in a Valid Split）
# 核心思路：记忆化搜索。每一段必须首尾元素的最大公约数大于 1；dfs(i) 枚举以 nums[i] 开头的所有合法段尾 j，答案为 1 + dfs(j + 1) 的最小值，@cache 缓存重复状态。
# 时间复杂度：O(n^2 log V)，共 n 个状态、每个状态枚举 n 个段尾并做一次 gcd；空间复杂度：O(n)，缓存与递归深度。
class Solution:  # LeetCode 约定的题解类
    def validSubarraySplit(self, nums: List[int]) -> int:  # nums：待分割数组；返回最少子数组数目，无解返回 -1
        @cache  # 自动记忆化：同一个 i 只真正计算一次
        def dfs(i):  # 递归函数 dfs(i)：求后缀 nums[i..] 的最少分割段数
            if i >= n:  # 下标越界说明剩余元素为空
                return 0  # 空后缀不需要切分，段数为 0
            ans = inf  # 先假设当前后缀无法完成分割
            for j in range(i, n):  # 枚举这一段的最后一个位置 j；段非空，所以从 i 开始
                if gcd(nums[i], nums[j]) > 1:  # 合法段要求段首与段尾元素的最大公约数大于 1
                    ans = min(ans, 1 + dfs(j + 1))  # 当前这一段算 1 段，再加上剩余部分的最优解，取较小者
            return ans  # 返回当前后缀的最优值

        n = len(nums)  # 数组长度，dfs 以闭包方式读取它
        ans = dfs(0)  # 从下标 0 开始分割整个数组
        dfs.cache_clear()  # 主动清空缓存，避免缓存跨测试用例残留
        return ans if ans < inf else -1  # 仍是 inf 说明不存在合法分割，按题意返回 -1
