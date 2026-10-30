# 题目：1814. 统计一个数组中好对子的数目（Count Nice Pairs in an Array）
# 思路：nums[i] + rev(nums[j]) == nums[j] + rev(nums[i]) 移项得 nums[i] - rev(nums[i]) == nums[j] - rev(nums[j])，统计每种差值出现次数后两两组合。
# 时间复杂度：O(n * log10(maxVal))，每个元素反转一次；空间复杂度：O(n)，计数器保存 n 个不同的差值。
class Solution:  # LeetCode 约定的题解类
    def countNicePairs(self, nums: List[int]) -> int:  # nums 是输入数组
        def rev(x):  # 局部函数：把整数按十进制位反转
            y = 0  # y 累积反转后的结果
            while x:  # 每轮取走最低位，直到 x 变成 0
                y = y * 10 + x % 10  # 把 x 的最低位接到 y 的末尾
                x //= 10  # 去掉 x 已经处理过的最低位
            return y  # 返回反转后的整数

        cnt = Counter(x - rev(x) for x in nums)  # 统计每个元素“值减反转值”这个特征值的出现频率
        mod = 10**9 + 7  # 题目要求的取模值
        return sum(v * (v - 1) // 2 for v in cnt.values()) % mod  # 每组内两两配对的组合数之和再取模
