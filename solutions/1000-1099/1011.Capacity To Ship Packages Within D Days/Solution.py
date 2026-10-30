# 题目：1011. 在 D 天内送达包裹的能力（Capacity To Ship Packages Within D Days）
# 核心思路：二分答案：在重量最大值与总重量之间查找最小可行运力
# 复杂度：时间 O(n log(sum))，每次 check 线性扫描；空间 O(1)
class Solution:  # LeetCode 约定的题解类
    def shipWithinDays(self, weights: List[int], days: int) -> int:  # weights：包裹重量（必须按给定顺序装运）；days：限定天数
        def check(mx):  # 内层函数：判断运力为 mx 时能否在 days 天内运完
            ws, cnt = 0, 1  # ws：当前这一船已装重量；cnt：已用天数（至少要用 1 天）
            for w in weights:  # 按给定顺序依次装船，顺序不能打乱
                ws += w  # 把当前包裹装上这一船
                if ws > mx:  # 超过运力，只能改用下一天
                    cnt += 1  # 使用天数加一
                    ws = w  # 新的一天从当前包裹开始装
            return cnt <= days  # 用掉的天数不超过限定天数就说明运力足够

        left, right = max(weights), sum(weights) + 1  # 二分区间：下界取最重包裹，上界取总重加一（右开，实际覆盖到总重）
        return left + bisect_left(range(left, right), True, key=check)  # range 是惰性序列，key=check 在偏移量上二分，返回第一个可行运力的偏移，加上下界即答案
