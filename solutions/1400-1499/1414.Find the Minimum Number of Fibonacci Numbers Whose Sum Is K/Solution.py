# 题目：1414. 和为 K 的最少斐波那契数字数目（Find the Minimum Number of Fibonacci Numbers Whose Sum Is K）
# 思路：先让 (a, b) 成为 k 附近相邻的一对斐波那契数，再从大到小贪心递减 k 并计数。
# 时间复杂度：O(log k)，斐波那契数列项数为 O(log k)；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def findMinFibonacciNumbers(self, k: int) -> int:  # k 是目标和，返回最少需要几个斐波那契数
        a = b = 1  # 从最小的两项 1,1 开始
        while b <= k:  # 一直生成到 b 超过 k 为止
            a, b = b, a + b  # 同时后移：a 取旧的 b，b 取两项之和
        ans = 0  # 记录已选数字个数
        while k:  # k 还没减到 0
            if k >= b:  # 贪心：b 不超过 k 就一定要用它
                k -= b  # 从 k 中减去 b
                ans += 1  # 计数加一
            a, b = b - a, a  # 同时回退一对相邻斐波那契数：新的 b 是旧 b 的前一项，新的 a 是旧 a 的前一项
        return ans  # 返回最少个数
