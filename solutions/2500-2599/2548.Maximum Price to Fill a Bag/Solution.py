# 题目：2548. 填满背包的最大价格（Maximum Price to Fill a Bag）
# 思路：贪心。物品可按比例拆分，因此按单位重量价格从高到低排序后依次尽量装满；容量还有剩余则返回 -1。
# 时间复杂度：O(n log n)，由排序决定；空间复杂度：O(n)，sorted 生成排序后的列表。
class Solution:  # LeetCode 约定的题解类
    def maxPrice(self, items: List[List[int]], capacity: int) -> float:  # items 的每个元素是 [price, weight]；capacity 是背包容量
        ans = 0  # ans 累计已装入部分的价值
        for p, w in sorted(items, key=lambda x: x[1] / x[0]):  # 按 weight/price 升序等价于按单位价格降序，优先装单位价格高的物品
            v = min(w, capacity)  # 本物品最多能装 min(重量, 剩余容量)
            ans += v / w * p  # 按装入比例折算价值
            capacity -= v  # 扣掉本次占用的容量
        return -1 if capacity else ans  # capacity 非 0 说明装不满，返回 -1；否则返回累计价值
