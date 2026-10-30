# 题目：1619. 删除某些元素后的数组均值（Mean of Array After Removing Some Elements）
# 思路：先排序，去掉最小的 5% 与最大的 5%，再对中间 90% 的元素求平均并按要求保留 5 位小数。
# 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(n)，切片会复制中间段（原地排序本身只需 O(log n) 栈）。
class Solution:  # LeetCode 约定的题解类
    def trimMean(self, arr: List[int]) -> float:  # arr：长度为 20 的倍数的整数数组
        n = len(arr)  # 记录原数组长度，用来计算删除个数与切片位置
        start, end = int(n * 0.05), int(n * 0.95)  # start/end 分别是保留区间的起点与终点（end 不含）
        arr.sort()  # 原地升序排序，让最小、最大的元素分别落到两端
        t = arr[start:end]  # 切片取出中间 90% 的元素
        return round(sum(t) / len(t), 5)  # 求和除以个数得到均值，再四舍五入到 5 位小数
