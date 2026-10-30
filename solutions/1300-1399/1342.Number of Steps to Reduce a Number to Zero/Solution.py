# 题目：1342. 将数字变成 0 的操作次数（Number of Steps to Reduce a Number to Zero）
# 思路：直接模拟。奇数减 1，偶数右移一位（即除以 2），每步计数加一，直到 num 为 0。
# 时间复杂度：O(log n)，每两步至少让二进制位数减少一位；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def numberOfSteps(self, num: int) -> int:  # num 是待归零的非负整数
        ans = 0  # 记录操作次数
        while num:  # num 变成 0 之前一直循环
            if num & 1:  # 判断最低位是否为 1，即是奇数
                num -= 1  # 奇数：减 1
            else:  # 否则是偶数
                num >>= 1  # 偶数：右移一位，等价于除以 2
            ans += 1  # 操作次数加一
        return ans  # 返回总操作次数
