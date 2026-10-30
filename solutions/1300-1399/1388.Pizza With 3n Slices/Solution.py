# 题目：1388. 3n 块披萨（Pizza With 3n Slices）
# 思路：环形数组选 n 个互不相邻元素的最大和；断环成链，分别去掉首、尾各做一次线性 DP，取较大值。
# 时间复杂度：O(n^2)，两次 O(m*n) 的 DP；空间复杂度：O(m*n)，二维 DP 表。
class Solution:  # LeetCode 约定的题解类
    def maxSizeSlices(self, slices: List[int]) -> int:  # slices：环形排列的 3n 块披萨
        def g(nums: List[int]) -> int:  # 线段上「不相邻取 n 个」的 DP
            m = len(nums)  # 当前线段长度
            f = [[0] * (n + 1) for _ in range(m + 1)]  # f[i][j]：前 i 个里选 j 个且互不相邻的最大和
            for i in range(1, m + 1):  # 枚举前缀长度
                for j in range(1, n + 1):  # 枚举已选个数
                    f[i][j] = max(  # 两种选择取较大者
                        f[i - 1][j], (f[i - 2][j - 1] if i >= 2 else 0) + nums[i - 1]  # 不选第 i 个 / 选它并跳过相邻元素
                    )  # 状态转移结束
            return f[m][n]  # 前 m 个里选 n 个的最优解

        n = len(slices) // 3  # 需要选出的块数
        a, b = g(slices[:-1]), g(slices[1:])  # 分别去掉最后一块、第一块，把环断成两条链
        return max(a, b)  # 环形问题取两种情况的最大值
