# 题目：857. 雇佣 K 名工人的最低成本（Minimum Cost to Hire K Workers）
# 思路：按「工资/质量」比值升序排序，枚举每个人的比值作为全员统一单价，同时用堆维护质量总和最小的 k 人。
# 时间复杂度：O(n log n)，排序与堆操作；空间复杂度：O(n)，比值列表与堆。
class Solution:  # 题解类
    def mincostToHireWorkers(  # 按「工资/质量」比值升序枚举统一单价
        self, quality: List[int], wage: List[int], k: int  # quality 为工作质量，wage 为最低期望工资，k 为雇佣人数
    ) -> float:  # 返回最小总成本
        t = sorted(zip(quality, wage), key=lambda x: x[1] / x[0])  # 把 (质量, 工资) 按工资/质量比值升序排序
        ans, tot = inf, 0  # ans 最小成本，tot 当前选中工人的质量总和
        h = []  # 用负质量维护大根堆，便于淘汰质量最大者
        for q, w in t:  # 依次以当前工人的比值作为统一单价
            tot += q  # 累加当前工人质量
            heappush(h, -q)  # 压入负质量（大根堆技巧）
            if len(h) == k:  # 已选够 k 人
                ans = min(ans, w / q * tot)  # 成本 = 质量总和 × 当前统一单价
                tot += heappop(h)  # 弹出质量最大的工人：heappop 返回负值，加到总和上等价于减去
        return ans  # 返回最小总成本
