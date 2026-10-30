# 题目：3191. 使二进制数组全部等于 1 的最少操作次数 I（Minimum Operations to Make Binary Array Elements Equal to One I）
# 思路：从左到右贪心，遇到 0 就以它为左端点翻转连续三位；由于最左的 0 只能靠这次翻转修好，所以该策略最优。
# 时间复杂度：O(n)，每个位置只处理一次；空间复杂度：O(1)，只用了常数个变量并直接原地修改数组。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums: List[int]) -> int:  # nums：0/1 数组，返回最少操作次数，无解返回 -1
        ans = 0  # 记录已执行的翻转次数
        for i, x in enumerate(nums):  # 同时取得下标 i 和当前值 x，从左向右处理
            if x == 0:  # 当前位置是 0，必须把它翻成 1
                if i + 2 >= len(nums):  # 右边不足两位，无法组成长度为 3 的区间
                    return -1  # 无法修好，按题意返回 -1
                nums[i + 1] ^= 1  # 异或 1 相当于取反，翻转 i+1 位
                nums[i + 2] ^= 1  # 同理翻转 i+2 位，完成整段三位翻转
                ans += 1  # nums[i] 已变成 1，操作次数加一
        return ans  # 全部元素均为 1，返回累计操作次数
