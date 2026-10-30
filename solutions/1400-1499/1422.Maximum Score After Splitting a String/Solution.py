# 题目：1422. 分割字符串的最大得分（Maximum Score After Splitting a String）
# 核心思路：先统计全串 1 的个数，再从左往右移动切点，增量维护左段 0 的个数与右段 1 的个数取最大值。
# 时间复杂度：O(n)，n 为字符串长度；空间复杂度：O(1)，只用几个标量。
class Solution:  # LeetCode 约定的题解类
    def maxScore(self, s: str) -> int:  # s：只含 "0" 和 "1" 的字符串
        l, r = 0, s.count("1")  # l：左段 0 的计数；r：右段 1 的计数（初始为全串 1 的个数）
        ans = 0  # 记录最大得分
        for x in s[:-1]:  # 逐个字符划入左段，最后一位必须留在右段
            l += int(x) ^ 1  # x 为 "0" 时异或 1 得 1，左段 0 的个数加一；为 "1" 则加 0
            r -= int(x)  # 该字符离开右段：它是 "1" 时右段 1 的个数减一
            ans = max(ans, l + r)  # 该切点得分 = 左段 0 的个数 + 右段 1 的个数，更新最大值
        return ans  # 返回最大得分
