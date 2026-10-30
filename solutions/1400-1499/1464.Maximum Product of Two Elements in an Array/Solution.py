# 题目：1464. 数组中两元素的最大乘积（Maximum Product of Two Elements in an Array）
# 核心思路：枚举所有下标对 (i, j)，取 (nums[i] - 1) * (nums[j] - 1) 的最大值。
# 时间复杂度：O(n^2)，双重循环枚举所有配对；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def maxProduct(self, nums: List[int]) -> int:  # nums 是输入数组，返回两元素减一后的最大乘积
        ans = 0  # 记录目前找到的最大乘积；元素都 ≥ 1，初值 0 安全
        for i, a in enumerate(nums):  # 同时取得第一个元素的下标 i 与值 a
            for b in nums[i + 1 :]:  # 只遍历 i 之后的元素，保证不重复配对
                ans = max(ans, (a - 1) * (b - 1))  # 按题目公式计算并尝试更新答案
        return ans  # 返回最大乘积
