# 3727. Maximum Alternating Sum of Squares（最大交替平方和）
# 核心思路：先把每个元素平方（非负），排序后让较小的前一半取负、较大的后一半取正，即可使交替和最大。
# 复杂度：时间 O(n log n)（排序），空间 O(n)（平方后生成新列表）。

class Solution:
    def maxAlternatingSum(self, nums: List[int]) -> int:  # 返回数组元素平方后能得到的最大交替和
        nums = [x * x for x in nums]  # 先把每个元素替换为它的平方
        nums.sort()  # 平方后升序排序，便于把小的放负号位、大的放正号位
        ans, m = 0, len(nums) >> 1  # ans 保存交替和，m 为元素个数的一半
        for i, x in enumerate(nums):  # 按下标遍历排序后的数组
            ans += -x if i < m else x  # 前一半（较小值）取负、后一半（较大值）取正，交替和最大
        return ans  # 返回最大交替和
