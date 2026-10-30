# 题目：88. 合并两个有序数组（Merge Sorted Array）
# 思路：从后往前双指针归并。nums1 尾部有 n 个空位，先把较大的元素放到 nums1 末尾，避免覆盖尚未比较的小元素。
# 时间复杂度：O(m + n)，每个元素最多被放一次；空间复杂度：O(1)，只用了三个下标变量。

class Solution:  # LeetCode 约定的题解类
    def merge(self, nums1: List[int], m: int, nums2: List[int], n: int) -> None:  # nums1 前 m 个有效、后 n 个空位；原地并入 nums2
        k = m + n - 1  # k：nums1 的写入位置，从最后一个下标开始
        i, j = m - 1, n - 1  # i 指向 nums1 有效部分的末尾，j 指向 nums2 的末尾
        while j >= 0:  # 只要 nums2 还没放完就继续（nums1 剩余元素本来就在正确位置）
            if i >= 0 and nums1[i] > nums2[j]:  # nums1 还有元素且它更大
                nums1[k] = nums1[i]  # 把较大的 nums1[i] 放到末尾
                i -= 1  # nums1 指针左移
            else:  # nums1 已取空，或 nums2[j] 不小于 nums1[i]
                nums1[k] = nums2[j]  # 把 nums2[j] 放到末尾（相等时优先取 nums2，保证结果稳定且不越界）
                j -= 1  # nums2 指针左移
            k -= 1  # 写入位置左移一位，指向下一个待填的空位
