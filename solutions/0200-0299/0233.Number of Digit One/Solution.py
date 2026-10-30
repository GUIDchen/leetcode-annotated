# 题目：233. 数字 1 的个数（Number of Digit One）
# 思路：数位 DP，从左往右逐位填数，状态为「第几位、已累计多少个 1、是否紧贴上界」，用 @cache 做记忆化。
# 时间复杂度：O(m²·10)，m 为 n 的十进制位数；空间复杂度：O(m²)，即缓存的状态数。
class Solution:  # LeetCode 约定的题解类
    def countDigitOne(self, n: int) -> int:  # n 是上界，返回 1..n 中数字 1 出现的总次数
        @cache  # 自动记忆化，等价于手写一个字典缓存，避免重复计算同一状态
        def dfs(i: int, cnt: int, limit: bool) -> int:  # 处理到第 i 位、前面已累计 cnt 个 1；limit 表示是否还紧贴 n 的上界
            if i >= len(s):  # 所有数位都填完了
                return cnt  # 返回这一条路径上累计的 1 的个数
            up = int(s[i]) if limit else 9  # 当前位能取的最大值：紧贴上界就取 s[i]，否则可以一路取到 9
            ans = 0  # 累计当前状态的方案数，初始为 0
            for j in range(up + 1):  # 枚举当前位所有合法取值
                ans += dfs(i + 1, cnt + (j == 1), limit and j == up)  # 往下一位递归：位数加一，若当前位填 1 则计数加一，只有顶上界时 limit 才继续为真
            return ans  # 返回当前状态的结果

        s = str(n)  # 转成字符串按位 DP；dfs 是闭包，运行时才读取这个变量
        return dfs(0, 0, True)  # 从最高位开始搜，初始 limit 为 True，表示紧贴 n 的上界
