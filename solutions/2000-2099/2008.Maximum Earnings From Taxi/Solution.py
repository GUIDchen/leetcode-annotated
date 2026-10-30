# 题目：2008. 出租车的最大盈利（Maximum Earnings From Taxi）
# 思路：按起点排序后做记忆化搜索：dfs(i) 表示只考虑第 i 单及之后的订单能获得的最大盈利，每次要么跳过第 i 单，要么接单后跳到第一个起点不小于本单终点的订单，两者取较大值。
# 时间复杂度：O(m log m)，每次状态转移二分查找一次；空间复杂度：O(m)，缓存表与递归深度。
class Solution:  # LeetCode 约定的题解类
    def maxTaxiEarnings(self, n: int, rides: List[List[int]]) -> int:  # n 是道路总长度（本题无需用到）；rides[i] = [起点, 终点, 小费]；返回能获得的最大盈利
        @cache  # 用 @cache 记住每个下标的答案，避免重复搜索同一后缀
        def dfs(i: int) -> int:  # dfs(i)：只考虑第 i 单及之后订单时能获得的最大盈利
            if i >= len(rides):  # 下标越界说明后面没有订单可接
                return 0  # 递归边界：盈利为 0
            st, ed, tip = rides[i]  # 拆出当前订单的起点、终点与小费
            j = bisect_left(rides, ed, lo=i + 1, key=lambda x: x[0])  # 二分找第一个起点不小于 ed 的订单下标；lo=i+1 表示从下一单开始找，key 指定按起点比较
            return max(dfs(i + 1), dfs(j) + ed - st + tip)  # 两种选择取较大值：不接第 i 单，或接单后跳到 j，本次盈利为 ed - st + tip

        rides.sort()  # 先按起点升序排序，二分查找才有意义
        return dfs(0)  # 从第 0 单开始搜索全局最优解
