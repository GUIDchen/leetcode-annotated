# 题目：2180. 统计各位数字之和为偶数的整数个数（Count Integers With Even Digit Sum）
# 思路：枚举 1 ~ num，对每个数用取模与整除逐位求数字之和，判断奇偶后累加计数。
# 时间复杂度：O(num log num)，每个数需要 O(log num) 次取位；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def countEven(self, num: int) -> int:  # num：统计范围的上界，统计 1 ~ num
        ans = 0  # 各位数字之和为偶数的整数个数
        for x in range(1, num + 1):  # 逐个枚举 1 ~ num，x 兼作后面逐位拆分的临时变量
            s = 0  # 当前整数的各位数字之和
            while x:  # 不断除以 10，直到所有位都取完
                s += x % 10  # 累加最低位数字
                x //= 10  # 去掉已经处理过的最低位
            ans += s % 2 == 0  # 和为偶数则计数加一（布尔值隐式转成 int）
        return ans  # 返回满足条件的整数个数
