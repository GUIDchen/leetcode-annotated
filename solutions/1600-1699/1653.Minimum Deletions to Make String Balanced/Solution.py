# 题目：1653. 使字符串平衡的最少删除次数（Minimum Deletions to Make String Balanced）
# 思路：动态规划：f[i] 表示让前 i 个字符平衡的最少删除数；遇到 b 直接继承并计数，遇到 a 取「删掉这个 a」与「删掉前面所有 b」的较小值。
# 时间复杂度：O(n)；空间复杂度：O(n)，一维 DP 数组。
class Solution:  # LeetCode 约定的题解类
    def minimumDeletions(self, s: str) -> int:  # s 只含 a、b，返回使其平衡的最少删除次数
        n = len(s)  # 字符串长度
        f = [0] * (n + 1)  # f[i]：前 i 个字符平衡的最少删除次数
        b = 0  # b：已扫描前缀中 b 的个数
        for i, c in enumerate(s, 1):  # i 从 1 开始，c 是当前字符
            if c == 'b':  # 遇到 b：排在所有 a 之前天然合法，状态继承
                f[i] = f[i - 1]  # 不需要删除任何字符
                b += 1  # b 的计数加一
            else:  # 否则遇到 a
                f[i] = min(f[i - 1] + 1, b)  # 取较小：删掉这个 a（f[i-1]+1）或删掉前面所有 b（b）
        return f[n]  # 整串的答案
