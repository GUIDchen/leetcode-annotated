# 题目：2827. 范围中美丽整数的数目（Number of Beautiful Integers in the Range）
# 思路：数位 DP + 记忆化，dfs(pos, mod, diff, lead, limit) 统计「数字和模 k 为 0 且奇数位个数等于偶数位个数」的方案数，答案用前缀计数相减。
# 时间复杂度：O(位数 × k × 位数)，状态数约 位数×k×(2×位数) 且每位枚举 10 个数字；空间复杂度：O(位数 × k × 位数)，即缓存大小。
class Solution:  # LeetCode 约定的题解类
    def numberOfBeautifulIntegers(self, low: int, high: int, k: int) -> int:  # low/high：闭区间左右端点；k：数字和必须能被它整除；返回区间内美丽整数的个数
        @cache  # functools.cache 自动做记忆化，避免同一状态被重复搜索
        def dfs(pos: int, mod: int, diff: int, lead: int, limit: int) -> int:  # pos 当前位，mod 已选数字模 k 的余数，diff 奇偶个数差（偏移 10 避免负数），lead 是否仍处于前导零，limit 是否贴着上界
            if pos >= len(s):  # 递归终点：所有位都已经填完
                return mod == 0 and diff == 10  # 余数为 0 且奇偶个数相等（diff 回到偏移 10）时才返回真，Python 的 bool 可以直接参与下面的整数累加
            up = int(s[pos]) if limit else 9  # 当前位的取值上限：贴着上界就只能取到 s[pos]，否则可以取到 9
            ans = 0  # 统计当前状态下合法后缀的个数
            for i in range(up + 1):  # 枚举当前位放哪个数字
                if i == 0 and lead:  # 仍在前导零阶段：这一位不算真实数字
                    ans += dfs(pos + 1, mod, diff, 1, limit and i == up)  # 保持 lead 与余数、奇偶差不变，limit 取决于本位是否顶到上限
                else:  # 本位是真实数字，需要更新余数与奇偶差
                    nxt = diff + (1 if i % 2 == 1 else -1)  # 奇数让奇偶差 +1，偶数让奇偶差 -1
                    ans += dfs(pos + 1, (mod * 10 + i) % k, nxt, 0, limit and i == up)  # 进入下一位：余数按十进制左移一位后加上 i 再对 k 取模，lead 从此结束
            return ans  # 返回当前状态统计到的个数

        s = str(high)  # 把上界转成字符串，方便按位取数字（dfs 会闭包引用它）
        a = dfs(0, 0, 10, 1, 1)  # 统计 [0, high] 中的美丽整数个数：余数 0、奇偶差偏移 10、处于前导零且贴上界
        dfs.cache_clear()  # 清空缓存，下面把 s 换成 low - 1，旧结果不能复用
        s = str(low - 1)  # 换成 low - 1，用前缀计数相减得到区间答案
        b = dfs(0, 0, 10, 1, 1)  # 统计 [0, low-1] 中的美丽整数个数
        return a - b  # 区间 [low, high] 的答案等于两个前缀计数之差
