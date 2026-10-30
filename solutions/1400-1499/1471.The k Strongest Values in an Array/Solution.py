# 题目：1471. 数组中的 k 个最强值（The k Strongest Values in an Array）
# 核心思路：先排序取得中位数 m（下标 (n-1)/2），再按「与 m 的距离降序、距离相同时值更大者优先」重排，取前 k 个。
# 时间复杂度：O(n log n)，两次排序；空间复杂度：O(k)，切片返回前 k 个元素。
class Solution:  # LeetCode 约定的题解类
    def getStrongest(self, arr: List[int], k: int) -> List[int]:  # arr 是输入数组，k 是要取出的最强值个数
        arr.sort()  # 先升序排序，才能直接按下标取到中位数
        m = arr[(len(arr) - 1) >> 1]  # 题目定义的中位数：下标 (n-1)/2（右移一位等价于除以 2 向下取整）
        arr.sort(key=lambda x: (-abs(x - m), -x))  # 以 (-距离, -值) 为键升序排序，等价于距离降序、同距离时值降序
        return arr[:k]  # 切片取前 k 个即为最强值
