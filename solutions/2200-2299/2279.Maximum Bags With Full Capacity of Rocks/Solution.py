# 题目：2279. 装满石头的背包的最大数量（Maximum Bags With Full Capacity of Rocks）
# 思路：算出每个背包的缺口 capacity[i] - rocks[i]，升序排序后用额外石头从缺口最小的开始填，能填几个就是几个。
# 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(1)，在传入的数组上原地修改。
class Solution:  # LeetCode 约定的题解类
    def maximumBags(  # capacity 为各背包容量，rocks 为现有石头，additionalRocks 为可额外分配的石头总数
        self, capacity: List[int], rocks: List[int], additionalRocks: int  # 参数列表（严格按题面顺序：容量、现有石头、额外石头）
    ) -> int:  # 返回值：能够装满的背包最大数量
        for i, x in enumerate(rocks):  # 遍历每个背包：i 是下标，x 是该背包当前已有的石头数
            capacity[i] -= x  # 原地把容量改写成「还差多少块石头才装满」
        capacity.sort()  # 按缺口升序排序：缺口小的背包更划算，优先填
        for i, x in enumerate(capacity):  # 依次尝试装满排序后的背包
            additionalRocks -= x  # 用额外石头填上当前背包的缺口
            if additionalRocks < 0:  # 石头不够，说明第 i 个背包装不满
                return i  # 前 i 个背包已装满，答案是 i
        return len(capacity)  # 石头足够，所有背包都能装满
