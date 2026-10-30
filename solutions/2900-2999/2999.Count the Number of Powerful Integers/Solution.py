# 题目：2999. 统计强大整数的数目（Count the Number of Powerful Integers）
# 思路：数位 DP。dfs(pos, lim) 统计 [1, t] 中「每个数位都不超过 limit 且以 s 结尾」的整数个数，答案 = dfs(finish) - dfs(start - 1)。
# 时间复杂度：O(位数 × 10)，每一位至多枚举 10 个数字；空间复杂度：O(位数)，记忆化缓存与递归栈。
class Solution:  # LeetCode 约定的题解类
    def numberOfPowerfulInt(self, start: int, finish: int, limit: int, s: str) -> int:  # start / finish：闭区间端点；limit：允许出现的最大数位；s：必须是该整数的后缀
        @cache  # 记忆化：相同的 (pos, lim) 只计算一次
        def dfs(pos: int, lim: int) -> int:  # 递归函数：统计不超过上界 t 的合法整数个数；pos 为当前位，lim 表示前缀是否仍紧贴上界
            if len(t) < n:  # 上界 t 的位数比后缀 s 还短，任何整数都不可能以 s 结尾
                return 0  # 无解，返回 0
            if len(t) - pos == n:  # 剩余待填位数正好等于后缀长度，剩下的位置只能原样放 s
                return int(s <= t[pos:]) if lim else 1  # 仍贴上界时比较 s 与 t 的剩余部分（等长，字典序等价于数值比较）；否则 s 一定可行
            up = min(int(t[pos]) if lim else 9, limit)  # 当前位可填的最大数字：贴上界时受 t[pos] 限制，且一律不超过 limit
            ans = 0  # 累计当前状态的方案数
            for i in range(up + 1):  # 枚举当前位的每一种取值
                ans += dfs(pos + 1, lim and i == int(t[pos]))  # 递归填下一位；lim and ... 保证只有持续贴上界才保持限制
            return ans  # 返回当前状态的方案数

        n = len(s)  # 后缀长度，供 dfs 内部使用（闭包引用）
        t = str(start - 1)  # 上界取 start - 1，用于前缀计数
        a = dfs(0, True)  # a = [1, start - 1] 内强大整数的个数
        dfs.cache_clear()  # 上界改变，先清空记忆化缓存
        t = str(finish)  # 把上界换成 finish
        b = dfs(0, True)  # b = [1, finish] 内强大整数的个数
        return b - a  # 两段前缀计数相减，得到 [start, finish] 的答案
