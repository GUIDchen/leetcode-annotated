# 题目：2218. 从栈中取出 K 个硬币的最大面值和（Maximum Value of K Coins From Piles）
# 思路：分组背包。f[i][j] 表示前 i 个栈里取 j 枚硬币的最大面值和；每个栈只能取顶部连续若干枚，用前缀和枚举取几枚做转移。
# 时间复杂度：O(n * k * m)，m 为单个栈的最大长度；空间复杂度：O(n * k)，即 DP 表的大小。
class Solution:  # LeetCode 约定的题解类
    def maxValueOfCoins(self, piles: List[List[int]], k: int) -> int:  # piles 是若干栈，k 是总共要取的硬币数
        n = len(piles)  # 栈的个数
        f = [[0] * (k + 1) for _ in range(n + 1)]  # f[i][j]：前 i 个栈取 j 枚硬币的最大面值和
        for i, nums in enumerate(piles, 1):  # 从 1 开始编号，逐个处理每个栈
            s = list(accumulate(nums, initial=0))  # 前缀和：s[h] 是从栈顶连取 h 枚的累计面值和
            for j in range(k + 1):  # 枚举前 i 个栈总共取的枚数 j
                for h, w in enumerate(s):  # 枚举本栈取的枚数 h 及其对应的面值和 w
                    if j < h:  # 本栈要取的枚数超过总数，方案不合法
                        break  # 后面 h 只会更大，直接结束本层枚举
                    f[i][j] = max(f[i][j], f[i - 1][j - h] + w)  # 不取本栈，或取本栈顶部 h 枚，取较大者
        return f[n][k]  # 前 n 个栈取 k 枚的最优值即答案
