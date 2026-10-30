# 题目：1213. 三个有序数组的交集（Intersection of Three Sorted Arrays）
# 思路：把三个数组合并起来用 Counter 统计，某值的计数达到 3 就说明它同时出现在三个数组里，再按 arr1 的顺序过滤。
# 时间复杂度：O(n1 + n2 + n3)，统计与过滤各线性；空间复杂度：O(n1 + n2 + n3)，拼接后的数组与计数表。
class Solution:  # LeetCode 约定的题解类
    def arraysIntersection(  # arr1、arr2、arr3：三个升序数组
        self, arr1: List[int], arr2: List[int], arr3: List[int]  # 三个输入数组都是升序，且各自内部没有重复元素
    ) -> List[int]:  # 返回同时出现在三个数组中的元素，保持升序
        cnt = Counter(arr1 + arr2 + arr3)  # 拼成一个序列统一计数，三个数组都含有的值计数恰为 3
        return [x for x in arr1 if cnt[x] == 3]  # 按 arr1 的升序过滤出计数为 3 的值，天然有序
