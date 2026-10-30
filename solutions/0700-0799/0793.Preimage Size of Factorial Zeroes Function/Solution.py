# 题目：793. 阶乘函数后 K 个零（Preimage Size of Factorial Zeroes Function）
# 思路：记 f(n) 为 n! 末尾零的个数，记 g(k) 为使 f(n) >= k 的最小 n；末尾零恰为 k 的 n 是区间 [g(k), g(k+1))，答案即 g(k+1)-g(k)。
# 时间复杂度：O(log²k)，二分 O(log k) 次、每次 f 递归 O(log n)；空间复杂度：O(log n)，递归栈深度。
class Solution:  # LeetCode 约定的题解类
    def preimageSizeFZF(self, k: int) -> int:  # k：希望 n! 末尾恰好有 k 个零
        def f(x):  # f(x)：x! 末尾零的个数，等于 1..x 中因子 5 的总数
            if x == 0:  # 递归出口：0! = 1，没有因子 5
                return 0  # 0 的阶乘末尾没有零
            return x // 5 + f(x // 5)  # 先取 floor(x/5) 这一层的贡献，再递归处理 floor(x/5) 的部分

        def g(k):  # g(k)：使 f(n) >= k 的最小 n
            return bisect_left(range(5 * k), k, key=f)  # 在 [0, 5k) 上按 f 的单调性二分，找第一个 f(n) >= k 的位置

        return g(k + 1) - g(k)  # 前缀计数之差：f(n) 恰为 k 的 n 共有 g(k+1)-g(k) 个
