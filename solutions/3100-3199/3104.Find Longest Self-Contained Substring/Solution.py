# 题目：3104. 查找最长的自包含子串（Find Longest Self-Contained Substring）
# 思路：先统计每个字母的首、末出现位置；以每个字母的首位置为左端点向右扩展，维护区间内最远末位置 mx，当 mx 恰好等于右端点 j 时区间自包含；长度等于 n 的整串不计，取最大值。
# 时间复杂度：O(26 * n) 即 O(n)，左端点最多 26 种；空间复杂度：O(26) 即 O(1)，只存首末位置字典。
class Solution:  # LeetCode 约定的题解类
    def maxSubstringLength(self, s: str) -> int:  # s：输入字符串；返回最长自包含子串长度，找不到返回 -1
        first, last = {}, {}  # 两个字典：字母 → 首次出现下标 / 末次出现下标
        for i, c in enumerate(s):  # 第一遍扫描：统计每个字母的首末位置
            if c not in first:  # 第一次遇到该字母
                first[c] = i  # 记录首次出现位置
            last[c] = i  # 每次遇到都刷新末次出现位置
        ans, n = -1, len(s)  # ans 存答案（初值 -1），n 是字符串长度
        for c, i in first.items():  # 枚举左端点所属字母：自包含子串左端一定是某字母的首次出现
            mx = last[c]  # 区间内最远末次出现位置的初值
            for j in range(i, n):  # 从 i 开始逐个尝试右端点
                a, b = first[s[j]], last[s[j]]  # 右端点字母的首、末出现位置
                if a < i:  # 该字母在 i 左边出现过，区间左侧漏了它
                    break  # 再扩展也不可能自包含，中断内层循环
                mx = max(mx, b)  # 合并当前字母的末位置，得到区间内最远末位置
                if mx == j and j - i + 1 < n:  # 恰好闭合，且长度小于 n（排除整串）
                    ans = max(ans, j - i + 1)  # 更新答案
        return ans  # 返回最长自包含子串长度
