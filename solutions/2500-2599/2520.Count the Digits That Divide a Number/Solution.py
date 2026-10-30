# 题目：2520. 统计能整除数字的位数（Count the Digits That Divide a Number）
# 核心思路：用 divmod 逐位取出 num 的最低位数，判断 num 能否被该位数字整除，能整除则计数加一。
# 时间复杂度：O(log num)，即 num 的位数；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def countDigits(self, num: int) -> int:  # num：待统计的整数；返回其中能整除 num 的位数
        ans, x = 0, num  # ans 记录答案；x 是 num 的副本，避免破坏入参
        while x:  # 只要还有位没处理完就继续循环
            x, val = divmod(x, 10)  # divmod 一次取得商与最低位数字 val
            ans += num % val == 0  # num % val == 0 的布尔值转成 0/1 直接累加
        return ans  # 返回能整除 num 的位数
