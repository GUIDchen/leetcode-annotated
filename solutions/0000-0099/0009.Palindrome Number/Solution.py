# 题目：9. 回文数（Palindrome Number）
# 思路：只反转后一半数字，反转值 y 追上剩余部分 x 时停止，再判断 x 是否等于 y（偶数位）或 y // 10（奇数位）。
# 时间复杂度：O(log x)，只处理一半位数；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def isPalindrome(self, x: int) -> bool:  # 判断整数 x 是否为回文数
        if x < 0 or (x and x % 10 == 0):  # 负数不是回文；末位为 0 的非零整数也不是（x 为 0 时放行）
            return False  # 提前返回，不做反转
        y = 0  # 反转得到的后半段数字
        while y < x:  # 只反转一半，y 追上 x 时停止
            y = y * 10 + x % 10  # 把 x 的末位并入 y
            x //= 10  # x 去掉末位
        return x in (y, y // 10)  # 偶数位时 x == y；奇数位时 x == y // 10（去掉中间位）
