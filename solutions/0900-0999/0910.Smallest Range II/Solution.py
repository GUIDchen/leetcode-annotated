# 题目：910. 最小差值 II（Smallest Range II）
# 核心思路：排序后枚举分界点，分界点左边统一加 k、右边统一减 k；每种划分的极差只由两端的极值决定，取所有划分的最小值即可。
# 时间复杂度：O(n log n)，主要花在排序上；空间复杂度：O(1)，只用了常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def smallestRangeII(self, nums: List[int], k: int) -> int:  # nums：输入数组；k：每个元素只能加 k 或减 k 的固定幅度
        nums.sort()  # 原地升序排序：保证最优方案是「排序后的某个前缀加 k、后缀减 k」
        ans = nums[-1] - nums[0]  # 初始答案：全部同向加减时极差不变
        for i in range(1, len(nums)):  # 枚举分界点 i：nums[:i] 加 k，nums[i:] 减 k
            mi = min(nums[0] + k, nums[i] - k)  # 新最小值 = min(左段最小 nums[0]+k, 右段最小 nums[i]-k)
            mx = max(nums[i - 1] + k, nums[-1] - k)  # 新最大值 = max(左段最大 nums[i-1]+k, 右段最大 nums[-1]-k)
            ans = min(ans, mx - mi)  # 用当前划分的极差更新答案
        return ans  # 返回所有划分中的最小极差
