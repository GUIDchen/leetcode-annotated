# 题目：3316. 从原字符串里进行删除操作的最多次数（Find Maximum Removals From Source String）
# 核心思路：DP，f[i][j] 表示用 source 前 i 个字符匹配 pattern 前 j 个字符时最多能删掉的字符数：位置可删就删并得分 1，或者用当前字符去匹配 pattern。
# 时间复杂度：O(m·n)，m、n 为两个串长度；空间复杂度：O(m·n)。
class Solution:  # LeetCode 约定的题解类
    def maxRemovals(self, source: str, pattern: str, targetIndices: List[int]) -> int:  # source：原串；pattern：必须留下的子序列；targetIndices：允许删除的下标集合
        m, n = len(source), len(pattern)  # m、n 分别是两个串的长度
        f = [[-inf] * (n + 1) for _ in range(m + 1)]  # DP 表，-inf 表示不可达，避免不可达状态参与后面的 max
        f[0][0] = 0  # 空串匹配空串，删除次数为 0
        s = set(targetIndices)  # 转成集合，O(1) 判断某个下标是否允许删除
        for i, c in enumerate(source, 1):  # i 从 1 开始表示已处理 source 的前 i 个字符，c 是第 i 个字符
            for j in range(n + 1):  # j 表示当前已匹配的 pattern 前缀长度
                f[i][j] = f[i - 1][j] + int((i - 1) in s)  # 选择一：删掉 source[i-1]，可删则 +1（int(True) == 1），否则 +0
                if j and c == pattern[j - 1]:  # 选择二：当前字符可以匹配 pattern 的第 j 个字符
                    f[i][j] = max(f[i][j], f[i - 1][j - 1])  # 匹配不得分，与原删除方案取更大值
        return f[m][n]  # 全部处理完且 pattern 匹配完时的最大删除次数
