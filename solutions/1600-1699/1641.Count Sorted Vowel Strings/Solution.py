# 题目：1641. 统计字典序元音字符串的数目（Count Sorted Vowel Strings）
# 思路：@cache 记忆化搜索，dfs(i, j) 表示已选 i 个字符、下一个可用元音下标从 j 开始时的合法方案数，枚举下一个元音累加。
# 时间复杂度：O(n×5) 个状态、每个状态最多 5 次转移；空间复杂度：O(n×5) 的记忆化缓存。
class Solution:  # LeetCode 约定的题解类
    def countVowelStrings(self, n: int) -> int:  # n：目标字符串长度，返回长度为 n 的字典序元音字符串个数
        @cache  # @cache 自动记忆化，同一个 (i, j) 只会真正计算一次
        def dfs(i, j):  # dfs(i, j)：已选 i 个字符、下一个元音下标从 j 开始时的方案数
            return 1 if i >= n else sum(dfs(i + 1, k) for k in range(j, 5))  # 选满 n 个就返回 1 种；否则枚举下一个元音 k（k 从 j 到 4）并累加后缀方案数

        return dfs(0, 0)  # 从「一个字符都没选、下一个元音从 a 开始」出发
