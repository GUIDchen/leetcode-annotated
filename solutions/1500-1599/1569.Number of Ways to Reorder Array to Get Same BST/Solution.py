# 题目：1569. 将子数组重新排序得到同一个二叉搜索树的方案数（Number of Ways to Reorder Array to Get Same BST）
# 思路：BST 形态由根与左右子树唯一确定；预处理组合数后 DFS：方案数 = C(|左|+|右|, |左|) * 左方案 * 右方案。
# 时间复杂度：O(n^2)，组合数表 O(n^2) 加递归划分；空间复杂度：O(n^2)，组合数二维表。
class Solution:  # LeetCode 约定的题解类
    def numOfWays(self, nums: List[int]) -> int:  # nums：构成同一棵 BST 的插入序列
        def dfs(nums):  # 递归求以 nums[0] 为根的合法方案数
            if len(nums) < 2:  # 空序列或单元素序列只有一种排列
                return 1  # 递归出口
            left = [x for x in nums if x < nums[0]]  # 比根小的元素构成左子树序列
            right = [x for x in nums if x > nums[0]]  # 比根大的元素构成右子树序列
            m, n = len(left), len(right)  # 左右子树的规模
            a, b = dfs(left), dfs(right)  # 左右子树各自的合法方案数
            return (((c[m + n][m] * a) % mod) * b) % mod  # 左右交叉排列数乘上子树方案数，逐步取模防溢出

        n = len(nums)  # 元素个数
        mod = 10**9 + 7  # 结果对 1e9+7 取模
        c = [[0] * n for _ in range(n)]  # 组合数表 c[i][j]：从 i 个里取 j 个的方案数
        c[0][0] = 1  # 边界：0 个里取 0 个只有一种方案
        for i in range(1, n):  # 逐行递推杨辉三角
            c[i][0] = 1  # 取 0 个的方案数恒为 1
            for j in range(1, i + 1):  # 枚举取 j 个
                c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod  # 帕斯卡公式并取模
        return (dfs(nums) - 1 + mod) % mod  # 减去原序列自身这一种方案，加 mod 避免负数
