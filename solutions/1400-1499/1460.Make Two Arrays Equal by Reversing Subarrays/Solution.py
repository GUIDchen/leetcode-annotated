# 题目：1460. 通过翻转子数组使两个数组相等（Make Two Arrays Equal by Reversing Subarrays）
# 思路：反转只改变顺序、不改变元素的多重集合，所以排序后比较两个数组是否逐位相同即可。
# 时间复杂度：O(n log n)，排序是主要开销；空间复杂度：O(n)，sorted 生成了两个新列表。
class Solution:  # LeetCode 约定的题解类
    def canBeEqual(self, target: List[int], arr: List[int]) -> bool:  # target、arr：两个待比较的数组
        return sorted(target) == sorted(arr)  # sorted 返回升序新列表，两个列表相等即元素多重集合相同
