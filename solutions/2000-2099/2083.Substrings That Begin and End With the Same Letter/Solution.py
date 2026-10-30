# 题目：2083. 求以相同字母开头和结尾的子串总数（Substrings That Begin and End With the Same Letter）
# 思路：顺序扫描并统计每个字母已出现的次数；当前字符与之前每个同字母位置都能配成一个合法子串，累加计数即可。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，计数器最多 26 个键。
class Solution:  # LeetCode 约定的题解类
    def numberOfSubstrings(self, s: str) -> int:  # s 为小写字母串，返回首尾字母相同的子串总数
        cnt = Counter()  # 计数器：记录每个字母到目前为止出现的次数
        ans = 0  # 累加子串总数，Python 整数不会溢出
        for c in s:  # 按顺序扫描字符串
            cnt[c] += 1  # 该字母出现次数加一
            ans += cnt[c]  # 它与之前每个同字母位置都能组成一个子串，故直接累加计数
        return ans  # 返回子串总数
