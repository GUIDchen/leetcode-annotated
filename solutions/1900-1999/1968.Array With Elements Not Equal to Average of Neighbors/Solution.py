# 题目：1968. 构造元素不等于两相邻元素平均值的数组（Array With Elements Not Equal to Average of Neighbors）
# 思路：先升序排序，把数组切成较小的前半段与较大的后半段，再两段交错取数，使中间元素绝不会等于左右两个邻居的平均值。
# 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(n)，答案数组。
class Solution:  # LeetCode 约定的题解类
    def rearrangeArray(self, nums: List[int]) -> List[int]:  # nums：待重排的数组
        nums.sort()  # 就地升序排序，便于按大小分成两半
        n = len(nums)  # 数组长度
        m = (n + 1) // 2  # 较小那一半的长度，向上取整：n 为奇数时这一半多一个
        ans = []  # 存放构造结果
        for i in range(m):  # i 同时充当两半段的下标
            ans.append(nums[i])  # 先放较小那一半的第 i 个元素
            if i + m < n:  # 较大那一半的下标未越界（n 为奇数时最后一轮没有对应元素）
                ans.append(nums[i + m])  # 再放较大那一半的第 i 个元素，形成小大交替
        return ans  # 返回交错排列后的数组
