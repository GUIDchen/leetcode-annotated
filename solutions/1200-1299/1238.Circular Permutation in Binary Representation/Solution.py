# 题目：1238. 循环码排列（Circular Permutation in Binary Representation）
# 思路：用公式 i ^ (i >> 1) 生成全部格雷码，相邻两项只差一位；再从 start 的下标处把列表首尾相接切开。
# 时间复杂度：O(2^n)，生成与切片各一遍；空间复杂度：O(2^n)，存储全部格雷码。
class Solution:  # LeetCode 约定的题解类
    def circularPermutation(self, n: int, start: int) -> List[int]:  # n 是二进制位数，start 是起点，返回首尾也相邻的循环排列
        g = [i ^ (i >> 1) for i in range(1 << n)]  # 列表推导生成全部格雷码：第 i 项是 i ^ (i >> 1)
        j = g.index(start)  # 找到 start 在格雷码中的下标
        return g[j:] + g[:j]  # 从 j 处把列表切成两段再拼接，等价于环状取数
