# 题目：1608. 特殊数组的特征值（Special Array With X Elements Greater Than or Equal X）
# 思路：特征值只可能是 1..n，逐个枚举 x 并统计 ≥ x 的元素个数，相等就返回。
# 时间复杂度：O(n^2)，每个 x 都扫一遍数组；空间复杂度：O(1)。
class Solution:  # 题解类
    def specialArray(self, nums: List[int]) -> int:  # nums 为输入数组
        for x in range(1, len(nums) + 1):  # 特征值只可能在 1..n 之间，逐个尝试
            cnt = sum(v >= x for v in nums)  # 用生成器表达式求和，统计 ≥ x 的元素个数
            if cnt == x:  # 恰好有 x 个元素 ≥ x，即找到特征值
                return x  # 返回该特征值
        return -1  # 都不满足，返回 -1
