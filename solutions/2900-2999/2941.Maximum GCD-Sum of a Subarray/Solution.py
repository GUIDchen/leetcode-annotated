# 题目：2941. 子数组的最大 GCD-Sum（Maximum GCD-Sum of a Subarray）
# 思路：枚举右端点，利用「终点固定时子数组的 gcd 只有 O(log V) 种」维护 (起点, gcd) 列表，长度达到 k 就更新答案。
# 时间复杂度：O(n log V log V)，每个右端点最多 O(log V) 个不同 gcd，每次求 gcd 为 O(log V)；空间复杂度：O(n)，前缀和与列表。
class Solution:  # LeetCode 约定的题解类
    def maxGcdSum(self, nums: List[int], k: int) -> int:  # nums：输入数组；k：子数组允许的最小长度
        s = list(accumulate(nums, initial=0))  # 前缀和：s[i] 表示 nums[0..i-1] 的元素之和（initial=0 保证有 s[0]）
        f = []  # f：以 i-1 结尾的 (起点, gcd) 列表，去重后不超过 O(log V) 项
        ans = 0  # ans：记录最大值，初始为 0
        for i, v in enumerate(nums):  # 枚举子数组的右端点 i，v 即 nums[i]
            g = []  # g：把右端点扩展到 i 之后的新列表
            for j, x in f:  # 继承所有以 i-1 结尾的区间
                y = gcd(x, v)  # 区间右端扩到 i 之后的新 gcd
                if not g or g[-1][1] != y:  # gcd 相同只保留最靠左（也就是最长）的那一项
                    g.append((j, y))  # 记录起点 j 与新的 gcd 值
            f = g  # 用新列表替换旧列表
            f.append((i, v))  # 补上只含 nums[i] 本身的区间
            for j, x in f:  # 枚举所有以 i 结尾的区间（每项代表一类相同 gcd）
                if i - j + 1 >= k:  # 区间长度至少为 k 才合法
                    ans = max(ans, (s[i + 1] - s[j]) * x)  # 区间和（前缀和相减）乘以 gcd，更新最大值
        return ans  # 返回最大的 gcd 与区间和之积
