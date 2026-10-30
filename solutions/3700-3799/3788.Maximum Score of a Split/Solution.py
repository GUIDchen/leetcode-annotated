# 题目：3788. 分割的最大得分（Maximum Score of a Split）
# 核心思路：先倒序预处理后缀最小值 suf[i]，再从左到右累加前缀和，在 i 处切分的得分为 pre - suf[i+1]，枚举所有切分点取最大值。
# 复杂度：时间 O(n)，后缀预处理与前缀扫描各一遍；空间 O(n)，后缀最小值数组。
class Solution:  # LeetCode 约定的题解类
    def maximumScore(self, nums: List[int]) -> int:  # 在 0 <= i < n-1 处切分，得分 = 前缀和 nums[0..i] 减去后缀最小值 nums[i+1..n-1]，求最大得分
        n = len(nums)  # 数组长度
        suf = [nums[-1]] * n  # suf[i] 表示 nums[i..n-1] 的最小值，先全部初始化为最后一个元素
        for i in range(n - 2, -1, -1):  # 从右往左递推后缀最小值
            suf[i] = min(nums[i], suf[i + 1])  # 后缀最小值 = min(当前元素, 右侧后缀最小值)
        ans = -inf  # 答案取负无穷，保证第一次比较一定被更新
        pre = 0  # pre 维护前缀和 nums[0..i]
        for i in range(n - 1):  # 枚举切分点 i，范围 0 到 n-2
            pre += nums[i]  # 把 nums[i] 累加进前缀和
            ans = max(ans, pre - suf[i + 1])  # 用「前缀和 - 后缀最小值」更新答案
        return ans  # 返回最大得分
