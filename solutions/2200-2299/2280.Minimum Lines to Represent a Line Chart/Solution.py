# 题目：2280. 表示一个折线图的最少线段数（Minimum Lines to Represent a Line Chart）
# 思路：先按日期排序，再用 pairwise 取相邻两点逐段用叉积比较斜率，斜率变化就新起一条线段，避免浮点误差。
# 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(1)，不计排序自身开销。
class Solution:  # LeetCode 约定的题解类
    def minimumLines(self, stockPrices: List[List[int]]) -> int:  # stockPrices[i] = [第 i 天, 当天股价]
        stockPrices.sort()  # 按日期升序排序，让相邻两点的连线正是折线图的每一段
        dx, dy = 0, 1  # 上一段的横纵增量；初值 (0, 1) 保证第一段一定被计入
        ans = 0  # 线段计数
        for (x, y), (x1, y1) in pairwise(stockPrices):  # pairwise 依次取出时间上相邻的两个点
            dx1, dy1 = x1 - x, y1 - y  # 当前段的横纵增量
            if dy * dx1 != dx * dy1:  # 叉积不等说明斜率改变，需要另起一条线段；Python 大整数不会溢出
                ans += 1  # 线段数加一
            dx, dy = dx1, dy1  # 更新「上一段」的增量，供下一轮比较
        return ans  # 返回最少线段数
