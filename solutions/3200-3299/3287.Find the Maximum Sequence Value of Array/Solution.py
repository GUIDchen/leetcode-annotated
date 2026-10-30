# 题目：3287. 求出数组中最大序列值（Find the Maximum Sequence Value of Array）
# 思路：前后缀各做一次 DP，标记「某段区间选 k 个能得到哪些按位或值」，再枚举分割点求两段按位或值的最大异或。
# 时间复杂度：O(n·k·2^7)；空间复杂度：O(n·k·2^7)，用于存放 f 与 g 两张布尔表。
class Solution:  # LeetCode 约定的题解类
    def maxValue(self, nums: List[int], k: int) -> int:  # nums：原数组；k：所选序列的长度
        m = 1 << 7  # 值域上界：元素 < 2^7，按位或结果不超过 127
        n = len(nums)  # 数组长度
        f = [[[False] * m for _ in range(k + 2)] for _ in range(n + 1)]  # f[i][j][x]：前 i 个数选 j 个能否按位或得到 x
        f[0][0][0] = True  # 边界：选 0 个数时按位或为 0
        for i in range(n):  # 前缀 DP：逐个把新元素加进来
            for j in range(k + 1):  # 已选个数，最多 k 个
                for x in range(m):  # 枚举可能的按位或值
                    f[i + 1][j][x] |= f[i][j][x]  # 不选 nums[i]：状态原样传给 i+1
                    f[i + 1][j + 1][x | nums[i]] |= f[i][j][x]  # 选 nums[i]：按位或上它，个数加一

        g = [[[False] * m for _ in range(k + 2)] for _ in range(n + 1)]  # g[i][j][y]：从下标 i 起的后缀选 j 个能否按位或得到 y
        g[n][0][0] = True  # 边界：空后缀按位或为 0
        for i in range(n, 0, -1):  # 后缀 DP：从后往前把元素加进来
            for j in range(k + 1):  # 已选个数
                for y in range(m):  # 枚举可能的按位或值
                    g[i - 1][j][y] |= g[i][j][y]  # 不选 nums[i-1]：状态前移到 i-1
                    g[i - 1][j + 1][y | nums[i - 1]] |= g[i][j][y]  # 选 nums[i-1]：按位或上它，个数加一

        ans = 0  # 记录两段按位或值的最大异或
        for i in range(k, n - k + 1):  # 枚举分割点，保证前后各够 k 个元素
            for x in range(m):  # 枚举前缀按位或值
                if f[i][k][x]:  # 前缀状态可达才继续
                    for y in range(m):  # 枚举后缀按位或值
                        if g[i][k][y]:  # 后缀状态可达
                            ans = max(ans, x ^ y)  # 用异或值刷新答案
        return ans  # 返回最大异或值
