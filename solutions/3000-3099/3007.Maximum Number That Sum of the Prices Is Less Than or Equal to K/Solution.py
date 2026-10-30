# 题目：3007. 价值和小于等于 K 的最大数字（Maximum Number That Sum of the Prices Is Less Than or Equal to K）
# 核心思路：价值和随数字单调不减，因此二分答案；用带缓存的数位 DP 快速算出 [0, num] 的价值总和，据此收缩二分区间。
# 时间复杂度：O(log² r)，二分 O(log r) 轮、每轮数位 DP 状态数 O(log² r)；空间复杂度：O(log² r)，缓存保存 DP 状态。
class Solution:  # LeetCode 约定的题解类
    def findMaximumNumber(self, k: int, x: int) -> int:  # k 是价值和上限，x 表示只统计位置为 x 倍数的二进制位
        @cache  # 给递归函数加缓存：相同的 (pos, limit, cnt) 直接复用结果
        def dfs(pos, limit, cnt):  # pos 为剩余位数，limit 表示是否贴着 num 的上界，cnt 为已累计价值
            if pos == 0:  # 位数用尽，这条路径的价值就是 cnt
                return cnt  # 返回路径价值
            ans = 0  # 累加各个分支带来的价值
            up = (self.num >> (pos - 1) & 1) if limit else 1  # 这一位能取的最大值：贴上限时取 num 的当前位，否则取 1
            for i in range(up + 1):  # 枚举这一位的所有可能取值
                ans += dfs(pos - 1, limit and i == up, cnt + (i == 1 and pos % x == 0))  # 该位取 1 且位置是 x 的倍数时价值加一，limit 也要向下传递
            return ans  # 返回 [0, num] 内所有数字的价值总和

        l, r = 1, 10**18  # 二分答案的左右边界
        while l < r:  # 二分寻找满足「价值和 <= k」的最大数字
            mid = (l + r + 1) >> 1  # 取上中位数，避免区间收缩时死循环
            self.num = mid  # 把当前二分的数写进实例属性，供 dfs 读取
            v = dfs(mid.bit_length(), True, 0)  # 计算价值总和，位数取 mid 的二进制长度
            dfs.cache_clear()  # 清空缓存，因为 num 变了之后缓存结果不再有效
            if v <= k:  # 价值总和不超过 k，答案至少是 mid
                l = mid  # 下界抬到 mid
            else:  # 否则答案一定更小
                r = mid - 1  # 上界降到 mid - 1
        return l  # 二分结束时 l == r，即为答案
