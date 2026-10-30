# 题目：2836. 在传球游戏中最大化函数值（Maximize Value of Function in a Ball Passing Game）
# 思路：二进制倍增。f[i][j] 表示从 i 走 2^j 步到达的位置，g[i][j] 为这段路径上的号码和；把 k 按二进制位拆成若干段跳跃再拼接。
# 时间复杂度：O(n log k)，建表与累计都是 n * log k 次操作；空间复杂度：O(n log k)，两张倍增表。
class Solution:  # LeetCode 约定的题解类
    def getMaxFunctionValue(self, receiver: List[int], k: int) -> int:  # receiver 是传球目标数组，k 是传球次数
        n, m = len(receiver), k.bit_length()  # n 为人数；m 为 k 的二进制位数，即倍增表的层数
        f = [[0] * m for _ in range(n)]  # f[i][j]：从 i 出发走 2^j 步后到达的位置
        g = [[0] * m for _ in range(n)]  # g[i][j]：走这 2^j 步途中经过的号码之和（含起点、不含终点）
        for i, x in enumerate(receiver):  # 初始化第 0 层，即只走 1 步的情况
            f[i][0] = x  # 走 1 步后停在传球目标上
            g[i][0] = i  # 只走 1 步时，途中的号码只有起点自己
        for j in range(1, m):  # 逐层递推走 2^j 步
            for i in range(n):  # 枚举每个起点
                f[i][j] = f[f[i][j - 1]][j - 1]  # 先走 2^(j-1) 步，再从落点走 2^(j-1) 步
                g[i][j] = g[i][j - 1] + g[f[i][j - 1]][j - 1]  # 两段路径的号码之和直接相加
        ans = 0  # 记录所有起点中的最大函数值
        for i in range(n):  # 枚举每个起点 i 作为函数值的起点
            p, t = i, 0  # p 是当前所在球员编号，t 是已累计的途中号码之和
            for j in range(m):  # 按 k 的二进制位从低到高拆出要跳的段
                if k >> j & 1:  # 第 j 位为 1，需要跳一段 2^j 步
                    t += g[p][j]  # 累加这一段沿途的号码之和
                    p = f[p][j]  # 位置随之前进 2^j 步
            ans = max(ans, t + p)  # 函数值等于途中号码之和加上终点号码，取最大
        return ans  # 返回最大函数值
