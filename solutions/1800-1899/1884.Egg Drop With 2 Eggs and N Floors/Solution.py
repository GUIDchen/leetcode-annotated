# 题目：1884. 鸡蛋掉落-两枚鸡蛋（Egg Drop With 2 Eggs and N Floors）
# 思路：动态规划，f[i] 表示确定 i 层楼的最少操作次数；第一次在第 j 层扔，碎了线性查 j-1 层、没碎查 f[i-j] 层，取较大值加 1。
# 时间复杂度：O(n^2)，两层循环；空间复杂度：O(n)，一维 DP 数组。
class Solution:  # LeetCode 约定的题解类
    def twoEggDrop(self, n: int) -> int:  # n 是楼层总数
        f = [0] + [inf] * n  # f[i] 是 i 层楼的最少操作次数：0 层为 0，其余先设为无穷大
        for i in range(1, n + 1):  # 自小到大递推楼层数
            for j in range(1, i + 1):  # 枚举第一次扔鸡蛋的楼层 j
                f[i] = min(f[i], 1 + max(j - 1, f[i - j]))  # 碎了查 j-1 层，没碎查 i-j 层，取最坏情况再加本次操作
        return f[n]  # 返回 n 层楼的最少操作次数
