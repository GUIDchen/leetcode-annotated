# 题目：3895. 统计数字出现总次数（Count Digit Appearances）
# 思路：对每个数不断取末位判断是否等于目标数字，再用整除 10 去掉末位，逐个累加出现次数。
# 时间复杂度：O(n × log₁₀M)，M 为数值大小；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def countDigitOccurrences(self, nums: list[int], digit: int) -> int:  # nums：输入数组；digit：要统计的数字
        ans = 0  # 答案：digit 出现的总次数
        for x in nums:  # 遍历每个整数
            while x:  # 不断取末位，直到这个数变成 0
                v = x % 10  # 取出当前末位
                if v == digit:  # 末位恰好等于目标数字
                    ans += 1  # 出现次数加 1
                x //= 10  # 去掉末位，继续看高位
        return ans  # 返回总次数
