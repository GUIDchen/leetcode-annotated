# 题目：4060. 统计偶好数（Count Evenly Good Integers）
# 思路：偶好数的定义只看“偶数数字有多少个”，因此用数位 DP 逐位填数：状态只需记住已填偶数数字个数的奇偶 st 和是否一直贴着上界 lim，填满所有位时 st 为偶数（st == 0）即为偶好数；对 dfs 做记忆化，区间答案再由 calc(r) - calc(l-1) 两个前缀答案相减得到。
# 时间复杂度：O(D × 2 × 2 × 10)，D 为十进制位数（不超过 16），每个状态枚举 10 个数字；空间复杂度：O(D × 2 × 2)，即记忆化数组的大小。
class Solution:  # LeetCode 约定的题解类
    def countEvenlyGoodIntegers(self, l: int, r: int) -> int:  # 返回 [l, r] 中“偶数数字个数为偶数”的整数个数
        @cache  # 缓存 dfs 的每个状态，避免同一个 (pos, st, lim) 重复枚举
        def dfs(pos: int, st: int, lim: bool) -> int:  # pos 为当前位，st 为已填偶数数字个数的奇偶，lim 表示前面是否一直贴着上界 s
            if pos >= len(s):  # 所有位都填完了
                return st ^ 1  # st 为 0 表示偶数数字个数是偶数；st ^ 1 把 0→1、1→0，正好直接当计数返回
            up = int(s[pos]) if lim else 9  # 贴着上界时当前位最多取 s[pos]，否则 0..9 随便填
            return sum(  # 枚举当前位所有合法数字并累加方案数
                dfs(pos + 1, (st + (i & 1 ^ 1)) % 2, lim and i == up)  # i 为偶数时 (i & 1) ^ 1 取 1，用来翻转偶数数字个数的奇偶；lim and i == up 维护上界标记
                for i in range(up + 1)  # 遍历 0 到 up
            )  # 求和结束（生成器跨行书写，故括号单独占一行）

        s = str(l - 1)  # 先算前缀 [0, l-1] 的答案（l 从 1 起，l-1 可能为 0）
        a = dfs(0, 0, True)  # 从最高位、偶数数字个数为 0、贴上界开始统计
        dfs.cache_clear()  # s 是闭包变量，换新的上界前必须清空缓存，否则会读到旧串的结果
        s = str(r)  # 再算前缀 [0, r] 的答案
        b = dfs(0, 0, True)  # 同样从最高位、初始状态、贴上界开始统计
        return b - a  # 区间答案 = 两个前缀答案之差
