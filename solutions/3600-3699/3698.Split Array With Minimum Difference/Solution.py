# 题目：3698. 分割数组得到最小绝对差（Split Array With Minimum Difference）
# 核心思路：accumulate 求前缀和；正序递推 f[i]（前缀是否严格递增）、逆序递推 g[i]（后缀是否严格递减）；最后枚举切点 i，在 f[i] 与 g[i+1] 同时成立时用两段区间和之差更新最小绝对差。
# 复杂度：时间 O(n)，两趟预处理加一趟枚举；空间 O(n)，存前缀和与两个标记数组。
class Solution:  # LeetCode 约定的题解类
    def splitArray(self, nums: List[int]) -> int:  # 返回把 nums 切成两段后两段和之差绝对值的最小值
        s = list(accumulate(nums))  # s[i] 表示 nums[0..i] 的前缀和
        n = len(nums)  # 数组长度
        f = [True] * n  # f[i]：前缀 nums[0..i] 是否严格递增
        for i in range(1, n):  # 从左到右递推前缀单调性
            f[i] = f[i - 1]  # 先继承前一位的单调性结论
            if nums[i] <= nums[i - 1]:  # 出现不严格递增（含相等）就破坏严格递增
                f[i] = False  # 标记该前缀不再严格递增
        g = [True] * n  # g[i]：后缀 nums[i..n-1] 是否严格递减
        for i in range(n - 2, -1, -1):  # 从右到左递推后缀单调性
            g[i] = g[i + 1]  # 先继承后一位的单调性结论
            if nums[i] <= nums[i + 1]:  # 出现不严格递减（含相等）就破坏严格递减
                g[i] = False  # 标记该后缀不再严格递减
        ans = inf  # 用无穷大作为「无解」哨兵
        for i in range(n - 1):  # 枚举切点 i：左段 nums[0..i]，右段 nums[i+1..]
            if f[i] and g[i + 1]:  # 左段严格递增且右段严格递减，该切点合法
                s1 = s[i]  # 左段区间和
                s2 = s[n - 1] - s[i]  # 右段区间和＝总和减去左段和
                ans = min(ans, abs(s1 - s2))  # 用当前切点的绝对差更新答案
        return ans if ans < inf else -1  # 有合法切点返回最小绝对差，否则返回 -1
