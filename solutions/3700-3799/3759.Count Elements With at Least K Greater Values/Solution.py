# 3759. 统计合格元素的数目（Count Elements With at Least K Greater Values）
# 核心思路：排序后，下标 i 处的元素后面至少有 k 个更大值，当且仅当 nums[n-k] > nums[i]；只需统计前 n-k 个位置中满足该不等式的个数。
# 复杂度：时间 O(n log n)（排序），空间 O(1)（不计排序栈）。
class Solution:  # 定义解法类
    def countElements(self, nums: List[int], k: int) -> int:  # 接口：统计至少有 k 个更大值的元素个数
        n = len(nums)  # n 为数组长度
        if k == 0:  # k 为 0 时任何元素都满足条件
            return n  # 直接返回全部元素个数
        nums.sort()  # 升序排序，方便用下标定位第 k 大的位置
        return sum(nums[n - k] > nums[i] for i in range(n - k))  # 前 n - k 个位置中，比 nums[n - k] 小的元素都至少有 k 个更大值，求和即答案
