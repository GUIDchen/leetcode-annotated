# 题目：2954. 统计感冒序列的数目（Count the Number of Infection Sequences）
# 思路：按已感染者把未感染人群切成若干段；先算未感染全排列 s!，再除以各段内部顺序 x!，中间段再乘 2^(x-1) 表示两侧先感染的先后选择。
# 时间复杂度：O(n + m log MOD)，阶乘预处理加若干次快速幂；空间复杂度：O(n)，阶乘数组。
mod = 10**9 + 7  # 取模常量
mx = 10**5  # 题目 n 的上界，阶乘表按它开大小
fac = [1] * (mx + 1)  # fac[i] 保存 i! % mod，全局预计算一次即可
for i in range(2, mx + 1):  # 从 2 开始递推（fac[0] 与 fac[1] 都已经是 1）
    fac[i] = fac[i - 1] * i % mod  # 阶乘递推并取模


class Solution:  # LeetCode 约定的题解类
    def numberOfSequence(self, n: int, sick: List[int]) -> int:  # n 是总人数，sick 是初始已感染者下标；返回可能的感染序列数目
        nums = [b - a - 1 for a, b in pairwise([-1] + sick + [n])]  # 在 sick 前后补上边界 -1 与 n，用 pairwise 求每段连续未感染人数
        ans = 1  # 累乘器，初值为 1
        s = sum(nums)  # 未感染总人数
        ans = fac[s]  # 先取未感染人群的全排列 s!
        for x in nums:  # 逐段扣除段内的排列重复
            if x:  # 只处理长度非 0 的段
                ans = ans * pow(fac[x], mod - 2, mod) % mod  # 乘 x! 的模逆元，等价于除以 x!
        for x in nums[1:-1]:  # 只看被两侧感染者夹住的中间段
            if x > 1:  # 长度大于 1 才有先感染哪一侧的选择
                ans = ans * pow(2, x - 1, mod) % mod  # 每段贡献 2^(x-1) 种内部顺序
        return ans  # 返回感染序列总数
