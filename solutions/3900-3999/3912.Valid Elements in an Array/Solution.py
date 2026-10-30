# 3912. Valid Elements in an Array | 数组中的有效元素（简单）
# 核心思路：先倒序递推出后缀最大值 right[i] = max(nums[i..n-1])，再从左往右扫一遍，用 left 维护前缀最大值；某元素只要严格大于左侧所有元素或严格大于右侧所有元素（首尾元素天然满足一侧），就是有效元素。
# 复杂度：时间 O(n)，两趟线性扫描；空间 O(n)，后缀最大值数组。
class Solution:  # 定义题解类
    def findValidElements(self, nums: list[int]) -> list[int]:  # 返回数组中所有“有效元素”，保持原有相对顺序
        n = len(nums)  # 数组长度
        right = [nums[-1]] * n  # right[i] 表示 nums[i..n-1] 这一段的最大值，末位先置为 nums[-1]
        for i in range(n - 2, -1, -1):  # 从右往左递推后缀最大值
            right[i] = max(right[i + 1], nums[i])  # 等于右侧后缀最大值与当前元素的较大者
        left = 0  # left 维护 nums[0..i-1] 这一段的最大值，初值为 0
        ans = []  # 收集答案
        for i, x in enumerate(nums):  # 从左往右枚举每个元素及其下标
            if x > left or i == n - 1 or x > right[i + 1]:  # 大于左侧全部 或 已是末位 或 大于右侧全部，即为有效
                ans.append(x)  # 该元素有效，追加到答案末尾
            left = max(left, x)  # 把当前元素并入前缀最大值，供下一个元素使用
        return ans  # 返回所有有效元素
