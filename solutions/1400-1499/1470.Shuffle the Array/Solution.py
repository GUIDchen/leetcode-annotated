# 题目：1470. 重新排列数组（Shuffle the Array）
# 核心思路：把数组切成前后两半，用 zip 按位配对后展平，得到交替排列的结果。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(n)，新建长度为 2n 的结果列表。
class Solution:  # LeetCode 约定的题解类
    def shuffle(self, nums: List[int], n: int) -> List[int]:  # nums 长度为 2n，n 为每半段的长度
        return [x for pair in zip(nums[:n], nums[n:]) for x in pair]  # zip 把前后两半按位配对，内层 for 再把每对拆开铺平，得到交替排列
