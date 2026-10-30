# 3897. 连接二进制片段得到的最大值 / Maximum Value of Concatenated Binary Segments
# 核心思路：按「纯 1 段 → 含 1 段 → 纯 0 段」贪心排序后依次拼接，再用 2 的幂权重从最高位往低位累加得到取模结果。
# 复杂度：时间 O(n log n)，空间 O(n)。
class Solution:  # 题解类
    def maxValue(self, nums1: list[int], nums0: list[int]) -> int:  # nums1[i] 个 1 与 nums0[i] 个 0 组成第 i 段，重排拼接后求最大值
        MOD = 10**9 + 7  # 结果取模的模数
        pairs = list(zip(nums1, nums0))  # 把两数组配对成 (1 的个数, 0 的个数)
        b = sum(x + y for x, y in pairs)  # 所有段的总位数

        def key(p: tuple[int, int]) -> tuple[int, int, int]:  # 排序键：类别优先，再按 1 的个数降序、0 的个数升序
            x, y = p  # 拆出 1 与 0 的个数
            if y == 0:  # 没有 0，整段都是 1
                return (0, -x, 0)  # 第 0 类排最前，1 更多的靠前
            if x > 0:  # 既有 1 又有 0
                return (1, -x, y)  # 第 1 类：1 更多的靠前，0 更少的靠前
            return (2, y, 0)  # 纯 0 段排最后，0 更少的靠前

        pairs.sort(key=key)  # 按贪心顺序排序

        ans = 0  # 拼接后的答案（取模）
        p = [1] * b  # p[i] = 2^i mod MOD，即第 i 位的权重
        for i in range(1, b):  # 递推每一位的权重
            p[i] = p[i - 1] * 2 % MOD  # 权重翻倍后取模

        b -= 1  # b 改为当前最高位的下标
        for cnt1, cnt0 in pairs:  # 按排序后的顺序依次拼接各段
            while cnt1:  # 先把本段的 1 放到当前最高位
                ans = (ans + p[b]) % MOD  # 该位为 1，累加其权重
                b -= 1  # 处理下一位
                cnt1 -= 1  # 本段的一个 1 已用掉
            b -= cnt0  # 跳过本段 0 占据的低位
        return ans  # 返回最大拼接值
