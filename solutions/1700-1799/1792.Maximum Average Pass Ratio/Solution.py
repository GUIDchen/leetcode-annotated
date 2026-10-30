# 题目：1792. 最大平均通过率（Maximum Average Pass Ratio）
# 思路：贪心 + 小根堆：堆里存「增益的相反数」，堆顶即加人后通过率提升最大的班级；每次给它加一人并重新计算增益，最后求平均。
# 时间复杂度：O((n + extraStudents) log n)；空间复杂度：O(n)，堆中保存所有班级。
class Solution:  # LeetCode 约定的题解类
    def maxAverageRatio(self, classes: List[List[int]], extraStudents: int) -> float:  # 返回分配完额外学生后能达到的最大平均通过率
        h = [(a / b - (a + 1) / (b + 1), a, b) for a, b in classes]  # 堆元素为 (增益的相反数, 已通过人数, 总人数)：取相反数是为了让 heapify 的最小堆等价于按增益取最大
        heapify(h)  # 原地建堆，时间复杂度 O(n)
        for _ in range(extraStudents):  # 逐个分配学生，共循环 extraStudents 次
            _, a, b = heappop(h)  # 弹出增益最大的班级（堆顶是相反数最小的那个），下划线丢弃增益值
            a, b = a + 1, b + 1  # 该班级多收一名学生：通过人数与总人数同时加一
            heappush(h, (a / b - (a + 1) / (b + 1), a, b))  # 重新计算增益并取相反数入堆，供下一轮贪心选择
        return sum(v[1] / v[2] for v in h) / len(classes)  # 把堆中所有班级的通过率求和，再除以班级数得到平均通过率
