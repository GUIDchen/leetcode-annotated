# 题目：926. 将字符串翻转到单调递增（Flip String to Monotone Increasing）
# 思路：枚举分界点，让前缀全为 0、后缀全为 1；代价 = 前缀 1 的个数 + 后缀 0 的个数，借助 0 的总数与前缀 0 计数 O(1) 算出。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minFlipsMonoIncr(self, s: str) -> int:  # s：只含 '0' 和 '1' 的字符串
        tot = s.count("0")  # 整串中 '0' 的总数，用于快速算后缀 0 的个数
        ans, cur = tot, 0  # ans 先取「全部翻成 1」的代价；cur 记录前缀中 '0' 的个数
        for i, c in enumerate(s, 1):  # enumerate 从 1 开始给出下标 i，表示前 i 个字符作为前缀
            cur += int(c == "0")  # 把 c 纳入前缀，若为 '0' 则前缀 0 计数加一（int 把布尔值转成 0/1）
            ans = min(ans, i - cur + tot - cur)  # 代价 = 前缀 1 的个数 (i-cur) + 后缀 0 的个数 (tot-cur)
        return ans  # 返回所有分界点中的最小代价
