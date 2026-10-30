# 题目：465. 最优账单平衡（Optimal Account Balancing）
# 思路：先把流水汇总成每人的净余额，再对非零余额做状压 DP：只对总和为 0 的子集，把 k 人平账的最少次数按子集拆分求最小值。
# 时间复杂度：O(3^m + m·2^m)，m 为净余额非零的人数（≤12）；空间复杂度：O(2^m)。
class Solution:  # LeetCode 约定的题解类
    def minTransfers(self, transactions: List[List[int]]) -> int:  # transactions 每项为 [付款人, 收款人, 金额]
        g = defaultdict(int)  # 记录每个人的净余额，未出现的人按 0 处理
        for f, t, x in transactions:  # 逐笔流水：f 付款、t 收款、x 金额
            g[f] -= x  # 付款人余额减少
            g[t] += x  # 收款人余额增加
        nums = [x for x in g.values() if x]  # 只保留净余额非零的人
        m = len(nums)  # 真正需要平账的人数
        f = [inf] * (1 << m)  # f[掩码]：该子集内部平账的最少转账次数
        f[0] = 0  # 空集合不需要转账
        for i in range(1, 1 << m):  # 枚举所有非空子集
            s = 0  # 该子集的余额总和
            for j, x in enumerate(nums):  # 逐位统计子集内的余额
                if i >> j & 1:  # 第 j 个人在子集内
                    s += x  # 累加他的余额
            if s == 0:  # 只有总和为零的子集才可能内部平账
                f[i] = i.bit_count() - 1  # k 个人平账至多需要 k-1 次转账
                j = (i - 1) & i  # 从 i 的最大真子集开始枚举
                while j > 0:  # 逐个枚举 i 的真子集
                    f[i] = min(f[i], f[j] + f[i ^ j])  # 拆成 j 与 i^j 两部分分别平账，取更优
                    j = (j - 1) & i  # 枚举下一个真子集
        return f[-1]  # f[-1] 即全集对应的状态，为答案
