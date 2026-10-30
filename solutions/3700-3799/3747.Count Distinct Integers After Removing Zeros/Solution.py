# 题目：3747. 统计移除零后不同整数的数目（Count Distinct Integers After Removing Zeros）
# 核心思路：去掉所有零后得到的数必不含 0，且任何不含 0 的数 y 都能由 y 自身得到，所以 [1, n] 去零后的不同结果恰好是区间内不含数字 0 的整数；用数位 DP 按位枚举，统计不含 0 的正整数个数。
# 复杂度：时间 O(log n)，每个数位状态至多被计算一次；空间 O(log n)，记忆化缓存规模与上界位数成正比。
class Solution:  # LeetCode 约定的题解类
    def countDistinct(self, n: int) -> int:  # 返回 1..n 每个数去掉所有零后能得到的不同整数个数
        @cache  # 用 cache 记忆化：相同的数位状态只计算一次
        def dfs(i: int, zero: bool, lead: bool, lim: bool) -> int:  # i 为当前位，zero 表示已出现过数字 0，lead 表示仍在前导零，lim 表示是否贴着上界
            if i >= len(s):  # 已经填完全部数位
                return 1 if (not zero and not lead) else 0  # 已开始填数且没出现过 0，说明是不含 0 的正整数，计 1 个
            up = int(s[i]) if lim else 9  # 贴着上界时当前位最多取到 s[i]，否则可以取到 9
            ans = 0  # ans 累加当前位枚举出的所有后续方案数
            for j in range(up + 1):  # 枚举当前位填入的数字 j
                nxt_zero = zero or (j == 0 and not lead)  # 已经填过数却填入 0，就标记该数含有数字 0
                nxt_lead = lead and j == 0  # 一直填 0 才继续处于前导零阶段
                nxt_lim = lim and j == up  # 只有前缀一直紧贴上界，限制才会继续传递
                ans += dfs(i + 1, nxt_zero, nxt_lead, nxt_lim)  # 递归处理下一位，把子问题的方案数累加进来
            return ans  # 返回当前状态下的合法方案数

        s = str(n)  # 把上界 n 转成字符串，便于逐位枚举
        return dfs(0, False, True, True)  # 从最高位开始：尚未出现 0、处于前导零、贴着上界
