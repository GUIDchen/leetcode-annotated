# 题目：13. 罗马数字转整数（Roman to Integer）
# 思路：用 pairwise 把字符串拆成相邻字符对，若左字符小于右字符则该位取负，否则取正；最后一位恒为正。
# 时间复杂度：O(n)，n 为字符串长度，一次线性扫描；空间复杂度：O(1)，字典只有 7 个固定键。
class Solution:  # LeetCode 约定的题解类
    def romanToInt(self, s: str) -> int:  # s 是合法的罗马数字字符串
        d = {'I': 1, 'V': 5, 'X': 10, 'L': 50, 'C': 100, 'D': 500, 'M': 1000}  # 字符 → 数值的查找字典
        return sum((-1 if d[a] < d[b] else 1) * d[a] for a, b in pairwise(s)) + d[s[-1]]  # pairwise 生成相邻字符对 (a, b)，左边小于右边则 a 取负；末位单独取正加上去
