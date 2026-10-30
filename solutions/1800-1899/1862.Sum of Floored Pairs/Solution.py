# 题目：1862. 向下取整数对和（Sum of Floored Pairs）
# 思路：先用 Counter 做值域计数并求前缀和 s，再枚举分母 y 与商 d，用前缀和一次算出「除以 y 后商为 d」的分子个数，累加 个数 × d × cnt[y]。
# 时间复杂度：O(n + M log M)，M 为最大值（调和级数式枚举倍数）；空间复杂度：O(M)，存放前缀和数组。
class Solution:  # LeetCode 约定的题解类
    def sumOfFlooredPairs(self, nums: List[int]) -> int:  # nums：待统计的整数数组
        mod = 10**9 + 7  # 题目要求的结果对 1e9+7 取模
        cnt = Counter(nums)  # 值域计数：cnt[y] 是数值 y 出现的次数，缺失的键自动为 0
        mx = max(nums)  # 最大值：决定循环上界
        s = [0] * (mx + 1)  # s[x] 将存放数值不超过 x 的元素个数（前缀和）
        for i in range(1, mx + 1):  # 从小到大构造前缀和
            s[i] = s[i - 1] + cnt[i]  # 前缀和递推：前一个前缀和加上数值 i 的出现次数
        ans = 0  # 答案累加器
        for y in range(1, mx + 1):  # 枚举分母 y
            if cnt[y]:  # 分母值没出现过就跳过
                d = 1  # 商 d 从 1 开始枚举
                while d * y <= mx:  # 只要 d*y 不超过最大值，这一档就有贡献
                    ans += cnt[y] * d * (s[min(mx, d * y + y - 1)] - s[d * y - 1])  # 分子落在 [d*y, d*y+y-1] 的个数 × 商 d × 分母个数
                    ans %= mod  # 每步取模，防止数值膨胀
                    d += 1  # 枚举下一档商
        return ans  # 返回取模后的答案
