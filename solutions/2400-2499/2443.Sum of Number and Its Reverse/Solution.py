# 题目：2443. 反转之后的数字和（Sum of Number and Its Reverse）
# 思路：枚举 k ∈ [0, num]，用切片 [::-1] 求十进制反转，判断 k + 反转(k) 是否等于 num，存在即真。
# 时间复杂度：O(num·log num)，共 num+1 次反转、每次 O(log num)；空间复杂度：O(log num)，字符串与整数的临时空间。
class Solution:  # LeetCode 约定的题解类
    def sumOfNumberAndReverse(self, num: int) -> bool:  # num 是目标和，返回是否存在一对「数 + 反转数」
        return any(k + int(str(k)[::-1]) == num for k in range(num + 1))  # 生成器惰性枚举 [0, num]：str 转字符串、切片反转、int 转回整数；any 遇到第一个成立项即短路返回 True，全不成立则为 False
