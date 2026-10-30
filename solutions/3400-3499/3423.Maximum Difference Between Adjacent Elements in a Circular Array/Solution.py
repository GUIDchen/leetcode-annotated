# 3423. 循环数组中相邻元素的最大差值 / Maximum Difference Between Adjacent Elements in a Circular Array
# 核心思路：把首元素追加到末尾形成闭环，用 pairwise 枚举全部相邻对，取绝对差的最大值
# 复杂度：时间 O(n)，空间 O(n)（拼接出的新列表；若不复制则为 O(1)）
class Solution:  # 定义题解类
    def maxAdjacentDistance(self, nums: List[int]) -> int:  # 求循环数组中相邻元素绝对差的最大值
        return max(abs(a - b) for a, b in pairwise(nums + [nums[0]]))  # 拼接首元素形成闭环，再用 pairwise 遍历所有相邻对并取最大绝对差
