# 题目：3574. 最大子数组 GCD 分数 / Maximize Subarray GCD Score（困难）
# 核心思路：先统计每个元素的因子 2 个数 cnt[i]；枚举子数组左端点并向右扩展，用 gcd 维护区间 GCD，同时维护区间内最小因子 2 个数 mi 与取到该最小值的元素个数 t。翻倍一个元素等价于给它的因子 2 个数加一，因此只有把取到最小值的这 t 个元素全部翻倍才能让 GCD 再乘 2，条件是 t <= k；于是得分 = 长度 * (t <= k ? 2 * g : g)，枚举过程中取最大值。
# 复杂度：时间复杂度 O(n^2 log V)（V 为元素最大值），空间复杂度 O(n)。
class Solution:  # 定义题解类
    def maxGCDScore(self, nums: List[int], k: int) -> int:  # 返回最大子数组 GCD 分数，nums 为正整数数组，k 为最多翻倍次数
        n = len(nums)  # 数组长度
        cnt = [0] * n  # cnt[i] 记录 nums[i] 中因子 2 的个数
        for i, x in enumerate(nums):  # 预处理每个元素的因子 2 个数
            while x % 2 == 0:  # 不断除以 2，直到变成奇数
                cnt[i] += 1  # 因子 2 的个数加一
                x //= 2  # 去掉一个因子 2
        ans = 0  # 记录最大得分
        for l in range(n):  # 枚举子数组左端点 l
            g = 0  # 当前子数组的 GCD，0 与任意数取 gcd 仍是该数
            mi = inf  # 当前子数组中最小的因子 2 个数
            t = 0  # 取到最小因子 2 个数的元素个数
            for r in range(l, n):  # 枚举子数组右端点 r
                g = gcd(g, nums[r])  # 维护区间 GCD
                if cnt[r] < mi:  # 出现了更小的因子 2 个数
                    mi = cnt[r]  # 更新最小值
                    t = 1  # 目前只有当前元素取到最小值
                elif cnt[r] == mi:  # 与当前最小值相等
                    t += 1  # 取到最小值的元素个数加一
                ans = max(ans, (g if t > k else g * 2) * (r - l + 1))  # 得分 = GCD * 长度，最小值元素都能翻倍时 GCD 翻倍
        return ans  # 返回最大得分
