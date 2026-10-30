# 题目：1221. 分割平衡字符串（Split a String in Balanced Strings）
# 思路：贪心扫描，用计数器把 L 记 +1、R 记 -1，计数器归零处就是一段最短平衡子串的结束位置。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用计数变量。
class Solution:  # LeetCode 约定的题解类
    def balancedStringSplit(self, s: str) -> int:  # s：只由 L 和 R 组成的平衡字符串
        ans = l = 0  # ans：段数；l：当前这一段里 L 与 R 的数量差
        for c in s:  # 逐个字符扫描
            if c == 'L':  # 遇到 L，差值加一
                l += 1  # L 计数加一
            else:  # 否则就是 R
                l -= 1  # R 让差值减一
            if l == 0:  # 差值归零说明这一段已经平衡，贪心地在最短处切分可以拿到最多段数
                ans += 1  # 段数加一
        return ans  # 返回最多的平衡子串个数
