# 题目：2842. 统计一个字符串的 k 子序列美丽值最大的数目（Count K-Subsequences of a String With Maximum Beauty）
# 思路：美丽值等于子序列中字符种数，故只选频次最大的 k 种字母；频次降序后对最后一个并列频次用组合数挑选，再乘各自频次。
# 时间复杂度：O(n + 26 log 26)，统计频次与排序为主，组合数与快速幂为对数级；空间复杂度：O(1)，只用 26 个字母的频次数组。
class Solution:  # LeetCode 约定的题解类
    def countKSubsequencesWithMaxBeauty(self, s: str, k: int) -> int:  # s 是原字符串，k 是子序列中要求的字符种数
        f = Counter(s)  # 每个字母在 s 中出现的次数
        if len(f) < k:  # 不同字母不足 k 种，凑不出长度为 k 的子序列
            return 0  # 方案数为 0
        mod = 10**9 + 7  # 结果需要对 1e9+7 取模
        vs = sorted(f.values(), reverse=True)  # 各字母频次从大到小排序，优先选频次高的字母
        val = vs[k - 1]  # 被选中的字母中频次最小的那个值，可能并列
        x = vs.count(val)  # 频次恰好等于 val 的字母个数
        ans = 1  # 方案数，用乘法逐步累积
        for v in vs:  # 处理频次严格大于 val 的字母
            if v == val:  # 遇到分界线上的频次就停止
                break  # 退出循环，剩下的交给组合数处理
            k -= 1  # 这类字母必须入选，待选名额减 1
            ans = ans * v % mod  # 每个字母可在各自频次个位置中任选一处贡献，累乘
        ans = ans * comb(x, k) * pow(val, k, mod) % mod  # 从 x 个并列字母中选 k 个，每个有 val 种位置选择，连乘取模
        return ans  # 返回美丽值最大的 k 子序列个数
