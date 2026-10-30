# 题目：3068. 最大节点价值之和（Find the Maximum Sum of Node Values）
# 核心思路：每次边操作等价于同时翻转边两端节点的标记，标记能沿树任意传导，所以真正受限的只是被翻转节点个数的奇偶性；用 DP 记录翻转个数为偶数/奇数时的最大价值之和。
# 时间复杂度：O(n)，只线性扫描一遍节点；空间复杂度：O(1)，只维护两个 DP 状态。
class Solution:  # LeetCode 约定的题解类
    def maximumValueSum(self, nums: List[int], k: int, edges: List[List[int]]) -> int:  # nums：各节点价值；k：异或值；edges：树的边（本题只用它保证奇偶性约束，不参与计算）
        f0, f1 = 0, -inf  # f0：翻转个数为偶数时的最大和，初始 0；f1：为奇数时的最大和，-inf 表示该状态尚不可达
        for x in nums:  # 逐个节点决定是否对它做异或翻转
            f0, f1 = max(f0 + x, f1 + (x ^ k)), max(f1 + x, f0 + (x ^ k))  # 右侧先用旧值全部算完再统一赋值：偶数态取「不翻」或「奇→偶」，奇数态取「不翻」或「偶→奇」
        return f0  # 翻转总数必须为偶数才可达，故答案取偶数状态 f0
