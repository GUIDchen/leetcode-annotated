# 3791. 给定范围内平衡整数的数目 / Number of Balanced Integers in a Range
# 核心思路：数位 DP，dfs(pos, diff, lim) 统计偶数位数字和减奇数位数字和为 0 的填法，用 cache 记忆化后做前缀和差分。
# 复杂度：时间 O(位数 × 差值范围 × 10)，空间 O(位数 × 差值范围)。
class Solution:  # 定义 LeetCode 题解类
    def countBalanced(self, low: int, high: int) -> int:  # 统计区间 [low, high] 内平衡整数的个数
        @cache  # 用缓存做记忆化
        def dfs(pos: int, diff: int, lim: int) -> int:  # 填到第 pos 位，diff 为偶数位和减奇数位和，lim 表示是否贴着上界
            if pos >= len(num):  # 所有数位已经填完
                return 1 if diff == 0 else 0  # 差值为 0 才计入答案
            res = 0  # 当前状态的方案数
            up = int(num[pos]) if lim else 9  # 当前位可填的上限：贴住上界时取 num[pos]，否则为 9
            for i in range(up + 1):  # 枚举当前位填入的数字
                res += dfs(  # 累加下一位递归得到的方案数
                    pos + 1, diff + i * (1 if pos % 2 == 0 else -1), lim and i == up  # 下标偶数对应题目奇数位取正号，否则取负号；同时更新上界限制
                )  # 结束递归调用
            return res  # 返回方案数

        if high < 11:  # 平衡数至少两位，high 小于 11 时无平衡数
            return 0  # 直接返回 0
        low = max(low, 11)  # 把下界抬到最小的两位数 11
        num = str(low - 1)  # 先计算前缀 [1, low-1]
        a = dfs(0, 0, True)  # 上界为 low-1 时的平衡数个数
        dfs.cache_clear()  # 清空缓存，供第二个上界重新计算
        num = str(high)  # 再计算前缀 [1, high]
        b = dfs(0, 0, True)  # 上界为 high 时的平衡数个数
        return b - a  # 两前缀之差即为区间答案
