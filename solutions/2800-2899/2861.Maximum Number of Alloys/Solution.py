# 题目：2861. 最大合金数（Maximum Number of Alloys）
# 思路：答案具有单调性，对每台机器分别在 [0, budget + stock[0]] 上二分合金数，取各机器结果的最大值。
# 复杂度：时间 O(k·n·log(budget))，二分 log 次、每次求和遍历 n 种金属；空间 O(1)。
class Solution:  # LeetCode 约定的题解类
    def maxNumberOfAlloys(  # n：金属种类数；k：机器台数；budget：预算
        self,  # self：实例本身，LeetCode 自动传入
        n: int,  # n 题面要求但本解法不直接用，保留以对齐参数
        k: int,  # k 是机器台数，与 len(composition) 等价
        budget: int,  # budget：总共能花的钱
        composition: List[List[int]],  # composition：每台机器各种金属的配比
        stock: List[int],  # stock：每种金属的现有库存
        cost: List[int],  # cost：每种金属的单价
    ) -> int:  # 返回最多能造的合金数
        ans = 0  # 记录目前找到的最大合金数
        for c in composition:  # 每台机器单独尝试，因为合金只能由同一台机器生产
            l, r = 0, budget + stock[0]  # 二分区间；上界 budget + stock[0] 足以覆盖答案
            while l < r:  # 二分查找这台机器最大可行的合金数
                mid = (l + r + 1) >> 1  # 取上中位数，避免区间不收缩
                s = sum(max(0, mid * x - y) * z for x, y, z in zip(c, stock, cost))  # 造 mid 个的总花费：每种金属的缺口乘单价后求和
                if s <= budget:  # 花费不超过预算，说明 mid 可行
                    l = mid  # 把可行解记到左边界
                else:  # 否则 mid 不可行
                    r = mid - 1  # 上界下调到 mid - 1
            ans = max(ans, l)  # 用这台机器的结果更新全局最优
        return ans  # 返回所有机器中的最大值
