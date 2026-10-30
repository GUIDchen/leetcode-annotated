# 题目：218. 天际线问题（The Skyline Problem）
# 核心思路：扫所有楼的左右端点，用（取负模拟的）大顶堆维护当前覆盖的最高楼，堆顶高度变化处即为关键点。
# 时间复杂度：O(n log n)，排序加每个楼入堆出堆各一次；空间复杂度：O(n)，端点列表与堆。
from queue import PriorityQueue  # 导入优先队列；Python 的堆是最小堆，下面用负数模拟大顶堆


class Solution:  # LeetCode 约定的题解类
    def getSkyline(self, buildings: List[List[int]]) -> List[List[int]]:  # 输入 [左端, 右端, 高度] 的楼群，返回天际线的关键点集合
        skys, lines, pq = [], [], PriorityQueue()  # skys 存结果，lines 存所有端点横坐标，pq 存当前覆盖的楼
        for build in buildings:  # 遍历每栋楼
            lines.extend([build[0], build[1]])  # 把左右端点都收进候选横坐标
        lines.sort()  # 端点升序排序，得到扫描线从左到右的推进顺序
        city, n = 0, len(buildings)  # city：下一栋待入堆的楼下标；n：楼的总数
        for line in lines:  # 按横坐标从小到大依次扫描每个端点
            while city < n and buildings[city][0] <= line:  # 把左端点已经到达当前横坐标的楼依次入堆
                pq.put([-buildings[city][2], buildings[city][0], buildings[city][1]])  # 压入 [-高度, 左端, 右端]：取负是为了让最小堆按高度弹出最高的楼
                city += 1  # 处理下一栋楼
            while not pq.empty() and pq.queue[0][2] <= line:  # 堆顶的楼已经在当前横坐标处或之前结束，需要移除
                pq.get()  # 弹出失效元素
            high = 0  # 默认高度为 0，表示该横坐标处没有楼覆盖
            if not pq.empty():  # 堆非空时取堆顶
                high = -pq.queue[0][0]  # 取回真实高度（把负号还原）
            if len(skys) > 0 and skys[-1][1] == high:  # 与前一个关键点高度相同，说明不产生新轮廓
                continue  # 跳过，不记录这个点
            skys.append([line, high])  # 记录关键点 [横坐标, 当前最大高度]
        return skys  # 返回天际线关键点
