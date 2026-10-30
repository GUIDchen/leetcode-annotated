# 题目：2563. 统计公平数对的数目（Count the Number of Fair Pairs）
# 核心思路：排序后固定较小的下标 i，用两次二分在后缀中定位和落在 [lower, upper] 的右端点区间，区间长度即为贡献。
# 时间复杂度：O(n log n)，排序加 n 次二分；空间复杂度：O(1)，仅用常数个变量（排序为原地）。
class Solution:  # LeetCode 约定的题解类
    def countFairPairs(self, nums: List[int], lower: int, upper: int) -> int:  # nums：输入数组；lower/upper：和的下界与上界
        nums.sort()  # 原地升序排序，使后缀中「和」随下标单调不减
        ans = 0  # 公平数对总数
        for i, x in enumerate(nums):  # 枚举数对中较小的下标 i 与其值 x
            j = bisect_left(nums, lower - x, lo=i + 1)  # 只在下标 i 之后找第一个满足 x + nums[j] >= lower 的位置
            k = bisect_left(nums, upper - x + 1, lo=i + 1)  # 找第一个满足 x + nums[k] > upper 的位置（+1 实现闭区间的上界）
            ans += k - j  # 两者之间所有下标都是合法右端点，个数为 k - j
        return ans  # 返回公平数对总数
