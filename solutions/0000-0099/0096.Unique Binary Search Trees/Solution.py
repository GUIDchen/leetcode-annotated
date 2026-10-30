# 题目：96. 不同的二叉搜索树（Unique Binary Search Trees）
# 思路：卡特兰数 DP，f[i] 表示 i 个结点的 BST 种数；枚举左子树结点数 j，左右方案数相乘后累加。
# 时间复杂度：O(n^2)，双重循环枚举；空间复杂度：O(n)，一维 DP 列表。
class Solution:  # LeetCode 约定的题解类
    def numTrees(self, n: int) -> int:  # n 是结点个数，返回不同结构的 BST 数量
        f = [1] + [0] * n  # f[0] = 1 作为空树边界，其余位置先置 0
        for i in range(n + 1):  # 依次计算结点数为 0..n 的答案
            for j in range(i):  # j 是左子树的结点数，右子树则有 i-j-1 个
                f[i] += f[j] * f[i - j - 1]  # 左右方案数相乘，对所有根的划分求和
        return f[n]  # n 个结点的种数即答案
