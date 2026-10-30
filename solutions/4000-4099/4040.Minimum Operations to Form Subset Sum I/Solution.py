# 题目：4040. 构造子集和的最少操作次数 I（Minimum Operations to Form Subset Sum I）
# 思路：0-1 背包 DP，f[w] 表示凑出子集和 w 的最少操作次数；对每个数 x 逆序枚举容量 w，分别尝试「翻倍 i 次得 x*2^i」与「减半 i 次得 floor(x/2^i)」两条分支来更新 f[w]。
# 复杂度：时间复杂度 O(n * sum * log(sum))，n 为 nums 长度；空间复杂度 O(sum)，即 DP 数组 f。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums: List[int], sum: int) -> int:  # nums：可选数字；sum：目标和；返回最少操作次数，无法达成返回 -1
        f = [0] + [inf] * sum  # f[w]：凑出子集和 w 的最少操作次数；f[0] = 0，其余先置无穷
        for x in nums:  # 依次枚举每个可选数字（每个数最多用一次）
            for w in range(sum, -1, -1):  # 逆序枚举容量，避免同一个数在本轮被重复使用
                i, y = 0, x  # i：已做操作次数；y：操作 i 次后得到的值
                while y <= w:  # 不断翻倍，直到超过当前容量 w
                    f[w] = min(f[w], f[w - y] + i)  # 用 y 填 w-y 这部分，总代价 = 凑 w-y 的代价 + i 次操作
                    i += 1  # 操作次数加一
                    y <<= 1  # y 翻倍：x -> 2x -> 4x ...
                i, y = 1, x >> 1  # 换一条分支：y = floor(x / 2)，对应减半 1 次
                while y > 0:  # 一直减半，直到值变成 0
                    if y <= w:  # 该值不超过剩余容量才可能用上
                        f[w] = min(f[w], f[w - y] + i)  # 用 y 填 w-y 这部分
                    i += 1  # 操作次数加一
                    y >>= 1  # y 减半：x -> floor(x/2) -> floor(x/4) ...
        return -1 if f[sum] == inf else f[sum]  # 目标不可达返回 -1，否则返回最少操作次数
