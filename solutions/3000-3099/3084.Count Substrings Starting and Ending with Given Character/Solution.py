# 题目：3084. 统计以给定字符开头和结尾的子字符串总数（Count Substrings Starting and Ending with Given Character）
# 思路：统计字符 c 出现次数 cnt，单字符子串有 cnt 个，任取两个 c 作为首尾又贡献 C(cnt,2) 个。
# 时间复杂度：O(n)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def countSubstrings(self, s: str, c: str) -> int:  # 统计以字符 c 开头且以字符 c 结尾的子字符串总数
        cnt = s.count(c)  # 字符 c 在 s 中出现的次数
        return cnt + cnt * (cnt - 1) // 2  # 单字符子串共 cnt 个，加上任选两个 c 组成的 C(cnt,2) 个
