# 题目：171. Excel 表列序号（Excel Sheet Column Number）
# 思路：26 进制转换，逐位累加 ans = ans * 26 + 当前字母序号（A=1 … Z=26）。
# 时间复杂度：O(n)，n 为标题长度；空间复杂度：O(1)，只用一个累加变量。
class Solution:  # LeetCode 约定的题解类
    def titleToNumber(self, columnTitle: str) -> int:  # 把 Excel 列标题转换成对应的列序号
        ans = 0  # 结果：按 26 进制逐位累积
        for c in map(ord, columnTitle):  # 用 map(ord, ...) 把每个字符转成 ASCII 码后再遍历
            ans = ans * 26 + c - ord("A") + 1  # 左移一位（乘 26）再加当前字母的值：c - ord("A") + 1 使 A 记为 1
        return ans  # 返回最终列序号
