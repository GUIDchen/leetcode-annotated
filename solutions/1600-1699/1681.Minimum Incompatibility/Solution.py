# 题目：1681. 最小不兼容性（Minimum Incompatibility）
# 思路：状压 DP。先用 g[mask] 预处理每个「元素个数为 n/k 且数字互不相同」的子集的不兼容性，再在状态 mask 上枚举剩余可选位置组成的子集做转移，f[mask] 表示恰好覆盖 mask 的最小代价。
# 时间复杂度：O(n·2^n + 3^n)，子集枚举主导（n ≤ 16）；空间复杂度：O(2^n)，g 与 f 两个数组。
class Solution:  # LeetCode 约定的题解类
    def minimumIncompatibility(self, nums: List[int], k: int) -> int:  # nums：待分组数字；k：组数；返回最小不兼容性之和
        n = len(nums)  # n 是数字个数
        m = n // k  # 每组恰好 m 个数字
        g = [-1] * (1 << n)  # g[mask]：mask 这个子集单独作为一组时的不兼容性，-1 表示不能成组
        for i in range(1, 1 << n):  # 枚举所有非空子集
            if i.bit_count() != m:  # bit_count 统计二进制中 1 的个数，元素个数不是 m 的子集不能成组
                continue  # 直接跳过
            s = set()  # 用集合检查子集内部是否有重复数字
            mi, mx = 20, 0  # mi、mx 记录子集的最小值与最大值（数字不超过 16，20 当哨兵）
            for j, x in enumerate(nums):  # 逐位检查哪些位置被选进子集
                if i >> j & 1:  # 第 j 位为 1，说明 nums[j] 属于子集 i
                    if x in s:  # 出现重复数字，这个子集不合法
                        break  # 提前跳出内层循环
                    s.add(x)  # 记录该数字，供后续去重判断
                    mi = min(mi, x)  # 更新子集最小值
                    mx = max(mx, x)  # 更新子集最大值
            if len(s) == m:  # 集合大小正好为 m，说明这 m 个数字互不相同
                g[i] = mx - mi  # 该子集的不兼容性等于最大值减最小值
        f = [inf] * (1 << n)  # f[mask]：用若干合法组恰好覆盖 mask 的最小不兼容性之和，inf 表示不可达
        f[0] = 0  # 空集不需要任何组，代价为 0
        for i in range(1 << n):  # 按 mask 递增顺序推状态
            if f[i] == inf:  # 该状态不可达，无法继续扩展
                continue  # 跳过
            s = set()  # 记录已经选过代表的数字，保证同一组内不出现重复值
            mask = 0  # mask 汇总「每个不同数值各取一个代表位置」的位
            for j, x in enumerate(nums):  # 遍历所有位置
                if (i >> j & 1) == 0 and x not in s:  # 位置 j 还没被使用，且它对应的数值还没被选作代表
                    s.add(x)  # 标记该数值已出现
                    mask |= 1 << j  # 把位置 j 加入候选位掩码
            if len(s) < m:  # 剩下的不同数值不足 m 个，无法再凑出一组
                continue  # 跳过
            j = mask  # 从 mask 出发枚举它的所有非空子集
            while j:  # while j 控制子集枚举，j 为 0 时结束
                if g[j] != -1:  # 该子集本身能作为合法的一组
                    f[i | j] = min(f[i | j], f[i] + g[j])  # 用这一组更新目标状态的最优值
                j = (j - 1) & mask  # (j - 1) & mask 是枚举子集的标准写法，得到 mask 中下一个更小的子集
        return f[-1] if f[-1] != inf else -1  # 全选状态仍为 inf 说明无解返回 -1，否则返回最小代价
