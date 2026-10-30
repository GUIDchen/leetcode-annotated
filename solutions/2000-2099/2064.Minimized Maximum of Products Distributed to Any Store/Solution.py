# 题目：2064. 分配给商店的最多商品的最小值（Minimized Maximum of Products Distributed to Any Store）
# 思路：二分答案，内嵌 check(x) 判断单店上限为 x 时商店是否够用，再用 bisect_left 找出第一个满足条件的位置。
# 时间复杂度：O(m log 1e6)，m 为商品种类数；空间复杂度：O(1)，只用了常数个辅助变量。
class Solution:  # LeetCode 约定的题解类
    def minimizedMaximum(self, n: int, quantities: List[int]) -> int:  # n 是商店数量，quantities 是各商品件数
        def check(x):  # 内嵌判定函数：单店上限为 x 时，能否用不超过 n 家店装完
            return sum((v + x - 1) // x for v in quantities) <= n  # 向上取整求每种商品所需商店数，求和后与 n 比较

        # 在候选上限区间 [1, 10**6) 上做二分，找第一个判定为 True 的位置
        # bisect_left 返回的是下标（从 0 开始），所以再加 1 才是真正的最小上限
        return 1 + bisect_left(range(1, 10**6), True, key=check)  # key=check 让二分直接比较判定结果
