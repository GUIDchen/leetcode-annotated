# 题目：2466. 统计构造好字符串的方案数（Count Ways To Build Good Strings）
# 核心思路：记忆化搜索统计方案数。dfs(i) 表示当前串长度为 i 时能补出的好字符串个数；若 i 已在 [low, high] 内，当前串自身算 1 种，再分别追加 zero 个 0 与 one 个 1 递归累加。
# 时间复杂度：O(high)，每个长度状态只计算一次；空间复杂度：O(high)，缓存与递归深度。
class Solution:  # LeetCode 约定的题解类
    def countGoodStrings(self, low: int, high: int, zero: int, one: int) -> int:  # low/high：合法长度区间；zero/one：每次追加的 0 与 1 的个数
        @cache  # 自动记忆化：同一个长度状态只真正计算一次
        def dfs(i):  # 递归函数 dfs(i)：当前串长度为 i 时，后续能构造出的好字符串个数
            if i > high:  # 长度超过上界
                return 0  # 非法路径，贡献 0 种方案
            ans = 0  # 累加器：从当前长度出发能得到的方案数
            if low <= i <= high:  # 当前长度已经落在合法区间内
                ans += 1  # 当前串本身就算一种好字符串
            ans += dfs(i + zero) + dfs(i + one)  # 追加 zero 个 '0' 或 one 个 '1'，两条分支的方案数相加
            return ans % mod  # 对大数取模，防止结果膨胀并符合题意

        mod = 10**9 + 7  # 取模常量；dfs 在调用时才查这个闭包变量，所以可以后定义
        return dfs(0)  # 空串长度为 0，从长度 0 开始构造
