# 题目：2719. 统计整数数目（Count of Integers）
# 思路：数位 DP 求前缀和，答案 = f(num2) - f(num1 - 1)；dfs(pos, 数位和, 是否贴上界) 配合 @cache 记忆化。
# 时间复杂度：O(位数 × max_sum × 10)；空间复杂度：O(位数 × max_sum)。
class Solution:  # LeetCode 约定的题解类
    def count(self, num1: str, num2: str, min_sum: int, max_sum: int) -> int:  # 返回 [num1, num2] 内数位和落在 [min_sum, max_sum] 的整数个数
        @cache  # functools.cache 自动按参数缓存 dfs 结果，等价于手写记忆化数组
        def dfs(pos: int, s: int, limit: bool) -> int:  # pos 当前位，s 已累计的数位和，limit 表示前缀是否紧贴上界
            if pos >= len(num):  # 递归出口：num 的所有位都已经填完
                return int(min_sum <= s <= max_sum)  # 数位和落在区间内返回 1，否则返回 0
            up = int(num[pos]) if limit else 9  # 当前位能填的最大数字：贴上界时不超过 num 的对应位，否则可取 9
            # 枚举当前位所有取值，把下一层方案数累加后对 mod 取模（外层括号只用于折行）
            return (
                sum(dfs(pos + 1, s + i, limit and i == up) for i in range(up + 1)) % mod  # 递归下一位；limit 仅在前缀一直贴上界且当前位取到上界时才保持为真
            )

        mod = 10**9 + 7  # 取模常量（dfs 内部闭包引用它）
        num = num2  # 先以上界 num2 作为数位 DP 的数字串
        a = dfs(0, 0, True)  # 统计 0..num2 中的合法个数
        dfs.cache_clear()  # 清空缓存，准备换下界重新计算
        num = str(int(num1) - 1)  # 把下界减一，这样相减后正好得到 [num1, num2] 区间的答案
        b = dfs(0, 0, True)  # 统计 0..(num1-1) 中的合法个数
        return (a - b) % mod  # 前缀和相减得到答案，Python 的 % 会自动把负数修正为非负
