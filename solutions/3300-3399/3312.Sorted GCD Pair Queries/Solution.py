# 题目：3312. 查询排序后的最大公约数（Sorted GCD Pair Queries）
# 思路：从大到小枚举 g，用「能被 g 整除的个数 v」算出 gcd 为 g 的倍数的数对总数 C(v,2)，减去更大倍数上已统计的数对即得 gcd 恰为 g 的个数；再做前缀和，用二分回答每个查询。
# 复杂度：时间 O(M log M + q log M)，M = max(nums)，枚举倍数是调和级数；空间 O(M)，计数数组与前缀和数组。
class Solution:  # LeetCode 约定的题解类
    def gcdValues(self, nums: List[int], queries: List[int]) -> List[int]:  # nums 为原数组，queries 为排序后两两 gcd 序列中的 0 起始下标
        mx = max(nums)  # 数组最大值，用于确定计数数组长度
        cnt = Counter(nums)  # 数值到出现次数的映射（不存在的键按 0 计）
        cnt_g = [0] * (mx + 1)  # cnt_g[g]：先存 gcd 恰为 g 的数对个数，之后改成前缀和
        for i in range(mx, 0, -1):  # 从大到小枚举 g，保证它的倍数都已算好
            v = 0  # v：nums 中能被 g 整除的元素个数
            for j in range(i, mx + 1, i):  # 枚举 g 的所有倍数 j
                v += cnt[j]  # 累加倍数 j 出现的次数
                cnt_g[i] -= cnt_g[j]  # 排除 gcd 恰为更大倍数 j 的那些数对
            cnt_g[i] += v * (v - 1) // 2  # 加上「gcd 是 g 的倍数」的数对总数 C(v, 2)
        s = list(accumulate(cnt_g))  # 前缀和：s[i] 表示 gcd <= i 的数对个数，长度与 cnt_g 相同
        return [bisect_right(s, q) for q in queries]  # 第一个前缀和大于 q 的下标，就是第 q 个（0 起始）gcd 的值
