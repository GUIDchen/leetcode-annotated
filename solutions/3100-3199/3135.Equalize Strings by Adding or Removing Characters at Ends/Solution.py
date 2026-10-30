# 题目：3135. 通过添加或删除结尾字符来同化字符串（Equalize Strings by Adding or Removing Characters at Ends）
# 思路：只能在串首/串尾增删字符，因此中间那段必须原样保留；求两串的最长公共子串长度 mx，其余字符全删全补，答案 m+n-2*mx。
# 时间复杂度：O(m*n)，两层 DP 填表；空间复杂度：O(m*n)，二维 DP 表。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, initial: str, target: str) -> int:  # initial 是起始串，target 是目标串，返回最少操作次数
        m, n = len(initial), len(target)  # 分别记录两个串的长度
        f = [[0] * (n + 1) for _ in range(m + 1)]  # f[i][j]：以 initial[i-1] 与 target[j-1] 结尾的最长公共子串长度
        mx = 0  # mx 记录全局最长公共子串长度
        for i, a in enumerate(initial, 1):  # 下标从 1 开始枚举 initial，同时取得当前字符 a
            for j, b in enumerate(target, 1):  # 内层同样从 1 开始枚举 target，取得当前字符 b
                if a == b:  # 两个字符相同，公共子串才能继续延长
                    f[i][j] = f[i - 1][j - 1] + 1  # 沿用左上角状态并接上当前这个字符
                    mx = max(mx, f[i][j])  # 用当前长度更新答案下界
        return m + n - mx * 2  # 保留公共子串，其余字符删掉或补齐，操作次数为 m+n-2*mx
