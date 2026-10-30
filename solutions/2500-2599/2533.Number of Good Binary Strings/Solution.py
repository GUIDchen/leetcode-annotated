# 题目：2533. 好二进制字符串的数量（Number of Good Binary Strings）
# 核心思路：线性 DP。f[i] 表示长度为 i 的好串数目；好串要么以 oneGroup 个 1 结尾、要么以 zeroGroup 个 0 结尾，故 f[i] = f[i-oneGroup] + f[i-zeroGroup]，最后对区间 [minLength, maxLength] 内的 f 求和。
# 时间复杂度：O(maxLength)，一趟递推加一趟切片求和；空间复杂度：O(maxLength)，一维 DP 列表。
class Solution:  # LeetCode 约定的题解类
    def goodBinaryStrings(  # minLength / maxLength 为长度区间，oneGroup / zeroGroup 分别是「1 组」与「0 组」的固定块长度（参数跨行书写）
        self, minLength: int, maxLength: int, oneGroup: int, zeroGroup: int  # 参数续行，四个参数的类型都是 int
    ) -> int:  # 返回长度在区间内的好二进制串数量
        mod = 10**9 + 7  # 结果对 1e9+7 取模，避免数值无限增大
        f = [1] + [0] * maxLength  # f[i] 表示长度为 i 的好串个数，f[0] = 1 作为递推起点
        for i in range(1, len(f)):  # 按长度从小到大递推每个状态
            if i - oneGroup >= 0:  # 长度足够放下一整组 1
                f[i] += f[i - oneGroup]  # 末尾接 oneGroup 个 1，方案数来自长度 i-oneGroup
            if i - zeroGroup >= 0:  # 长度足够放下一整组 0
                f[i] += f[i - zeroGroup]  # 末尾接 zeroGroup 个 0，方案数来自长度 i-zeroGroup
            f[i] %= mod  # 每个状态算完立刻取模，保持数值可控
        return sum(f[minLength:]) % mod  # 取出长度不小于 minLength 的所有状态求和后再取模
