# 题目：3803. 统计残差前缀（Count Residue Prefixes）
# 思路：用集合维护每个前缀出现过的不同字符数，若其等于「前缀长度对 3 取余」就计数加一。
# 时间复杂度：O(n)，每个字符只插入一次；空间复杂度：O(1)，字符种类最多 26 种。
class Solution:  # LeetCode 约定的题解类
    def residuePrefixes(self, s: str) -> int:  # 统计有多少前缀的不同字符数恰好等于该前缀长度对 3 取余
        st = set()  # 记录当前前缀里出现过的字符
        ans = 0  # 满足条件的前缀个数
        for i, c in enumerate(s, 1):  # enumerate(s, 1)：i 取 1..n 表示前缀长度，c 是第 i 个字符
            st.add(c)  # 把它加入集合（重复则不变）
            if len(st) == i % 3:  # 不同字符数恰好等于前缀长度对 3 取余
                ans += 1  # 计数加一
        return ans  # 返回答案
