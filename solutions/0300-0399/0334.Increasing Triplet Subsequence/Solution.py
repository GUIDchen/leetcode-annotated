# 题目：334. 递增的三元子序列（Increasing Triplet Subsequence）
# 核心思路：维护最小值 mi 与第二小值 mid，顺序扫描时一旦出现大于 mid 的数，就说明存在 i<j<k 的递增三元组。
# 时间复杂度：O(n)，只扫描一遍；空间复杂度：O(1)，只用了两个常数变量。
class Solution:  # LeetCode 约定的题解类
    def increasingTriplet(self, nums: List[int]) -> bool:  # nums 是输入数组，返回是否存在递增三元组
        mi, mid = inf, inf  # mi 是最小值，mid 是「前面已有更小元素」的第二小值；用 inf 表示尚未填值
        for num in nums:  # 从左到右遍历每个元素
            if num > mid:  # 当前值大于 mid，说明 mi < mid < num，三元组成立
                return True  # 找到递增三元组，返回 True
            if num <= mi:  # 当前值不超过最小值 mi
                mi = num  # 只能刷新最小值，mid 保持不变
            else:  # 否则当前值落在区间 (mi, mid] 内
                mid = num  # 刷新第二小值，为后面更大的元素做铺垫
        return False  # 遍历完仍未找到，返回 False
