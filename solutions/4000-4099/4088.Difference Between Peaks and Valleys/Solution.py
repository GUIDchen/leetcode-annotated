# 题目：4088. 峰值与谷值的差（Difference Between Peaks and Valleys）
# 核心思路：逐个检查非端点的中间元素，比左右邻居都大即为峰值（累加），比左右邻居都小即为谷值（累减），端点不参与判断。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用累加变量。
class Solution:  # LeetCode 约定的题解类
    def peakValleyDifference(self, nums: list[int]) -> int:  # nums：目标数组；返回所有峰值之和减去所有谷值之和
        ans = 0  # ans 累计「峰值之和 - 谷值之和」
        for i in range(1, len(nums) - 1):  # 只检查非端点的中间元素
            if nums[i - 1] < nums[i] > nums[i + 1]:  # 比左右邻居都大，说明是峰值
                ans += nums[i]  # 峰值计入答案（加）
            elif nums[i - 1] > nums[i] < nums[i + 1]:  # 比左右邻居都小，说明是谷值
                ans -= nums[i]  # 谷值从答案中扣除（减）
        return ans  # 返回峰值之和与谷值之和的差
