# 题目：1012. 至少有 1 位重复的数字（Numbers With Repeated Digits）
# 思路：数位 DP + 状态压缩。用总数 n 减去「各位数字互不相同」的合法数字个数，mask 记录已用过的数字，递归时禁止重复。
# 时间复杂度：O(m * 2^10 * 10)，m 为 n 的十进制位数；空间复杂度：O(m * 2^10)，为缓存状态的数量。
class Solution:  # LeetCode 约定的题解类
    def numDupDigitsAtMostN(self, n: int) -> int:  # n：统计上界，返回 [1, n] 中至少有 1 位重复的数字个数
        @cache  # 记忆化装饰器：把 dfs 的结果按参数缓存起来，避免重复计算
        def dfs(i: int, mask: int, lead: bool, limit: bool) -> int:  # i 当前位数，mask 已用数字的位图，lead 是否仍处于前导零，limit 是否贴着上界
            if i >= len(s):  # 所有位都填完了，递归到底
                return lead ^ 1  # lead 为真说明整个数是 0，不计入；否则记 1 个合法数
            up = int(s[i]) if limit else 9  # 当前位的枚举上界：贴着上界取 s[i]，否则可以取到 9
            ans = 0  # 累计当前状态的合法方案数
            for j in range(up + 1):  # 枚举当前位填入的数字 j
                if lead and j == 0:  # 仍处在前导零阶段且填 0：这个数字还没有真正开始
                    ans += dfs(i + 1, mask, True, False)  # 继续保留前导零；填 0 后一定小于上界，limit 置 False
                elif mask >> j & 1 ^ 1:  # 数字 j 还没用过（mask 的第 j 位为 0）才允许填入
                    ans += dfs(i + 1, mask | 1 << j, False, limit and j == up)  # 把 j 记入已用集合，进入下一位；只有贴着上界时才可能继续受限
            return ans  # 返回当前状态的合法方案数

        s = str(n)  # 把上界转成字符串，供 dfs 按位取值（dfs 通过闭包读取 s）
        return n - dfs(0, 0, True, True)  # 用总数 n 减去「各位互不相同」的个数，得到至少有 1 位重复的数字个数
