# 3462. 提取至多 K 个元素的最大总和 / Maximum Sum With at Most K Elements
# 核心思路：每行升序排序后只取不超过 limits[i] 个最大值，用小顶堆维护全局最大的至多 k 个元素，最后求和。
# 复杂度：时间 O(S log L + S log k)，空间 O(k + L)，S 为各行取数总量、L 为单行长度。
class Solution:  # 定义题解类
    def maxSum(self, grid: List[List[int]], limits: List[int], k: int) -> int:  # 返回至多选 k 个元素能得到的最大总和
        pq = []  # 小顶堆，保存当前全局最大的至多 k 个元素
        for nums, limit in zip(grid, limits):  # 把每一行与该行可选上限配对遍历
            nums.sort()  # 升序排序，末尾是最大值
            for _ in range(limit):  # 取该行前 limit 大的元素
                heappush(pq, nums.pop())  # 弹出该行最大值（即当前全局候选）并入堆
                if len(pq) > k:  # 堆内元素超过 k 个
                    heappop(pq)  # 弹出最小值，保持堆内是最大的 k 个
        return sum(pq)  # 堆内元素之和即答案
