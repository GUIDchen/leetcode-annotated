# 3723. Maximize Sum of Squares of Digits（数位平方和的最大值）
# 核心思路：要让各位平方和最大，应让数字尽量“集中”——先用尽可能多的 9 填满（k = sum/9 个），再放余数位，最后用 0 补齐到 num 位。
# 复杂度：时间 O(num)，空间 O(num)（构造结果串）。

class Solution:
    def maxSumOfSquares(self, num: int, sum: int) -> str:  # 返回各位数字平方和最大、位数为 num、数字和恰为 sum 的数字串；无解返回空串
        if num * 9 < sum:  # 即使每一位都取 9，数字和也不够 sum，说明无解
            return ""  # 无解，返回空串
        k, s = divmod(sum, 9)  # 尽量多地使用 9：k 个 9，余数为 s
        ans = "9" * k  # 先用 k 个 '9' 铺满高位
        if s:  # 还有余数位需要放置
            ans += str(s)  # 把余数位接在 9 之后，集中数字才能最大化平方和
        ans += "0" * (num - len(ans))  # 剩余位数用 '0' 补齐，使总位数恰好为 num
        return ans  # 返回构造出的数字串
