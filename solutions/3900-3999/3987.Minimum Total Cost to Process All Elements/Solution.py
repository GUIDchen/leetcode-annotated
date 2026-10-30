# 题目：3987. Minimum Total Cost to Process All Elements（3987. 处理所有元素的成本）
# 核心思路：贪心模拟。维护当前资源 cur（初值 k），处理每个元素 x 时若 cur < x，则再执行 ceil((x-cur)/k) 次补充操作恰好够用；第 i 次操作成本为 i，于是总成本是 1+2+…+cnt = cnt·(cnt+1)/2。
# 复杂度：时间 O(n)，空间 O(1)。
class Solution:  # 定义题解类
    def minimumCost(self, nums: list[int], k: int) -> int:  # 返回按顺序处理完所有元素的最小总成本
        cnt = 0  # 已执行的补充操作次数
        cur = k  # 当前可用资源，初始是 k
        mod = 10**9 + 7  # 取模常量 1e9+7
        for x in nums:  # 按顺序处理每个元素
            diff = x - cur  # 处理当前元素所需的资源缺口
            if diff > 0:  # 资源不足，必须补充
                m = (diff + k - 1) // k  # 向上取整得到至少需要的补充次数 m
                cur += m * k  # 补充后资源增加 m·k
                cnt += m  # 操作次数累加
            cur -= x  # 支付 x 单位资源处理当前元素
        cnt %= mod  # 先取模，避免后面乘法过大
        return (1 + cnt) * cnt // 2 % mod  # 总成本为 1+2+…+cnt = cnt·(cnt+1)/2，再取模
