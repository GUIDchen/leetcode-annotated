# 题目：658. 找到 K 个最接近的元素（Find K Closest Elements）
# 核心思路：按「与 x 的距离」稳定排序后取前 k 个，再升序返回。
# 时间复杂度：O(n log n)；空间复杂度：O(k) 存放结果。
class Solution:  # LeetCode 约定的题解类
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:  # arr 已升序，返回离 x 最近的 k 个数（按升序）
        arr.sort(key=lambda v: abs(v - x))  # 按与 x 的距离升序排序；sort 稳定，等距元素保持原来的升序
        return sorted(arr[:k])  # 取前 k 个再升序排序后返回
