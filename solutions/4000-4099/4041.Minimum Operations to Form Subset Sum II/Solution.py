# 题目：4041. 构造子集和的最少操作次数 II（Minimum Operations to Form Subset Sum II）
# 思路：0-1 背包 DP，f[w] 表示凑出子集和 w 的最少操作次数；对每个数 x 逆序枚举容量 w，外层只用「翻倍 x*2^i」，内层再嵌套「先减半 i 次、后翻倍 j 次」得 floor(x/2^i)*2^j，两者代价分别为 i 与 i+j。
# 复杂度：时间复杂度 O(n * sum * log^2(sum))，n 为 nums 长度；空间复杂度 O(sum)，即 DP 数组 f。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums: List[int], sum: int) -> int:  # nums：可选数字；sum：目标和；返回最少操作次数，无法达成返回 -1
        inf = 10**9  # 无穷大，表示该和暂时不可达
        f = [0] + [inf] * sum  # f[w]：凑出子集和 w 的最少操作次数，f[0] = 0

        for x in nums:  # 依次枚举每个可选数字（每个数最多用一次）
            for w in range(sum, -1, -1):  # 逆序枚举容量，保证本轮内每个数只被用一次
                i, y = 0, x  # i：操作次数；y：当前得到的值
                while y <= w:  # 只翻倍的分支：y = x * 2^i
                    f[w] = min(f[w], f[w - y] + i)  # 用 y 填 w-y 这部分，代价为 i
                    i += 1  # 操作次数加一
                    y *= 2  # y 翻倍

                i, y = 1, x // 2  # 先减半 i 次：y = floor(x / 2^i)
                while y > 0:  # 减半到 0 就停止
                    j, z = 0, y  # j：翻倍次数；z：在 y 基础上翻倍 j 次的值
                    while z <= w:  # 再翻倍的分支：z = y * 2^j
                        f[w] = min(f[w], f[w - z] + i + j)  # 总代价 = 凑 w-z 的代价 + i + j
                        j += 1  # 翻倍次数加一
                        z *= 2  # z 翻倍
                    i += 1  # 减半次数加一
                    y //= 2  # y 减半

        return -1 if f[sum] == inf else f[sum]  # 可达就返回最小代价，否则返回 -1
