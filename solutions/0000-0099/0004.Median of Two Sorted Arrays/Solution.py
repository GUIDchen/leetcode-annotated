# 题目：4. 寻找两个正序数组的中位数（Median of Two Sorted Arrays）
# 思路：二分第 k 小——每轮比较两数组第 k/2 个元素，淘汰较小的一段并把 k 减去该步长，递归逼近中位数。
# 时间复杂度：O(log(m + n))，k 每层减半；空间复杂度：O(log(m + n))，递归调用的栈深度。
class Solution:  # LeetCode 约定的题解类
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:  # 两个升序数组，返回合并后的中位数
        def f(i: int, j: int, k: int) -> int:  # 内部递归函数：在 nums1[i..]、nums2[j..] 中找第 k 小的数
            if i >= m:  # nums1 已取空
                return nums2[j + k - 1]  # 答案只能来自 nums2
            if j >= n:  # nums2 已取空
                return nums1[i + k - 1]  # 答案只能来自 nums1
            if k == 1:  # 只需要一个元素
                return min(nums1[i], nums2[j])  # 取两个候选头部的较小值
            p = k // 2  # 每轮淘汰的步长
            x = nums1[i + p - 1] if i + p - 1 < m else inf  # nums1 的第 p 个候选，越界时视为正无穷
            y = nums2[j + p - 1] if j + p - 1 < n else inf  # nums2 的第 p 个候选，越界同样视为正无穷
            return f(i + p, j, k - p) if x < y else f(i, j + p, k - p)  # 较小的一段整体被淘汰，k 减去 p 继续找

        m, n = len(nums1), len(nums2)  # 求出长度，供上面的闭包读取（闭包按引用查变量）
        a = f(0, 0, (m + n + 1) // 2)  # 左中位数
        b = f(0, 0, (m + n + 2) // 2)  # 右中位数；总数为奇数时 a、b 是同一个数
        return (a + b) / 2  # 取平均；Python 的 / 自动得到 float
