# 题目：4043. 恰好有 K 对相等相邻字符的循环移位数量（Count Rotations With Exactly K Equal Adjacent Pairs）
# 思路：滚动计数。先算出不移位时 n-1 对相邻字符中相等的对数 score，再把统计窗口沿原串右移：每移一步只需加上新进窗口的一对、减去移出窗口的一对，从而 O(1) 更新并统计 score 恰好等于 k 的移位个数。
# 复杂度：时间复杂度 O(n)，n 为字符串长度；空间复杂度 O(1)，只用了常数个计数变量。
class Solution:  # LeetCode 约定的题解类
    def countRotations(self, s: str, k: int) -> int:  # s：环形字符串；k：要求相等的相邻对数；返回满足条件的循环移位个数
        n = len(s)  # 字符串长度，也是循环移位的个数
        score = sum(a == b for a, b in pairwise(s))  # 不移位时相邻字符相等的对数（共 n-1 对）
        ans = int(score == k)  # 不移位这一种是否满足要求

        for i in range(n, n * 2 - 1):  # 窗口右移，枚举余下的 n-1 种移位
            score += int(s[i % n] == s[(i - 1) % n])  # 加上从右边新进入窗口的那一对是否相等
            score -= int(s[i % n] == s[(i + 1) % n])  # 减去从左边移出窗口的那一对
            ans += int(score == k)  # 当前移位满足条件则累加答案

        return ans  # 返回满足条件的循环移位总数
