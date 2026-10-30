# 题目：922. 按奇偶排序数组 II（Sort Array By Parity II）
# 思路：偶数下标只放偶数、奇数下标只放奇数；变量 j 记录下一个可交换的奇数下标，遇到错位的奇数就交换。
# 时间复杂度：O(n)，i、j 各自单向推进；空间复杂度：O(1)，除输入外只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def sortArrayByParityII(self, nums: List[int]) -> List[int]:  # nums：待调整的数组，返回同一个数组对象
        n, j = len(nums), 1  # n 是数组长度；j 是当前可用的奇数下标
        for i in range(0, n, 2):  # i 只走偶数下标 0,2,4,...
            if nums[i] % 2:  # 偶数下标上却是奇数，位置放错了
                while nums[j] % 2:  # 找第一个「奇数下标上放偶数」的位置
                    j += 2  # 每次跨 2，保证 j 一直是奇数下标
                nums[i], nums[j] = nums[j], nums[i]  # 交换后两边奇偶性都正确
        return nums  # 返回原地调整后的数组
