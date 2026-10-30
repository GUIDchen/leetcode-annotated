# 题目：2712. 使所有字符相等的最小成本（Minimum Cost to Make All Characters Equal）
# 思路：相邻字符不同处必须被翻转覆盖；翻转前 i 个成本 i，翻转后 n-i 个成本 n-i，逐处累加较小值。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minimumCost(self, s: str) -> int:  # s：只含 '0' 和 '1' 的字符串，返回使其全部相等的最小成本
        ans, n = 0, len(s)  # ans 累计成本，n 为字符串长度，一次赋值同时初始化
        for i in range(1, n):  # 从下标 1 开始，逐个检查相邻字符对
            if s[i] != s[i - 1]:  # 相邻字符不同，这条缝隙必须被某次翻转跨过
                ans += min(i, n - i)  # 翻转前 i 个花 i，翻转后 n-i 个花 n-i，取较小值累加
        return ans  # 返回最小总成本
