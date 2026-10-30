# 题目：2169. 得到 0 的操作数（Count Operations to Obtain Zero）
# 思路：直接模拟，每轮用较大数减去较小数并把计数器加一，直到其中一个数减到 0。
# 时间复杂度：O(num1 + num2)，最坏情况是辗转相减的步数；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def countOperations(self, num1: int, num2: int) -> int:  # num1、num2：两个非负整数；返回让其中一个变成 0 的操作次数
        ans = 0  # ans：记录已经执行了多少次相减
        while num1 and num2:  # 两个数都大于 0 时继续模拟，任一归零即结束
            if num1 >= num2:  # num1 不小于 num2，就用 num1 去减 num2
                num1 -= num2  # 减去较小的数
            else:  # 否则 num1 更小
                num2 -= num1  # 用 num2 去减 num1
            ans += 1  # 每轮无论走哪个分支都算一次操作
        return ans  # 返回总操作次数
