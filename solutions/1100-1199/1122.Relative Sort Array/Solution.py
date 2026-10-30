# 题目：1122. 数组的相对排序（Relative Sort Array）
# 思路：arr2 中的值用其下标作排序键，未出现的值用 1000+x 作键——既排在下标之后，又按值升序。
# 时间复杂度：O(n log n)，主要开销是 sorted；空间复杂度：O(n)，哈希表与结果列表。
class Solution:  # LeetCode 约定的题解类
    def relativeSortArray(self, arr1: List[int], arr2: List[int]) -> List[int]:  # 按 arr2 顺序重排 arr1，arr2 里没有的元素升序排在后面
        pos = {x: i for i, x in enumerate(arr2)}  # 值 → 在 arr2 中的下标，下标越小越靠前
        return sorted(arr1, key=lambda x: pos.get(x, 1000 + x))  # 出现过的用下标作键；没出现的用 1000+x：先排在下标之后，再按值升序
