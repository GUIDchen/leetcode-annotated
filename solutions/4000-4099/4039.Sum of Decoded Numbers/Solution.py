# 题目：4039. 解码值之和 / Sum of Decoded Numbers
# 核心思路：把每个编码值拆成底数部分与最后一位的切分位置，切片得到底数与指数后，用内置 pow 的三参快速幂求值并累加取模
# 复杂度：时间复杂度 O(n log y)，空间复杂度 O(log v)
class Solution:  # 定义 LeetCode 题解类
    def sumDecoded(self, nums: List[int]) -> int:  # 对每个编码值解码后求幂，返回所有结果之和取模的值
        mod = 10**9 + 7  # 取模常量
        ans = 0  # 答案累加器
        for v in nums:  # 逐个处理编码值 v
            d, w = divmod(v, 10)  # 把 v 拆成底数部分 d 与最后一位切分位置 w
            s = str(d)  # 底数部分转成字符串，便于切片
            x = int(s[:w])  # 前 w 位作为底数 x
            y = int(s[w:])  # 剩余位作为指数 y
            ans = (ans + pow(x, y, mod)) % mod  # 把 x 的 y 次幂对 mod 取模后累加到答案
        return ans  # 返回解码值之和对 mod 取模的结果
