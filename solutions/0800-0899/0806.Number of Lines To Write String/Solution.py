# 题目：806. 写字符串需要的行数（Number of Lines To Write String）
# 思路：按顺序累加每个字母的宽度，放不下 100 就另起一行，并把该字母的宽度作为新行的已用宽度。
# 时间复杂度：O(n)，n 为字符串长度；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def numberOfLines(self, widths: List[int], s: str) -> List[int]:  # widths：a~z 每个字母的宽度；s：要写的字符串；返回 [行数, 最后一行宽度]
        lines, last = 1, 0  # lines：已用行数；last：当前行已用宽度
        for w in map(lambda c: widths[ord(c) - ord("a")], s):  # 先把每个字符映射成宽度，再逐个遍历
            if last + w <= 100:  # 本行还放得下
                last += w  # 直接累加宽度
            else:  # 放不下，需要换行
                lines += 1  # 另起一行
                last = w  # 新行的已用宽度就是这个字符的宽度
        return [lines, last]  # 返回 [行数, 最后一行宽度]
