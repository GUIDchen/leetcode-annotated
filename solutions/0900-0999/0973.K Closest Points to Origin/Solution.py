# 题目：973. 最接近原点的 K 个点（K Closest Points to Origin）
# 思路：按到原点的欧氏距离升序排序，排序后的前 k 个点就是答案。
# 时间复杂度：O(n log n)，来自排序；空间复杂度：O(k)，返回结果占用的空间。
class Solution:  # LeetCode 约定的题解类
    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:  # points：所有点的坐标；k：需要取出的点数
        points.sort(key=lambda p: hypot(p[0], p[1]))  # 以到原点的距离为 key 原地升序排序，hypot 计算欧氏距离
        return points[:k]  # 排序后前 k 个即最近的 k 个点
