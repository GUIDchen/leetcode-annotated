# 题目：3647. 两个袋子中的最大重量（Maximum Weight in Two Bags）
# 核心思路：二维 0-1 背包。f[j][k] 表示两个袋子容量分别为 j、k 时的最大装载重量；每个物品只有「放进第一个袋子、放进第二个袋子、不放」三种选择，两个容量维度都从大到小遍历，保证同一物品不会被重复使用。
# 复杂度：时间 O(n·w1·w2)，每个物品枚举两维容量；空间 O(w1·w2)，二维 DP 表。
class Solution:  # LeetCode 题解类
    def maxWeight(self, weights: List[int], w1: int, w2: int) -> int:  # weights：物品重量；w1、w2：两个袋子的容量
        f = [[0] * (w2 + 1) for _ in range(w1 + 1)]  # DP 表：f[j][k] 表示容量 j、k 时能装的最大重量，初值全为 0
        max = lambda a, b: a if a > b else b  # 自定义取较大值的函数（在本函数内覆盖内置 max）
        for x in weights:  # 逐个物品做 0-1 背包
            for j in range(w1, -1, -1):  # 倒序枚举第一个袋子的容量，保证该物品只用一次
                for k in range(w2, -1, -1):  # 倒序枚举第二个袋子的容量
                    if x <= j:  # 第一个袋子放得下
                        f[j][k] = max(f[j][k], f[j - x][k] + x)  # 在「不装」与「装进第一个袋子」之间取较大值
                    if x <= k:  # 第二个袋子放得下
                        f[j][k] = max(f[j][k], f[j][k - x] + x)  # 在「不装」与「装进第二个袋子」之间取较大值
        return f[w1][w2]  # 两个袋子恰好用满各自容量时的最优解
