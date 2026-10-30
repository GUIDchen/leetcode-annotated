# 题目：2310. 个位数字为 K 的整数之和（Sum of Numbers With Units Digit K）
# 思路：取 i 个加数时个位之和是 k·i，剩余部分 num − k·i 必须是 10 的倍数；从小到大枚举 i 求最少个数。
# 时间复杂度：O(num)，最坏枚举 num 次；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minimumNumbers(self, num: int, k: int) -> int:  # num 是目标和，k 是每个加数要求的个位数字
        if num == 0:  # num 为 0 时不需要任何加数
            return 0  # 最少个数是 0
        for i in range(1, num + 1):  # 从小到大枚举加数个数，第一个可行的就是最优解
            if (t := num - k * i) >= 0 and t % 10 == 0:  # 海象运算符：先算出剩余部分 t，再判断它非负且是 10 的倍数
                return i  # 可行，返回当前个数
        return -1  # 任何个数都凑不出，返回 -1
