# 3584. 子序列首尾元素的最大乘积（Maximum Product of First and Last Elements of a Subsequence）
# 核心思路：枚举子序列末端下标，用滑动窗口维护可作首元素区间的最小值与最大值，分别与末端值相乘取最优。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(1)，其中 n 为数组长度。
class Solution:  # 定义题解类
    def maximumProduct(self, nums: List[int], m: int) -> int:  # 求长度为 m 的子序列首尾元素的最大乘积
        ans = mx = -inf  # 答案与首元素候选最大值初始化为负无穷
        mi = inf  # 首元素候选最小值初始化为正无穷
        for i in range(m - 1, len(nums)):  # 枚举子序列末端下标 i
            x = nums[i]  # 当前末端元素
            y = nums[i - m + 1]  # 当前新进入候选范围的首元素
            mi = min(mi, y)  # 更新候选最小值
            mx = max(mx, y)  # 更新候选最大值
            ans = max(ans, x * mi, x * mx)  # 末端为正时乘最大值，为负时乘最小值，取更优解
        return ans  # 返回最大乘积
