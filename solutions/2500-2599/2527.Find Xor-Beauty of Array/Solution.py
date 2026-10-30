# 题目：2527. 查询数组异或美丽值（Find Xor-Beauty of Array）
# 思路：按位独立分析可证，下标三分组的组合中有偶数次重复，最终美丽值等于所有元素的异或和。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用到 reduce 的累加器。
class Solution:  # LeetCode 约定的题解类
    def xorBeauty(self, nums: List[int]) -> int:  # nums 是输入数组，返回它的异或美丽值
        return reduce(xor, nums)  # 用 reduce 让 xor 依次作用于所有元素，等价于把全部元素异或起来
