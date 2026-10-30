# 题目：1439. 有序矩阵中的第 k 个最小数组和（Find the Kth Smallest Sum of a Matrix With Sorted Rows）
# 思路：逐行递推，pre 始终保存「已处理行」的前 k 小数组和；每行与 pre 两两相加后排序截断到 k 个。
# 时间复杂度：O(m·k²·log(k²))；空间复杂度：O(k²)。
class Solution:  # LeetCode 约定的题解类
    def kthSmallest(self, mat: List[List[int]], k: int) -> int:  # mat 是每行递增的矩阵，k 是要求的排名
        pre = [0]  # 一行都还没取时，唯一的数组和是 0
        for cur in mat:  # 逐行并入，cur 是当前这一行的值
            pre = sorted(a + b for a in pre for b in cur[:k])[:k]  # 上一轮的前 k 小和与本行前 k 个元素两两相加（行内递增，更大的列不可能进前 k），排序后只保留前 k 个
        return pre[-1]  # 此时 pre 恰好是前 k 小且升序，最后一个就是第 k 小
