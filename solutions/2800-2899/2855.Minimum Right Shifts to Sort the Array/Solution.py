# 题目：2855. 使数组成为递增数组的最少右移次数（Minimum Right Shifts to Sort the Array）
# 核心思路：右移等价于循环移位，先找到第一段严格递增的结尾 i，再验证剩余部分也递增且都小于首元素，答案是 n - i。
# 时间复杂度：O(n)，只线性扫描一遍；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def minimumRightShifts(self, nums: List[int]) -> int:  # nums 为待排序的数组
        n = len(nums)  # 数组长度
        i = 1  # i 指向第一段严格递增区间的下一个位置
        while i < n and nums[i - 1] < nums[i]:  # 找到第一处不再严格递增的断点
            i += 1  # 仍然递增就继续右移指针
        k = i + 1  # 从断点的下一位开始检查第二段
        while k < n and nums[k - 1] < nums[k] < nums[0]:  # 第二段必须严格递增且整体小于首元素
            k += 1  # 满足条件就继续右移指针
        return -1 if k < n else n - i  # 没走到末尾说明无法排好序返回 -1，否则右移 n - i 次
