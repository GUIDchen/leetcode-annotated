# 题目：2575. 找出字符串的可整除数组（Find the Divisibility Array of a String）
# 思路：从高位到低位边读边取模，(余数 × 10 + 当前数字) % m 逐步递推，避免构造超大整数。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(n)，结果列表与字符串等长。
class Solution:  # LeetCode 约定的题解类
    def divisibilityArray(self, word: str, m: int) -> List[int]:  # word 是只含数字的字符串，m 是除数，返回每个前缀的可整除标记
        ans = []  # 收集每个前缀的结果
        x = 0  # x 保存当前前缀对 m 取模后的余数
        for c in word:  # 从最高位开始逐位处理
            x = (x * 10 + int(c)) % m  # 在余数末尾接上当前数字，再对 m 取模
            ans.append(1 if x == 0 else 0)  # 余数为 0 说明该前缀能被 m 整除
        return ans  # 返回结果列表
