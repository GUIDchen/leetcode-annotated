# 题目：4011. 按奇偶比统计子数组 I（Count Subarrays With Even Odd Ratio I）
# 思路：枚举左端点并向右扩张右端点，实时维护子数组中的奇数个数 y 与偶数个数 x；按题目给出的比值公式判断 x / y <= a / b，注意 y 为 0 时不能作分母。
# 时间复杂度：O(n^2)，枚举了所有子数组；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def countRatioSubarrays(self, nums: list[int], a: int, b: int) -> int:  # nums：待统计的数组；a、b：比值上界 a / b；返回满足条件的子数组个数
        ans = 0  # ans 记录满足条件的子数组个数
        n = len(nums)  # n 为数组长度
        for i in range(n):  # 枚举子数组的左端点
            y = 0  # y 记录当前子数组中奇数的个数
            for j in range(i, n):  # 右端点逐步右移，枚举所有以 i 开头的子数组
                y += nums[j] % 2  # 当前元素为奇数则 y 加 1
                x = j - i + 1 - y  # 偶数个数 = 子数组长度 - 奇数个数
                if y and (x / y) <= (a / b):  # 先判断 y 非零（分母不为零），再按题目给出的比值公式比较
                    ans += 1  # 满足条件则计数加 1
        return ans  # 返回满足条件的子数组总数
