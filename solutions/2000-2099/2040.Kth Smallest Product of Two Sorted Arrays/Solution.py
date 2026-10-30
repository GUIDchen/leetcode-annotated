# 题目：2040. 两个有序数组的第 K 小乘积（Kth Smallest Product of Two Sorted Arrays）
# 思路：二分答案，用 count(p) 统计乘积不超过 p 的数对个数；nums2 有序，可按 nums1 元素的符号用 bisect 定位分界点，再二分出答案。
# 时间复杂度：O(m log n log(M))，m、n 为两数组长度、M 为值域；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def kthSmallestProduct(self, nums1: List[int], nums2: List[int], k: int) -> int:  # nums1、nums2：两个升序数组；k：第 k 小（从 1 开始）
        def count(p: int) -> int:  # count(p)：统计乘积不超过 p 的数对个数
            cnt = 0  # cnt：数对个数累加器
            n = len(nums2)  # n：nums2 的长度，处理负数时要用到
            for x in nums1:  # 枚举 nums1 的每个元素
                if x > 0:  # x 为正数时，乘积随 nums2 单调递增
                    cnt += bisect_right(nums2, p / x)  # bisect_right 找出第一个大于 p/x 的位置，它前面的元素乘积都不超过 p
                elif x < 0:  # x 为负数时，乘积随 nums2 单调递减
                    cnt += n - bisect_left(nums2, p / x)  # bisect_left 找到第一个不小于 p/x 的位置，它及其右侧的乘积都不超过 p
                else:  # x 为 0，所有乘积都是 0，只有 p 不为负时才计入
                    cnt += n * int(p >= 0)  # n 个乘积 0 全部计入
            return cnt  # 返回乘积不超过 p 的数对总数

        mx = max(abs(nums1[0]), abs(nums1[-1])) * max(abs(nums2[0]), abs(nums2[-1]))  # mx：最大乘积的绝对值，由两数组各自两端绝对值较大者相乘得到
        return bisect_left(range(-mx, mx + 1), k, key=count) - mx  # 在 [-mx, mx] 上二分：bisect_left 找到第一个 count 不小于 k 的位置，再减去偏移 mx 还原成乘积
