# 题目：1655. 分配重复整数（Distribute Repeating Integers）
# 思路：状压 DP：先预处理 quantity 每个子集的需求总和 s[mask]，再把 nums 按值聚合成每种数字的可用个数，f[i][j] 表示用前 i+1 种数字能否满足顾客集合 j，枚举 j 的子集做转移。
# 时间复杂度：O(n·3^m)，m 为顾客数（≤10）；空间复杂度：O(n·2^m)。
class Solution:  # LeetCode 约定的题解类
    def canDistribute(self, nums: List[int], quantity: List[int]) -> bool:  # nums 是可分配的数字，quantity 是每个顾客需要的个数
        m = len(quantity)  # 顾客数量，决定状压位数
        s = [0] * (1 << m)  # s[mask]：需求集合 mask 中的需求量总和
        for i in range(1, 1 << m):  # 枚举除空集外的每个需求子集
            for j in range(m):  # 找 mask 中最低的一个置位
                if i >> j & 1:  # 该位存在，可以用去掉它的子集递推
                    s[i] = s[i ^ (1 << j)] + quantity[j]  # 去掉这一位后的需求总和，再加该顾客的需求
                    break  # 只用最低位递推一次，避免重复累加
        cnt = Counter(nums)  # 统计 nums 中每个值出现的次数
        arr = list(cnt.values())  # 把每种数字的可用个数压成数组
        n = len(arr)  # 不同数字的种类数
        f = [[False] * (1 << m) for _ in range(n)]  # f[i][j]：用前 i+1 种数字能否满足顾客集合 j
        for i in range(n):  # 任意前 i 种数字都能满足空需求集合
            f[i][0] = True  # 空集合恒为真
        for i, x in enumerate(arr):  # 逐种数字做转移，x 是当前数字的可用个数
            for j in range(1, 1 << m):  # 枚举非空的需求集合
                if i and f[i - 1][j]:  # 前一种数字已经能满足 j，直接继承
                    f[i][j] = True  # 继承成功状态
                    continue  # 跳过当前数字
                k = j  # 从整个集合 j 开始枚举它的子集
                while k:  # k 非空时继续
                    ok1 = j == k if i == 0 else f[i - 1][j ^ k]  # 剩余集合 j^k 要么为空（i==0），要么由前 i-1 种数字满足
                    ok2 = s[k] <= x  # 子集 k 的总需求量不能超过当前数字的可用个数
                    if ok1 and ok2:  # 两个条件同时成立，说明可以接下子集 k
                        f[i][j] = True  # 记录可行状态
                        break  # 找到一种拆法就够了
                    k = (k - 1) & j  # (k-1)&j 得到下一个更小的子集
        return f[-1][-1]  # 所有数字用完后能否满足全部顾客
