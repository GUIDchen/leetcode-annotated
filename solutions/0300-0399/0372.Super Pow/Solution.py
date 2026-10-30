# 题目：372. 超级次方（Super Pow）
# 思路：把大指数 b 按十进制位拆开，从最低位向左逐位累乘 a^(b[i])，每位之间把底数自乘 10 次（a ← a^10）；pow 自带模参数，等价于快速幂。
# 时间复杂度：O(len(b))，每位的 pow 是 O(log 10)；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def superPow(self, a: int, b: List[int]) -> int:  # a 是底数，b 是以数组形式给出的大指数（高位在前），返回 a^b mod 1337
        mod = 1337  # 题目指定的模数
        ans = 1  # 累乘结果，从 1 开始
        for e in b[::-1]:  # 从 b 的最低位（数组末尾）向左逐位处理
            ans = ans * pow(a, e, mod) % mod  # 把 a^(当前十进制位) 这一份乘进总结果
            a = pow(a, 10, mod)  # 处理完这一位后底数变成 a^10，供高一位使用
        return ans  # 返回 a^b mod 1337
