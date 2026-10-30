# 题目：215. 数组中的第K个最大元素（Kth Largest Element in an Array）
# 核心思路：把「第 k 大」换算成升序下标 n-k，用快速选择每次只递归目标所在的一侧，避免整体排序。
# 时间复杂度：O(n) 平均，每轮划分期望排除一半元素；空间复杂度：O(log n)，递归栈深度期望为对数级。
class Solution:  # LeetCode 约定的题解类
    def findKthLargest(self, nums: List[int], k: int) -> int:  # 返回数组升序排序后第 k 大的元素
        def quick_sort(l: int, r: int) -> int:  # 在闭区间 [l, r] 内做快速选择，返回目标下标的元素
            if l == r:  # 区间只剩一个元素，它就是答案
                return nums[l]  # 直接返回该元素
            i, j = l - 1, r + 1  # 双指针从区间外侧一格开始，便于先自增/自减再比较
            x = nums[(l + r) >> 1]  # 取中点元素作为划分基准
            while i < j:  # 两指针未交错时继续划分
                while 1:  # 无限循环，靠内部的 break 退出（等价 do-while）
                    i += 1  # 左指针先右移一格
                    if nums[i] >= x:  # 找到第一个不小于基准的元素
                        break  # 退出内层循环
                while 1:  # 同样靠 break 退出的循环
                    j -= 1  # 右指针先左移一格
                    if nums[j] <= x:  # 找到第一个不大于基准的元素
                        break  # 退出内层循环
                if i < j:  # 两指针没交错，说明这两个元素放错了边
                    nums[i], nums[j] = nums[j], nums[i]  # 交换它们，使左边不大于基准、右边不小于基准
            if j < k:  # 划分后 j 是左半区右端点；目标下标在右半区
                return quick_sort(j + 1, r)  # 只在右半区递归查找
            return quick_sort(l, j)  # 否则目标在左半区（含 j），继续在 [l, j] 里找

        n = len(nums)  # 数组长度
        k = n - k  # 第 k 大等价于升序下标 n-k（0 基）
        return quick_sort(0, n - 1)  # 从整个数组开始快速选择
