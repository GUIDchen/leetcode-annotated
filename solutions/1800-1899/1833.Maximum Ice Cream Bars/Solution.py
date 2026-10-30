# 题目：1833. 雪糕的最大数量（Maximum Ice Cream Bars）
# 思路：贪心，先排序价格，再从最便宜的雪糕开始买，直到钱不够为止。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，原地排序（TimSort 额外开销视实现而定）。
class Solution:  # LeetCode 约定的题解类
    def maxIceCream(self, costs: List[int], coins: int) -> int:  # costs：各雪糕的价格；coins：手里的钱；返回最多能买的雪糕数量
        costs.sort()  # 原地升序排序，优先买便宜的
        for i, c in enumerate(costs):  # 按价格从小到大依次尝试购买
            if coins < c:  # 钱不够买当前这支
                return i  # 已经买了 i 支，直接返回
            coins -= c  # 买下当前雪糕，扣除花费
        return len(costs)  # 全部买得起，返回总数量
